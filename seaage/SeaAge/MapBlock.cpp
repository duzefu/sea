/*
**  mapblock.cpp
**  map block functions.
**  
**  geaan, 2001.6.22.
*/
#include "mainfun.h"
#include "mapblock.h"



MAP_BLOCK   map_block[MAX_MAP_BLOCK];
SLONG       map_block_max = 0;



void    reset_map_block_count(void)
{
    map_block_max = 0;
}


SLONG   get_map_block_count(void)
{
    return map_block_max;
}

void    set_map_block_count(SLONG count)
{
    map_block_max = count;
}

void    naked_read_map_block(PACK_FILE *fp, SLONG read_blocks)
{
    if( (read_blocks < MAX_MAP_BLOCK) && (fp) )
    {
        pack_fread((USTR *)map_block, 1, sizeof(MAP_BLOCK)*read_blocks, fp);
    }
}


void    redraw_map_block_layer(SLONG sx,SLONG sy,SLONG flag,BMP *bmp)
{
    SLONG i;
    const SLONG draw_poly_flags = PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS 
        | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_PINK;//| PDP_ZHEIGHT;

    if(!flag) return;
    for(i=0;i<map_block_max;i++)
    {
        D3_draw_poly(-sx, -sy, 0, draw_poly_flags, &map_block[i].poly, bmp);
        //D3_draw_poly(-map_data.map_sx, -map_data.map_sy, 0, draw_poly_flags, &map_block[i].poly, bmp);
        
        sprintf((char *)print_rec,"~C0~O3%d~C0~O0~C4~C0",i);
        print16(map_block[i].poly.bx-sx, map_block[i].poly.by-sy, (USTR *)print_rec,PEST_PUT,bmp);
    }
}


SLONG   find_map_block_whose_cover_include_point(SLONG x,SLONG y)
{
    SLONG   i,find;
    
    find=-1;
    for(i=0;i<map_block_max;i++)
    {
        if(TRUE == D3_is_point_in_poly_cover(&(map_block[i].poly),x,y) )
        {
            find=i;
            break;
        }
    }
    return(find);
}



SLONG   find_point_of_map_block_underside(SLONG *x,SLONG *y,SLONG *no,SLONG *index,SLONG dist)
{
    SLONG xx,yy;
    SLONG i,j,pn,tx,ty;
    
    xx=*x;
    yy=*y;
    for(i=0;i<map_block_max;i++)
    {
        pn=map_block[i].poly.pn;
        for(j=0;j<pn;j++)
        {
            tx=map_block[i].poly.px[j];
            ty=map_block[i].poly.py[j];
            if(abs(tx-xx)<dist && abs(ty-yy)<dist)
            {
                *x=tx;
                *y=ty;
                *no=i;
                *index=j;
                return(TTN_OK);
            }
        }
    }
    *no=-1;
    *index=0;
    return(TTN_NOT_OK);
}


USTR *  get_map_block_type_string(SLONG type)
{
    switch(type)
    {
    case MBT_LAND          :return (USTR *)"陸地";
    case MBT_SNOW          :return (USTR *)"雪地";
    case MBT_WATER         :return (USTR *)"淺水";
    case MBT_BOG           :return (USTR *)"沼澤";
    case MBT_DEEPWATER     :return (USTR *)"深水";
    case MBT_BUILDING      :return (USTR *)"建筑";
    default:        return (USTR *)"未知";
    }
}


void    clear_all_map_blocks(void)
{
    SLONG i;

    map_block_max=0;
    for(i=0;i<MAX_MAP_BLOCK;i++)
        clear_map_block(i);
}


SLONG   add_map_block(SLONG type,POLY poly)
{
    if(map_block_max < MAX_MAP_BLOCK)
    {
        map_block[map_block_max].type = type;
        D3_copy_poly(&map_block[map_block_max].poly,&poly);
        map_block_max ++;
        return (map_block_max-1);   // return added index
    }
    return -1;
}

void    del_map_block(SLONG index)
{
    SLONG i;
    if(index>=0 && index<map_block_max)
    {
        for(i=index;i<map_block_max-1;i++)
            memcpy(&map_block[i],&map_block[i+1],sizeof(MAP_BLOCK));
        clear_map_block(map_block_max-1);
        map_block_max--;
        if(map_block_max<0)
            map_block_max=0;
    }
}


void    clear_map_block(SLONG index)
{
    SLONG i;

    map_block[index].type = MBT_LAND;
    D3_clear_poly(&map_block[index].poly);
    for(i=0;i<MAX_POLY_NUM;i++)
    {
        map_block[index].adj[i] = -1;
        map_block[index].dist[i] = 99999999;
    }
}


SLONG   update_map_block_data(void)
{
    SLONG   i,j,pn;
    SLONG   x1,x2,y1,y2,z1,z2;
    SLONG   n1,n2,l1,l2;
    SLONG   dist;
    
    for(i=0;i<map_block_max;i++)
    {
        pn=map_block[i].poly.pn;
        if(pn>0)
        {
            for(j=0;j<pn;j++)
            {
                x1=map_block[i].poly.px[j];
                y1=map_block[i].poly.py[j];
                z1=map_block[i].poly.pz[j];
                x2=map_block[i].poly.px[(j+1)%pn];
                y2=map_block[i].poly.py[(j+1)%pn];
                z2=map_block[i].poly.pz[(j+1)%pn];
                find_map_block_line(x1,y1,z1,x2,y2,z2,&n1,&l1,&n2,&l2);
                if(n1>=0 && l1>=0 && n2>=0 && l2>=0)
                {
                    //add .other[] here to memorize the relation of the two blocks ,
                    //we will use it later in find walk path.
                    map_block[n1].adj[l1]=n2;
                    map_block[n1].other[l1]=l2;
                    
                    map_block[n2].adj[l2]=n1;
                    map_block[n2].other[l2]=l1;
                    
                    dist=operate_map_block_distance(n1,n2);
                    map_block[n1].dist[l1]=dist;
                    map_block[n2].dist[l2]=dist;
                }
                else
                {
                    map_block[i].adj[j]=-1;
                    map_block[i].other[j]=-1;
                    map_block[i].dist[j]=MAX_PATH_LONG;
                }
            }
        }
    }
    return(TTN_OK);
}



SLONG   find_map_block_line(SLONG x1,SLONG y1,SLONG z1,SLONG x2,SLONG y2,SLONG z2,SLONG *no1,SLONG *lindex1,SLONG *no2,SLONG *lindex2)
{
    static  SLONG   b1,b2,l1,l2;
    SLONG   i,j,pn;
    SLONG   tx1,ty1,tz1,tx2,ty2,tz2;
    SLONG   d1,d2,d3,d4;
    SLONG   find;
    
    find=0;
    b1=l1=b2=l2=-1;
    for(i=0;i<map_block_max;i++)
    {
        pn=map_block[i].poly.pn;
        if(pn>0)
        {
            for(j=0;j<pn;j++)
            {
                tx1=map_block[i].poly.px[j];
                ty1=map_block[i].poly.py[j];
                tz1=map_block[i].poly.pz[j];
                tx2=map_block[i].poly.px[(j+1)%pn];
                ty2=map_block[i].poly.py[(j+1)%pn];
                tz2=map_block[i].poly.pz[(j+1)%pn];
                d1=abs(tx1-x1)+abs(ty1-y1)+abs(tz1-z1);
                d2=abs(tx2-x2)+abs(ty2-y2)+abs(tz2-z2);
                d3=abs(tx1-x2)+abs(ty1-y2)+abs(tz1-z2);
                d4=abs(tx2-x1)+abs(ty2-y1)+abs(tz2-z1);
                if((d1==0 && d2==0)||(d3==0 && d4==0))
                {
                    if(find==0)
                    {
                        b1=i;
                        l1=j;
                        find=1;
                    }
                    else if(find==1)
                    {
                        b2=i;
                        l2=j;
                        j=pn+100;
                        i=map_block_max+100;
                    }
                }
            }
        }
    }
    *no1=b1;
    *lindex1=l1;
    *no2=b2;
    *lindex2=l2;
    return(TTN_OK);
}


SLONG   operate_map_block_distance(SLONG index1,SLONG index2)
{
    SLONG   i,type1,type2;
    SLONG   find,pn;
    SLONG   dist,x1,y1,z1,x2,y2,z2;
    SLONG   xx1,yy1,zz1,xx2,yy2,zz2,width;
    
    type1=map_block[index1].type;
    type2=map_block[index2].type;
    if(!(type1 & type2))
        return(MAX_PATH_LONG);
    if(index1==index2)
        return(0);
    find=-1;
    pn=map_block[index1].poly.pn;
    for(i=0;i<pn;i++)
    {
        if(map_block[index1].adj[i]==index2)
        {
            find=i;
            break;
        }
    }
    if(find>=0)
    {
        xx1=map_block[index1].poly.px[find];
        yy1=map_block[index1].poly.py[find];
        zz1=map_block[index1].poly.pz[find];
        xx2=map_block[index1].poly.px[(find+1)%pn];
        yy2=map_block[index1].poly.py[(find+1)%pn];
        zz2=map_block[index1].poly.pz[(find+1)%pn];
        width=(SLONG)(sqrt((xx1-xx2)*(xx1-xx2)+(yy1-yy2)*(yy1-yy2)+(zz1-zz2)*(zz1-zz2)));
        if(width<MIN_PATH_WIDTH)
            return(MAX_PATH_LONG);
        x1=map_block[index1].poly.bx;
        y1=map_block[index1].poly.by;
        z1=map_block[index1].poly.bz;
        x2=map_block[index2].poly.bx;
        y2=map_block[index2].poly.by;
        z2=map_block[index2].poly.bz;
        dist=(SLONG)(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2)));
        return(dist);
    }
    return(MAX_PATH_LONG);
}


SLONG   find_map_block_over_line(SLONG no1,SLONG no2,SLONG *x1,SLONG *y1,SLONG *z1,SLONG *x2,SLONG *y2,SLONG *z2)
{
    SLONG   i,index,pn;
    
    pn=map_block[no1].poly.pn;
    index=-1;
    for(i=0;i<pn;i++)
    {
        if(map_block[no1].adj[i]==no2)
        {
            index=i;
            break;
        }
    }
    if(index>=0)
    {
        *x1=map_block[no1].poly.px[index];
        *y1=map_block[no1].poly.py[index];
        *z1=map_block[no1].poly.pz[index];
        *x2=map_block[no1].poly.px[(index+1)%pn];
        *y2=map_block[no1].poly.py[(index+1)%pn];
        *z2=map_block[no1].poly.pz[(index+1)%pn];
        return(TTN_OK);
    }
    return(TTN_NOT_OK);
}


SLONG   find_map_block_cover_point(SLONG x,SLONG y,SLONG *height)
{
    SLONG i,find;
    SLONG height2;
    
    (*height) = -99999999;
    find = -1;
    for(i=0;i<map_block_max;i++)
    {
        if( TRUE == D3_is_point_in_poly_cover(&(map_block[i].poly),x,y) )
        {
            height2 = D3_compute_height_point_poly_cover(&(map_block[i].poly),x,y);
            if(height2 > (*height) )
            {
                (*height) = height2;
                find = i;
            }
        }
    }
    return(find);
}


SLONG   redraw_map_block_info(SLONG no,BMP *bit_map)
{
    SLONG   i;
    SLONG   bno,disp_x,disp_y,pn,type;
    USTR    temp[256];
    
    if(map_block_max<=0) return TTN_NOT_OK;
    disp_x=32;
    disp_y=16;
    bno=no;
    print16(0,0,(USTR *)"~C0~O3",PEST_PUT,bit_map);
    if(bno>=0 && bno<map_block_max)
    {
        sprintf((char *)print_rec,"BLOCK NO : %d",bno);
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        type=map_block[bno].type;
        sprintf((char *)print_rec,"TYPE     : %s",get_map_block_type_string(type));
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        sprintf((char *)print_rec,"CENTER   : %d , %d",map_block[bno].poly.bx,map_block[bno].poly.by);
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        sprintf((char *)print_rec,"POLY NUM : %d",map_block[bno].poly.pn);
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        pn=map_block[bno].poly.pn;
        strcpy((char *)print_rec, "POLY  PX : ");
        for(i=0;i<pn;i++)
        {
            sprintf((char *)temp,"%9d",map_block[bno].poly.px[i]);
            strcat((char *)print_rec,(const char *)temp);
            if(i!=pn-1)
                strcat((char *)print_rec," , ");
        }
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        strcpy((char *)print_rec, "POLY  PY : ");
        for(i=0;i<pn;i++)
        {
            sprintf((char *)temp,"%9d",map_block[bno].poly.py[i]);
            strcat((char *)print_rec,(const char *)temp);
            if(i!=pn-1)
                strcat((char *)print_rec," , ");
        }
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        strcpy((char *)print_rec, "POLY  PZ : ");
        for(i=0;i<pn;i++)
        {
            sprintf((char *)temp,"%9d",map_block[bno].poly.pz[i]);
            strcat((char *)print_rec,(const char *)temp);
            if(i!=pn-1)
                strcat((char *)print_rec," , ");
        }
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        strcpy((char *)print_rec, "ADJOINT  : ");
        for(i=0;i<pn;i++)
        {
            sprintf((char *)temp,"%9d",map_block[bno].adj[i]);
            strcat((char *)print_rec,(const char *)temp);
            if(i!=pn-1)
                strcat((char *)print_rec," , ");
        }
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
        strcpy((char *)print_rec, "DISTANCE : ");
        for(i=0;i<pn;i++)
        {
            sprintf((char *)temp,"%9d",map_block[bno].dist[i]);
            strcat((char *)print_rec,(const char *)temp);
            if(i!=pn-1)
                strcat((char *)print_rec," , ");
        }
        print16(disp_x,disp_y,(USTR *)print_rec,PEST_PUT,bit_map);
        disp_y+=20;
    }
    print16(0,0,(USTR *)"~C0~O0",PEST_PUT,bit_map);
    disp_y+=20;
    return(TTN_OK);
}


SLONG   find_map_block_intersect_point(SLONG *xx,SLONG *yy,SLONG *zz,SLONG no,SLONG no1)
{
    static  SLONG   x,y,z;
    SLONG   x1,y1,z1,x2,y2,z2;
    double  dis1,dis2;
    SLONG   find,n;
    SLONG   i;
    SLONG   size;
    
    x=*xx;
    y=*yy;
    size=MIN_PATH_WIDTH;
    find=-1;
    n=map_block[no].poly.pn;
    for(i=0;i<n;i++)
    {
        if(map_block[no].adj[i]==no1)
        {
            find=i;
            break;
        }
    }
    if(find>=0)
    {
        x1=map_block[no].poly.px[find];
        y1=map_block[no].poly.py[find];
        z1=map_block[no].poly.pz[find];
        x2=map_block[no].poly.px[(find+1)%n];
        y2=map_block[no].poly.py[(find+1)%n];
        z2=map_block[no].poly.pz[(find+1)%n];
        dis1=(x1-x)*(x1-x)+(y1-y)*(y1-y)+(z1-z)*(z1-z);
        dis2=(x2-x)*(x2-x)+(y2-y)*(y2-y)+(z2-z)*(z2-z);
        if(dis1<dis2)
            D3_seek_space_point_segment(x1,y1,z1,x2,y2,z2,&x,&y,&z,size);
        else
            D3_seek_space_point_segment(x2,y2,z1,x1,y1,z2,&x,&y,&z,size);
    }
    *xx=x;
    *yy=y;
    *zz=z;
    return(TTN_OK);
}


SLONG   find_map_specific_block_point(SLONG block_index,SLONG dist,SLONG *x,SLONG *y,SLONG *point_index)
{
   static  xx,yy;
   SLONG   j,pn,tx,ty;
   
   xx=*x;
   yy=*y;
   if((block_index>=0)&&(block_index<map_block_max))
   {
      pn=map_block[block_index].poly.pn;
      for(j=0;j<pn;j++)
      {
         tx=map_block[block_index].poly.px[j];
         ty=map_block[block_index].poly.py[j];
         if( abs(tx-xx)<dist && abs(ty-yy)<dist )
         {
            *x=tx;
            *y=ty;
            *point_index=j;
            return(TTN_OK);
         }
      }
   }
   *point_index=0;
   return(TTN_NOT_OK);
}


SLONG   find_point_of_map_block_cover(SLONG dist,SLONG *x,SLONG *y,SLONG *block_index,SLONG *point_index)
{
   static  xx,yy;
   SLONG   i,j,pn,tx,ty;
   
   xx=*x;
   yy=*y;
   for(i=0;i<map_block_max;i++)
   {
      pn=map_block[i].poly.pn;
      for(j=0;j<pn;j++)
      {
         tx=map_block[i].poly.px[j];
         ty=map_block[i].poly.py[j]-map_block[i].poly.pz[j];
         if(abs(tx-xx)<dist && abs(ty-yy)<dist)
         {
            *x=tx;
            *y=ty;
            *block_index=i;
            *point_index=j;
            return(TTN_OK);
         }
      }
   }
   *block_index=-1;
   *point_index=0;
   return(TTN_NOT_OK);
}


SLONG   seek_map_point_block_height(SLONG x,SLONG y,SLONG *hh)
{
   SLONG   i,max_height,height,side,find;
   SLONG   ret;
   
   max_height=-999999;
   find=0;
   ret = TTN_NOT_OK;
   for(i=0;i<map_block_max;i++)
   {
      if( TRUE == D3_is_point_in_poly_cover(&(map_block[i].poly),x,y))
      {
         height = D3_compute_height_point_poly_cover(&(map_block[i].poly),x,y);
         if(height>max_height)
         {
            max_height=height;
            find=1;
            ret=TTN_OK;
         }
      }
      else
      {
         if( TRUE == D3_is_point_in_poly_foreside(&(map_block[i].poly),x,y,&side) )
         {
            height = D3_compute_height_point_poly_foreside(&(map_block[i].poly),side,x,y);
            if(height>max_height)
            {
               max_height=height;
               find=1;
               ret=TTN_NOT_OK;
            }
         }
      }
   }
   *hh = (find) ? max_height : max(max_height,0);
   return(ret);
}
