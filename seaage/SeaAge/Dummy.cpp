//dummy.cpp
#if 0   /////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------
/*
static  void    apply_character_quick_to_player(SLONG index, TPOS_CHARACTER_QUICK quick)
{
    //ITEM_ESSE   ie;
    
    LOCK_CHARACTER(index);
	//���e�w�g��o�F ZONE ���Ҧ����a�M NPC ����ơA�ñq�Ӫ��D�F�� NPC �� SHAPE_TYPE 
	//�O���v�٬O���a�A�ҥH�A�o�̪����]�m���k��ޯ�Y�i(�Ө禡�����|�Ϥ����a�M���v)�C
    set_player_rhand_magic(index, (SLONG)quick.dSkillA);
    set_player_rhand_magic(index, (SLONG)quick.dSkillB);

	// Jack. [1/2/2003]
    //ie.base = (SLONG)quick.dItemA;
    //set_player_sash_item(index, 0, ie);
    //ie.base = (SLONG)quick.dItemB;
    //set_player_sash_item(index, 1, ie);
    //ie.base = (SLONG)quick.dItemC;
    //set_player_sash_item(index, 2, ie);
    //ie.base = (SLONG)quick.dItemD;
    //set_player_sash_item(index, 3, ie);
    UNLOCK_CHARACTER(index);
}

*/
void    sync_heartbeat_data(DWORD dwTimes)
{
    DWORD   dwNextSyncTimes;
    DWORD   dwBeats, dwPeriod, dwMsPerBeat;

    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return;

    LOCK_HEARTBEAT();
    if(heartbeat_data.flags & HBF_INIT_HEARTBEAT)
    {
        //�w�p SERVER ���U���߸�
        dwNextSyncTimes = (dwTimes - heartbeat_data.dwSyncTimes) + dwTimes;

        //
        if(dwNextSyncTimes > heartbeat_data.dwBeatTimes)
        {
            //��U�@���P�B, �ۤv�ݭn�߸�������.
            dwBeats = dwNextSyncTimes - heartbeat_data.dwBeatTimes;
            
            //�ɶ����j
            dwPeriod = heartbeat_data.dwMsPerBeat * (heartbeat_data.dwBeatTimes - heartbeat_data.dwLastTimes);
            
            if(dwBeats > 0 && dwPeriod > 0)
            {
                dwMsPerBeat = dwPeriod / dwBeats;
                if(dwMsPerBeat < 25)
                    dwMsPerBeat = 25;   //�̧֤��W�L�C��40��.
            }
            else
            {
                dwMsPerBeat = 50;
            }
            
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = dwMsPerBeat;
        }
        //�ۤv���߸��ӧ�, �H�P��U���P�B�ɦۤv�����ݭn, �ҥH, �ݭn�C�U��.
        else if(dwNextSyncTimes < heartbeat_data.dwBeatTimes)
        {
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = 100;   //�T�w�C���C��10��.
        }
    }
    else
    {
        heartbeat_data.dwLastTimes = dwTimes;
        heartbeat_data.dwBeatTimes = dwTimes;
        heartbeat_data.dwSyncTimes = dwTimes;
        heartbeat_data.dwMsPerBeat = 50;
        heartbeat_data.flags |= HBF_INIT_HEARTBEAT;
    }
    UNLOCK_HEARTBEAT();
}
// Jack, New version [1/14/2003]
static	SLONG   client_handle_change_npc_doing(DWORD wParam)
{
	TPOS_EVENT_GETCHANGENPCDOING *info = (TPOS_EVENT_GETCHANGENPCDOING *)wParam;
    SLONG   src_attack_x, src_attack_y;
    
    switch(info->DoingKind)
    {
    case DOING_KIND_IDLE:   //�ݾ�
        {
            switch(info->d4)
            {
            case 0: //do nothing
                //LOCK_CHARACTER(info->Index);
                change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, 0, info->d5);
                //UNLOCK_CHARACTER(info->Index);
                break;

            case 1: //init rhand magic state
                //LOCK_CHARACTER(info->Index);;
                change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, 0, info->d5);
                InitCharacterRightSkillState(info->Index);
                //UNLOCK_CHARACTER(info->Index);;
                break;
            }
        }
        break;
        
    case DOING_KIND_BEATED:         //�Q��
    case DOING_KIND_DOWN_AND_OUT:   //�Q����
        //LOCK_CHARACTER(info->Index);
        SetCharacterHp(info->Index, (UHINT)info->d2);
        src_attack_x = info->d3;
        src_attack_y = info->d4;
        change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, 0, src_attack_x, src_attack_y, info->d5);
        //UNLOCK_CHARACTER(info->Index);
        break;

    case DOING_KIND_DEAD:   //�Q����
        //LOCK_CHARACTER(info->Index);
        SetCharacterHp(info->Index, 0);
        SetCharacterDeadTicks(info->Index, (UHINT)info->d2);
        src_attack_x = info->d3;
        src_attack_y = info->d4;
        change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, 0, src_attack_x, src_attack_y, info->d5);
        //UNLOCK_CHARACTER(info->Index);
        break;

    case DOING_KIND_SPOWER: //�W�O
        //LOCK_CHARACTER(info->Index);
        change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, info->d4, info->d5);
        SetCharacterRightHandMagicStartSpower(info->Index);
        //UNLOCK_CHARACTER(info->Index);
        break;

    case DOING_KIND_CLASH:  //�ļ�
        //LOCK_CHARACTER(info->Index);
        change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, info->d4, info->d5);
        InitCharacterRightSkillState(info->Index);
        //UNLOCK_CHARACTER(info->Index);
        break;
        
    default:
        //LOCK_CHARACTER(0);
        change_npc_doing(info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, info->d4, info->d5);
        //UNLOCK_CHARACTER(0);
        break;
    }
    
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CHANGE_NPC_DOING(%d, %d, %d, %d, %d, %d, %d, %d)",
        info->Index, info->DoingKind, info->DoingStep, info->d1, info->d2, info->d3, info->d4, info->d5);
#endif//DEBUG_MSG
    
    return  0;
}

void    set_mouse_hand_item(TPOS_ITEM *pit)
{
	SLONG	NowBaseID, NewBaseID;

	NowBaseID = GetItemBaseID(&mouse_hand.item);
	NewBaseID = GetItemBaseID(pit);
    if(NowBaseID == NewBaseID)
        return;

    mouse_hand.item = *pit;

	//
	//link item image with mouse
	//
    if(! IsItemNone(pit))
    {
        CAKE_FRAME_ANI  *cfa;
        SLONG   icon_index;
        SLONG   hrooms, vrooms, item_xl, item_yl;

        icon_index = GetItemIconIndex(pit);
        cfa = get_item_icon_cfa(icon_index);
        get_item_icon_size(icon_index, &hrooms, &vrooms, &item_xl, &item_yl);
        make_mouse_image_cursor(5, cfa, 1);
        set_mouse_spot(5, item_xl/2, item_yl/2);
        set_mouse_cursor(5);
    }
    else    //unlink item image from mouse
    {
        set_mouse_cursor(MOUSE_IMAGE_ARROW);
    }
}


void    set_mouse_hand_item(TPOS_ITEM *pit);

SLONG   get_map_object_poly(SLONG object_index, POLY **poly)
{
    SLONG   flag, id, object_type;

    flag = map_object[object_index].flag;
    if(!(flag & MOBJ_ACTIVE))
        return  TTN_NOT_OK;

    id = map_object[object_index].id;
    object_type = flag & MOBJ_TYPES;

    switch(object_type)
    {
    case MOBJ_HOUSE_OBJECT:
        {/* this object is house object */
            
            HOUSE_OBJECT *house_object = NULL;
            SLONG   house_index, house_no, house_object_index;
            
            house_index = (id & 0xffff0000) >> 16;
            house_object_index = (id & 0xffff) - 1;
            house_no = map_house[house_index].no;
            house_object = get_house_object(house_no, house_object_index);
            if(house_object)
            {
                *poly = house_object->poly;
                
                return  TTN_OK;
            }
        }
        break;

    case MOBJ_HOUSE_ROOF:
        {/* this object is house roof */
            
            HOUSE_ROOF *house_roof = NULL;
            SLONG   house_index, house_no;
            
            house_index = (id & 0xffff0000) >> 16;
            house_no = map_house[house_index].no;
            house_roof = get_house_roof(house_no);
            if(house_roof)
            {
                *poly = house_roof->poly;
                
                return  TTN_OK;
            }
        }
        break;

    case MOBJ_SIMPLE:
    case MOBJ_DYNAMIC:
    case MOBJ_FIXED:
    case MOBJ_NPC:
    case MOBJ_MAGIC:
        {/* this object is a library object */
            
            CAKE_FRAME_ANI *cfa = NULL;
            CAKE_FRAME  * cf = NULL;
            
            if( id != INVALID_OBJECT_ID && flag )
            {
                cfa = get_map_object_image(id, map_object[object_index].frame);
                if(cfa) cf = cfa->cake_frame;
                if(cf) 
                {   
                    *poly = cf->poly;
                    
                    return  TTN_OK;
                }
            }
        }
        break;
    }

    return  TTN_NOT_OK;
}

//extern  SLONG   get_map_object_poly(SLONG object_index, POLY **poly);


/*
SLONG   add_map_simple_object(SLONG id,SLONG px,SLONG py,SLONG pz,SLONG effect,SLONG change_tick)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_SIMPLE;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].change_tick = change_tick;
        map_object[index].now_tick = 0;
        map_object[index].effect = effect;
        map_object[index].frame = 0;
        
        add_reference_for_map_object_image(id);

        if(index >= map_object_max)
            map_object_max = index + 1;
    }
    return index;
}
*/


//-------------------------------------------------------------------------------------------
SLONG   get_map_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
    SLONG   object_type;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

    switch(object_type)
    {
    case MOBJ_HOUSE_OBJECT:
        {/* this object is house object */
            
            HOUSE_OBJECT *house_object = NULL;
            SLONG   house_index, house_no, house_object_index;
            
            house_index = (id & 0xffff0000) >> 16;
            house_object_index = (id & 0xffff) - 1;
            house_no = map_house[house_index].no;
            house_object = get_house_object(house_no, house_object_index);
            if(house_object)
            {
                *object_flag = flag;
                *sx = -map_data.map_sx + px + house_object->fx;
                *sy = -map_data.map_sy + (py - pz) + house_object->fy;
                *ex = *sx + house_object->rle->w;
                *ey = *sy + house_object->rle->h;
                *poly = house_object->poly;
                
                return  TTN_OK;
            }
        }
        break;

    case MOBJ_HOUSE_ROOF:
        {/* this object is house roof */
            
            HOUSE_ROOF *house_roof = NULL;
            SLONG   house_index, house_no;
            
            house_index = (id & 0xffff0000) >> 16;
            house_no = map_house[house_index].no;
            house_roof = get_house_roof(house_no);
            if(house_roof)
            {
                *object_flag = flag;
                *sx = -map_data.map_sx + px + house_roof->fx;
                *sy = -map_data.map_sy + (py - pz) + house_roof->fy;
                *ex = *sx + house_roof->rla->w;
                *ey = *sy + house_roof->rla->h;
                *poly = house_roof->poly;
                
                return  TTN_OK;
            }
        }
        break;

    case MOBJ_SIMPLE:
    case MOBJ_DYNAMIC:
    case MOBJ_FIXED:
    case MOBJ_NPC:
    case MOBJ_MAGIC:
        {/* this object is a library object */
            
            CAKE_FRAME_ANI *cfa = NULL;
            CAKE_FRAME  * cf = NULL;
            RLE*    rle = NULL;
            POLY*   pl = NULL;
            SLONG   ox, oy;
            
            if( id != INVALID_OBJECT_ID && flag )
            {
                cfa = get_map_object_image(id, map_object[object_index].frame);
                if(cfa) cf = cfa->cake_frame;
                if(cf) 
                {   
                    rle = cf->rle;
                    pl = cf->poly;
                }
                if(rle && pl)
                {
                    // we suppose all frame's polys have the same barycenter position,
                    // so the offset x/y is just the following values...
                    ox = -cf->poly_rx;
                    oy = -cf->poly_ry;
                    
                    *object_flag = flag;
                    *sx = - map_data.map_sx + ox + px;
                    *sy = - map_data.map_sy + oy + (py - pz);
                    *ex = *sx + rle->w;
                    *ey = *sy + rle->h;
                    *poly = pl;
                    
                    return  TTN_OK;
                }
            }
        }
        break;
    }
    return  TTN_NOT_OK;
}


void    redraw_one_map_object(SLONG index, SLONG ext_flag, BMP *bitmap)
{
    SLONG   sx, sy;
    CAKE_FRAME_ANI *cfa = NULL;
    CAKE_FRAME *cf = NULL;
    RLE *rle = NULL;

    if(! (map_object[index].flag & MOBJ_ACTIVE) )return;

    cfa = get_map_object_image(map_object[index].id, map_object[index].frame);
    if(cfa) cf=cfa->cake_frame;
    if(cf) { rle=cf->rle; }
    if(rle)
    {
        // we suppose all frame's polys have the same barycenter position,
        // so the offset x/y is just the following values...
        sx = -cf->poly_rx + map_object[index].px - map_data.map_sx;
        sy = -cf->poly_ry + map_object[index].py - map_object[index].pz - map_data.map_sy;
        put_rle(sx,sy,rle,bitmap);
        // Jack,  [16:13,9/27/2002]
        /*
        if(ext_flag<0)
        {
            mesh_put_rle(sx,sy,rle,bitmap);
        }
        else
        {
            put_rle(sx,sy,rle,bitmap);
        }
        */
    }
}


void    redraw_one_map_house_roof(SLONG obj_index, SLONG ext_flag, BMP *bitmap)
{
    HOUSE_ROOF * house_roof = NULL;
    RLA *   rla = NULL;
    SLONG   id, sx, sy, house_index, house_no, alpha;

    id = map_object[obj_index].id;

    house_index = (id & 0xffff0000) >> 16;
    house_no = map_house[house_index].no;
    house_roof = get_house_roof(house_no);
    rla = house_roof->rla;

    if(rla)
    {
        sx = map_object[obj_index].px - map_data.map_sx + house_roof->fx;
        sy = map_object[obj_index].py - map_object[obj_index].pz - map_data.map_sy + house_roof->fy;

        // Jack,  [16:16,9/27/2002]
        /*
        if(ext_flag<0)
        {
            mesh_put_rla(sx, sy, rla, bitmap);
        }
        else
        */
        {
            // we use now_tick for it's alpha value.
            alpha = map_object[obj_index].now_tick;
            switch(alpha)
            {
            case 0x00:
                break;
            case 0xff:
                put_rla(sx, sy, rla, bitmap);
                break;
            default:
                alpha_put_rla(sx, sy, rla, bitmap, alpha);
                break;
            }
        }
    }
}



extern  SLONG   change_map_object_id(SLONG index, SLONG new_id);
//

SLONG   change_map_object_id(SLONG index, SLONG new_id)
{
    if(map_object[index].id != new_id)
    {
		// Jack, TODO [1/24/2003]
        if(map_object[index].id != INVALID_OBJECT_ID)
            dec_reference_for_map_object_image(map_object[index].id);
        add_reference_for_map_object_image(new_id);

        map_object[index].id = new_id;
        map_object[index].frame = 0;
        map_object[index].now_tick = 0;

        return  TTN_OK;
    }
    return  TTN_NOT_OK;
}


void    redraw_one_map_magic_object( SLONG object_index, SLONG ext_flag, BMP *bitmap )
{
    SLONG   id;
    SLONG   px,py,pz;
    SLONG   effect;
    SLONG   frame;
    SLONG   sx,sy,ox,oy,xl,yl;
    SLONG   flag;
    CAKE_FRAME_ANI *cfa=NULL;
    CAKE_FRAME *cf=NULL;
    RLE *   rle=NULL;
    RLE *   headrle=NULL;
    SLONG   part_index;

    POLY *  pl=NULL;
    SLONG   show_image_type;
    const SLONG draw_poly_flags = PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS 
        | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_ZHEIGHT ;

    flag = map_object[object_index].flag;
    if(! (flag & MOBJ_ACTIVE) )return;

    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    effect = map_object[object_index].effect;
    frame = map_object[object_index].frame;
    part_index = map_object[object_index].magic_part_no;

    cfa=get_map_object_image(id,0);
    if(cfa) cf=cfa->cake_frame;
    if(cf) headrle=cf->rle;
    
    cfa = get_map_object_image(id,frame);
    
    rle=NULL;

    if(cfa) cf=cfa->cake_frame;
    if(cf) { rle=cf->rle; pl=cf->poly; }
    if(rle)
    {
        // we suppose all frame's polys have the same barycenter position,
        // so the offset x/y is just the following values...
        ox=-cf->poly_rx;
        oy=-cf->poly_ry;
        
        xl=rle->w;
        yl=rle->h;
        
        sx=ox+px-map_data.map_sx;
        sy=oy+py-pz-map_data.map_sy;

        // flags effect ---------------------------------------------------
        if( (flag & MOBJ_MARKED) && (headrle) )
        {
            put_ellipse(px-map_data.map_sx,py-pz-map_data.map_sy,headrle->w/2+2,headrle->w/4+1,SYSTEM_GREEN,bitmap);
        }

        // show auto shadow -----------------------------------------------
        if(effect & OBJECT_SHADOW)
        {
        }

        // show image ------------------------------------------------
        show_image_type = effect & OBJECT_IMAGE_MASK;

        // Jack,  [16:14,9/27/2002]
        /*
        if(ext_flag<0)
        {
            mesh_put_rle(sx,sy,rle,bitmap);
        }
        else
        */
        {
            switch(show_image_type)
            {
            case OBJECT_NORMAL_IMAGE:
                // Jack. [14:44,9/19/2002]
                //merge_put_rle(sx, sy, rle, bitmap);
                put_rle(sx,sy,rle,bitmap);
                //filter_put_rle(sx,sy,rle,bitmap,128);
                //additive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MASK_IMAGE:
                mesh_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MASK_EDGE_IMAGE:
                // we set default mask_color
                mask_edge_put_rle(sx,sy,SYSTEM_YELLOW,rle,bitmap);
                break;
            case OBJECT_GRAY_IMAGE:
                gray_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_GRAY_EDGE_IMAGE:
                gray_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_ALFA_IMAGE:
                // we set alpha=30
                alpha_put_rle(sx,sy,rle,bitmap,30);
                break;
            case OBJECT_ALFA_EDGE_IMAGE:
                // we set alpha=30
                alpha_edge_put_rle(sx,sy,rle,bitmap,30);
                break;
            case OBJECT_ADDITIVE_IMAGE:
                additive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_ADDITIVE_EDGE_IMAGE:
                additive_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SUBTRACTIVE_IMAGE:
                subtractive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SUBTRACTIVE_EDGE_IMAGE:
                subtractive_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MINIMUM_IMAGE:
                minimum_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MINIMUM_EDGE_IMAGE:
                minimum_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MAXIMUM_IMAGE:
                maximum_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MAXIMUM_EDGE_IMAGE:
                maximum_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_HALF_IMAGE:
                half_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_HALF_EDGE_IMAGE:
                half_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MESH_IMAGE:
                mesh_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SCALE_IMAGE:
                // for speed,we dont support this...
                //scale_put_rle(SLONG sx,SLONG sy,SLONG scalex,SLONG scaley,RLE *src_rle,BMP *dest_bmp);
                break;
            case OBJECT_LIGHT_IMAGE:
                //light_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_RED_IMAGE:
                red_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_GREEN_IMAGE:
                green_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_BLUE_IMAGE:
                blue_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_YELLOW_IMAGE:
                yellow_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_MERGE_IMAGE:
                merge_put_rle(sx, sy, rle, bitmap);
                break;
            default:
                break;
            }
        }
        // show poly -------------------------------------------------------
#ifdef  DEBUG
        if(effect & OBJECT_POLY)
        {
            D3_draw_poly(px-map_data.map_sx,py-map_data.map_sy,pz,draw_poly_flags,pl,bitmap);
        }
#endif//DEBUG
        // show box --------------------------------------------------------
        if(effect & OBJECT_BOX)
        {
        }
        //------------------------------------------------------------------

        //------------------------------------------------------------------

#ifdef  DEBUG
        //if(ext_flag)
        if(ext_flag<0)
        {
            sprintf((char *)print_rec,"~O3~C0#%d(H%d)~C0~O0",abs(ext_flag),pz);
            print16(px-map_data.map_sx,py-map_data.map_sy-pz,(USTR *)print_rec,PEST_PUT,bitmap);
        }
#endif//DEBUG

    }

#ifdef  DEBUG
    /*{
        SLONG   part_dest_x, part_dest_y, part_dest_z;
        SLONG   part_orig_x, part_orig_y, part_orig_z;

        LOCK_MAGIC(0);
        part_orig_x = magic_part[part_index].orig_x;
        part_orig_y = magic_part[part_index].orig_y;
        part_orig_z = magic_part[part_index].orig_z;
        part_dest_x = magic_part[part_index].dest_x;
        part_dest_y = magic_part[part_index].dest_y;
        part_dest_z = magic_part[part_index].dest_z;
        UNLOCK_MAGIC(0);

        put_line( part_orig_x - map_data.map_sx, part_orig_y - map_data.map_sy,
            part_dest_x - map_data.map_sx, part_dest_y - map_data.map_sy,
            SYSTEM_PINK, bitmap);
    }*/
#endif//DEBUG

}


void    redraw_one_map_magic_object( SLONG object_index, SLONG ext_flag, BMP *bitmap );

SLONG   del_map_object(SLONG index)
{
    SLONG   id, flag, type;

    if( (index>=0) && (index<map_object_max) )
    {
        flag = map_object[index].flag;
        id = map_object[index].id;
        type = map_object[index].flag & MOBJ_TYPES;

        switch(type)
        {
        case MOBJ_HOUSE_OBJECT:
            {/* this object is house object */
                
                //only set it's flag to 0, and we will free image memory at other place.
                map_object[index].flag = 0;

				// Jack, add here. [1/23/2003]
                map_object[index].id = INVALID_OBJECT_ID;
            }
            break;
        case MOBJ_HOUSE_ROOF:
            {/* this object is house roof */
                
                //only set it's flag to 0, and we will free image memory at other place.
                map_object[index].flag = 0;

				// Jack, add here. [1/23/2003]
                map_object[index].id = INVALID_OBJECT_ID;
            }
            break;
        default:
            {/* this object is normal object */
                
                if(id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(id);
                }
                map_object[index].flag = 0;
                map_object[index].id = INVALID_OBJECT_ID;
            }
            break;
        }
    }
    return TTN_OK;
}


SLONG   add_map_npc_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG npc_no)
{
    SLONG   object_index;

    object_index = get_usable_map_object();
    if(object_index >= 0)
    {
        map_object[object_index].flag = MOBJ_ACTIVE | MOBJ_NPC;
        map_object[object_index].id = id;
        map_object[object_index].px = px;
        map_object[object_index].py = py;
        map_object[object_index].pz = pz;
        map_object[object_index].npc_no = npc_no;

        map_object[object_index].effect = OBJECT_NORMAL_IMAGE;
        map_object[object_index].frame = 0;
        
        add_reference_for_map_object_image(id);

        if(object_index >= map_object_max)
            map_object_max = object_index + 1;
    }
    return object_index;
}


SLONG   add_map_magic_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG magic_part_no)
{
    SLONG   object_index;

    object_index = get_usable_map_object();
    if(object_index >= 0)
    {
        map_object[object_index].flag = MOBJ_ACTIVE | MOBJ_MAGIC;
        map_object[object_index].id = id;
        map_object[object_index].px = px;
        map_object[object_index].py = py;
        map_object[object_index].pz = pz;
        map_object[object_index].magic_part_no = magic_part_no;

        map_object[object_index].effect = effect;
        map_object[object_index].frame = 0;
        
        add_reference_for_map_object_image(id);

        if(object_index >= map_object_max)
            map_object_max = object_index + 1;
    }
    return object_index;
}


            flag = map_object[i].flag;
            if(flag & MOBJ_ACTIVE)
            {
                object_type = flag & MOBJ_TYPES;
                
                switch(object_type)
                {
                case MOBJ_SIMPLE:   //simple map objects, only one frame.
                    break;
                case MOBJ_DYNAMIC:  //multiframes dynamic map objects.
                    {
                        map_object[i].now_tick++;
                        if(map_object[i].now_tick>map_object[i].change_tick)
                        {
                            map_object[i].frame++;
                            if(map_object[i].frame >= GetObjectImageTotalFrames(map_object[i].id))
                                map_object[i].frame=0;
                            map_object[i].now_tick=0;
                        }
                    }
                    break;
                case MOBJ_HOUSE_OBJECT:    //we needn't refresh house object.
                    break;
                    
                case MOBJ_HOUSE_ROOF: //we refresh house roof's alpha.
                    {
                        update_alpha = map_object[i].update_alpha;
                        if(update_alpha > 0)
                        {
                            map_object[i].alpha += 32;
                            if(map_object[i].alpha >= 255)
                                map_object[i].alpha = 255;
                        }
                        else if(update_alpha < 0)
                        {
                            map_object[i].alpha -= 32;
                            if(map_object[i].alpha <= 0)
                                map_object[i].alpha = 0;
                        }
                    }
                    break;
                case MOBJ_NPC: // we will refresh npc objects at other place.
                    break;
                case MOBJ_MAGIC:   // we will refresh magic object at other place.
                    break;
                }
            }

void    redraw_one_map_npc_object(SLONG object_index, SLONG ext_flag, BMP *bitmap)
{
    SLONG   npc_no, flag, id, px, py, pz, effect, frame, alpha;
    SLONG   sx,sy,ox,oy,xl,yl;
    CAKE_FRAME_ANI *cfa=NULL;
    CAKE_FRAME *cf=NULL;
    RLE *rle=NULL;
    POLY *pl=NULL;
    SLONG   foot_state, i;
    SLONG   ext_id, ext_frame;
    CAKE_FRAME_ANI  *ext_cfa = NULL;
    CAKE_FRAME  *ext_cf = NULL;
    RLE *ext_rle = NULL;
    POLY *ext_pl = NULL;
    SLONG   talk_flag;

    npc_no = map_object[object_index].npc_no;
    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    effect = map_object[object_index].effect;
    frame = map_object[object_index].frame;

    if(! (flag & MOBJ_ACTIVE) )return;

    // Jack added. [7/30/2002]
    //add_npc_light(px, py, pz);

    LOCK_CHARACTER(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);
    talk_flag = get_npc_talk_flag(npc_no);
    UNLOCK_CHARACTER(npc_no);
    ext_id = get_npc_show_ext_id(npc_no);
    ext_frame = get_npc_show_ext_frame(npc_no);

    //(1) redraw foot abnormity effect
    //-------------------------------------------------------------------------------------------------
    switch(foot_state)
    {
    case NPC_FOOT_SPEED_STATE_TARDY:
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 4, NPC_MASK_WIDTH / 4 + 2, rgb2hi(200, 0, 0),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 5, NPC_MASK_WIDTH / 4 + 3, rgb2hi(255, 0, 0),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 6, NPC_MASK_WIDTH / 4 + 4 ,rgb2hi(200, 0, 0),bitmap);
        break;
    case NPC_FOOT_SPEED_STATE_TIRED:
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 4, NPC_MASK_WIDTH / 4 + 2, rgb2hi(0, 0, 200),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 5, NPC_MASK_WIDTH / 4 + 3, rgb2hi(0, 0, 255),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 6, NPC_MASK_WIDTH / 4 + 4 ,rgb2hi(0, 0, 200),bitmap);
        break;
    }

    //(2) redraw foot magic effect
    //-------------------------------------------------------------------------------------------------

    //(3) redraw body image
    //-------------------------------------------------------------------------------------------------
    {
        cfa = get_map_object_image(id, frame);
        rle = NULL;
        if( cfa ) cf = cfa->cake_frame;
        if( cf )  { rle = cf->rle; pl = cf->poly; }
        if( rle )
        {
            // we suppose all frame's polys have the same barycenter position,
            // so the offset x/y is just the following values...
            ox = -cf->poly_rx;
            oy = -cf->poly_ry;
            xl = rle->w;
            yl = rle->h;
            sx = ox + px - map_data.map_sx;
            sy = oy + py - pz - map_data.map_sy;

            /*
            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
				if(mouse_hand.point_kind == RT_NPC && mouse_hand.point_no == npc_no)
				{
                    put_ellipse(px-map_data.map_sx + 1, py-pz-map_data.map_sy + 1,
                        NPC_MASK_WIDTH / 3 + 2, NPC_MASK_WIDTH / 6 + 1 ,SYSTEM_DARK1,bitmap);
                    put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
                        NPC_MASK_WIDTH / 3 + 2, NPC_MASK_WIDTH / 6 + 1 ,SYSTEM_RED,bitmap);
				}
            }
            */

            //show body image
            // Jack,  [16:14,9/27/2002]
            /*
            if( ext_flag < 0 )
            {
#ifdef  DEBUG
                sprintf((char *)print_rec,"~O3~C0#%d(H%d)~C0~O0",abs(ext_flag),pz);
                print16(px-map_data.map_sx,py-map_data.map_sy-pz,(USTR *)print_rec,PEST_PUT,bitmap);
#endif//DEBUG
                mesh_put_rle(sx,sy,rle,bitmap);
            }
            else
            */
            {
                if(npc_show[npc_no].with_shadow)
                {
                    for(i=MAX_SHOW_SHADOWS-1; i>=0; i--)
                    {
                        blue_alpha_put_rle(sx + npc_show[npc_no].shadow_x[i] - px,
                            sy + npc_show[npc_no].shadow_y[i] - py, rle, bitmap, 192 - 24 * i);
                    }
                    put_rle(sx,sy,rle,bitmap);
                }
                else
                {
                    switch(effect & OBJECT_IMAGE_MASK)
                    {
                    case OBJECT_NORMAL_IMAGE:
                        put_rle(sx,sy,rle,bitmap);
                        break;
                    case OBJECT_ALFA_IMAGE:
                        alpha = (effect & OBJECT_ALPHA_MASK) >> 8;
                        alpha_put_rle(sx, sy, rle, bitmap, alpha);
                        break;
                    }
                }
            }

            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
				if(mouse_hand.point_kind == RT_NPC && mouse_hand.point_no == npc_no)
				{
					mask_put_rle_edge(sx, sy, SYSTEM_YELLOW, rle, bitmap);
				}
            }

            //update game_range
            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
                game_range.add( px - map_data.map_sx - NPC_MASK_WIDTH/2, py - pz - map_data.map_sy - NPC_MASK_HEIGHT,
                    NPC_MASK_WIDTH, NPC_MASK_HEIGHT, RT_NPC, npc_no );
            }

#ifdef  DEBUG
            const SLONG draw_poly_flags = PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS 
                | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_ZHEIGHT ;
            
            if(effect & OBJECT_POLY)
            {
                D3_draw_poly(px-map_data.map_sx,py-map_data.map_sy,pz,draw_poly_flags,pl,bitmap);
            }
#endif//DEBUG
        }
    }

    //(3) redraw body ext image
    //-------------------------------------------------------------------------------------------------
    {
        if(ext_id != INVALID_OBJECT_ID)
        {
            ext_cfa = get_map_object_image(ext_id, ext_frame);
            ext_rle = NULL;
            if( ext_cfa ) ext_cf = ext_cfa->cake_frame;
            if( ext_cf )  { ext_rle = ext_cf->rle; ext_pl = ext_cf->poly; }
            if( ext_rle )
            {
                // we suppose all frame's polys have the same barycenter position,
                // so the offset x/y is just the following values...
                ox = -ext_cf->poly_rx;
                oy = -ext_cf->poly_ry;
                sx = px - map_data.map_sx + ox;
                sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT * 2 / 4 + oy;
                //put_rle(sx, sy, ext_rle, bitmap);
                additive_put_rle(sx, sy, ext_rle, bitmap);
                //alpha_put_rle(sx, sy, ext_rle, bitmap, 128);
            }
        }
    }

    /*
    // Jack, todo [17:10,10/14/2002]
    //(4) redraw npc's head magic images --------------------------------------------------------------
    if( npc_show[npc_index].head_flag )
    {
        cfa = get_map_object_image( npc_show[npc_index].head_id, npc_show[npc_index].head_frame );
        if( cfa ) cf = cfa->cake_frame;
        if( cf )
        {
            rle = cf->rle;
            if(rle)
            {
                put_rle( -cf->poly_rx + npc_show[npc_index].head_x - map_data.map_sx,
                    -cf->poly_ry + npc_show[npc_index].head_y - npc_show[npc_index].head_z - map_data.map_sy,
                    rle, bitmap);
            }
        }
    }
    */

    //(5) redraw npc's talk or npc's name.
    //-------------------------------------------------------------------------------------------------
    switch(talk_flag)
    {
    case NPC_TALK_IS_DIALOG:
        sx = px - map_data.map_sx;
        sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT - 20;
        LOCK_CHARACTER(npc_no);
        set_npc_talk_position(npc_no, sx, sy);
        add_npc_to_npc_talk_list(npc_no);
        UNLOCK_CHARACTER(npc_no);
        break;
    default:
        sx = px - map_data.map_sx;
        sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT - 20;
        LOCK_CHARACTER(npc_no);
        set_npc_talk_flag(npc_no, NPC_TALK_IS_NAME);
        set_npc_talk_position(npc_no, sx, sy);
        add_npc_to_npc_talk_list(npc_no);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
}

extern  void    redraw_one_map_npc_object(SLONG object_index, SLONG ext_flag, BMP *bitmap);

//extern	SLONG   approach_screen_axis_dir_ex(SLONG dx, SLONG dy, SLONG parts);
//extern	SLONG	approach_screen_axis_degree_dir_ex(SLONG degree, SLONG parts);
//extern	double  compute_ship_r(SLONG v, SLONG veer);
//extern	SLONG   compute_ship_swerve_angle(SLONG x, SLONG y, SLONG dir_degree, SLONG dest_x, SLONG dest_y);
//extern	SLONG   compute_ship_sail_velocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps);
//extern	SLONG   compute_ship_werve_velocity(SLONG v, SLONG vmax, SLONG acc);
//extern	SLONG   is_ship_can_sail_to(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y);
//extern	SLONG   compute_screen_axis_degree(double dx, double dy);
//extern	SLONG	winding_axis_position(SLONG n, SLONG *x, SLONG *y);
//extern	SLONG	winding_attack_axis_position(SLONG n, SLONG *x, SLONG *y);
//
//extern	void    debug_test_shipfunc(void);
/******************************************************************************************************************/
/* ������B�⪺���                                                                                             */
/******************************************************************************************************************/
//
//�\�� : �p�����������ϥΪ��t��(�Ҽ{����[�t��)
//�Ѽ� : SLONG dist         -> ��Z���ؼ��I���Z��.
//       SLONG v            -> ���e���t��.
//       SLONG vmax         -> ����̤j���t��.
//       SLONG acc          -> ����[�t��.
//       SLONG keep_steps   -> ����ɥH�Y�t�ׯ��(����U���t�ק���)���B��.
//�^�� : ����t��.
SLONG   compute_ship_sail_velocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps)
{
    /*
    **  ���]���e�t�׬�v, �̤j�t�׬�vmax, �Z���ؼ��I���Z����dist, �[�t�׬�a, ���F�ؼ��I�ɪ��t�׬�vmin.
    **  �ϨҪ�ܱq�t��0�}�l�B�ʨ쵲���t��0, �åB�Z���������ɪ��L�{�p�U:
    **
    **      S......(�[�t��).....|.......(�ót��)......|....(��t��).........D
    **
    **���ڭ̥��Ҽ{��C�B�ʤ@�B�N�[�t(��t)�@��.
    **
    **  �]��q��e�t�ת��A�}�l��t�����檺�Z����dist0, ����dist0���{�ɴ�t�Z��.
    **  �p���t�{�ɶZ��dist0:
    **      ��q��e�t��v�}�l��t, ��ؼ��I�t�׬�0, �ݭn���ɶ���t0, 
    **          t0 = (vmin - v) / (- a);
    **      �Z��dist0,
    **          dist0 = v * t0 + (-a) * t0 * t0 / 2;
    **
    **�����]��H��e�t�רC�B�� k �B��}�l�[�t(��t)�@��, ���������dist0�p�U:
    **          kdist0 = k * dist0 = k * v * v / a / 2;
    **
    */
    enum {VMIN = 4};
    double  t0, dist0;
    SLONG   kdist0;

    t0 = (double)(VMIN - v) / (double)(-acc);
    dist0 = v * t0 + (-acc) * t0 * t0 / 2;
    kdist0 = (SLONG)(keep_steps * dist0 + 0.5);
    if(dist < kdist0)
    {//��e�Z���p���t�{�ɶZ��(��t��0�ɪ��Z��)��, �}�l��t.
        return  max(v - acc, VMIN);
    }
    else if(dist < kdist0 + v * keep_steps)
    {//�O���ثe�t��, ������Fkeep_steps�B���F�U�@�Ӵ�t�{���I.
        return  v;
    }
    else
    {//�_�h, �@���[�t.
        return  min(v+acc, vmax);
    }
}


//�\�� : �p���b��V���ɭ����ӨϥΪ��t��(�Ҽ{�[�t��).
SLONG   compute_ship_werve_velocity(SLONG v, SLONG vmax, SLONG acc)
{
    return  min(v+acc, vmax);
}


//�\�� : �p�������s�b�|.
double  compute_ship_r(SLONG v, SLONG veer)
{
    /*
    �p��������s���̤p�b�|:
    �]��V���C�B�樫�Z���� s, ���B�M�U�B�������ਤ�� t, �h���s�b�|��:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r;
    r = v / ( 2 * sin(veer * PI / 18000 / 2) );
    return  r;
}


//�\�� : �p����e�ݭn��ʪ�����.
SLONG   compute_ship_swerve_angle(SLONG x, SLONG y, SLONG dir_degree, SLONG veer, SLONG dest_x, SLONG dest_y)
{
    SLONG   dx, dy, dir_dx, dir_dy, delta;
    SLONG   dest_degree, delta_degree, swerve_degree;
    double  sita;

    dx = dest_x - x;
    dy = dest_y - y;
    dest_degree = compute_screen_axis_degree(dx, dy);
    
    sita = dir_degree * PI / 18000;
    dir_dx = (SLONG)(100 * cos(sita));
    dir_dy = (SLONG)(100 * sin(sita));
    delta_degree = D2_nipangle_line_line(0, 0, dir_dx, dir_dy, 0, 0, dx, dy);
    if(delta_degree < veer)
    {
        swerve_degree = dest_degree - dir_degree;
    }
    else
    {
        delta = dir_dx * dy - dir_dy * dx;
        if(delta > 0)
            swerve_degree = veer;
        else
            swerve_degree = -veer;
    }
    return  swerve_degree;
}


//�\�� : �P�_��O�_�i�H��F�ؼ��I.
SLONG   is_ship_can_sail_to(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y)
{
    //���i��F�ϰ�: 
    //�H���e��V�����߶b, ��ⰼ�P�Ӷb�ۤ�, �b�|����̤p���s�b�|����.
    /*
    ��樫������V�B�z:
    �]��V���C�B�樫�Z���� s, ���B�M�U�B�������ਤ�� t, �h���s�b�|��:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r, sita, a1, a2;
    double  x1, y1, x2, y2;
    double  dx, dy, dist1, dist2;

    //�p��������s���̤p�b�|�C
    sita = veer * PI / 18000 / 2;
    r = v / ( 2 * sin(sita) );

    //�p��P��e��V�۫������A�ⰼ���A�����F���A��ΰϰ쪺��߮y�СC
    a1 = (dir_degree + 9000) * PI / 18000;
    a2 = (dir_degree - 9000) * PI / 18000;
    x1 = x + r * cos(a1);
    y1 = y + r * sin(a1);
    x2 = x + r * cos(a2);
    y2 = y + r * sin(a2);

    //�P�_�ؼ��I�O�_��󤣯��F�ϰ�C
    dx = dest_x - x1;
    dy = dest_y - y1;
    dist1 = sqrt(dx * dx + dy * dy);
    if(dist1 < r)
        return  FALSE;
    dx = dest_x - x2;
    dy = dest_y - y2;
    dist2 = sqrt(dx * dx + dy * dy);
    if(dist2 < r)
        return  FALSE;

    return  TRUE;
}


//�\�� : �ھڶb�V�t�Z�p�⨤��(�̹��y�Шt)
//�Ѽ� : double dx       -> X�b(�̹��ۥ��ܥk)�t�Z
//       double dy       -> Y�b(�̹��ۤW�ܤU)�t�Z
//�^�� : ����, �d��[0, 36000).
SLONG   compute_screen_axis_degree(double dx, double dy)
{
    SLONG   degree;

    degree = (SLONG)( atan2(dy, dx) * 36000 / ( 2 * PI ) );
    if(degree < 0)
        degree += 36000;
    return  degree;
}


//�\�� : �ھڶb�V�t�Z�p���V���޸�(�̹��y�Шt)
//�Ѽ� : SLONG  dx      ->  X�b(�̹��ۥ��ܥk)�t�Z
//       SLONG  dy      ->  Y�b(�̹��ۥ��ܥk)�t�Z
//       SLONG  parts   ->  ��P��V�`��.
//�^�� : ��V���ޭ�, �� [0, parts-1].
SLONG   approach_screen_axis_dir_ex(SLONG dx, SLONG dy, SLONG parts)
{
    SLONG   degree, dir, part_degree;

    if(parts <= 0)
        return  0;

    // Get degree between [0, 2 * PI] -> [0, 36000].
    degree = (SLONG)( atan2(dy, dx) * 36000 / ( 2 * PI ) );
    if(degree < 0)
        degree += 36000;

    part_degree = 36000 / parts;

    // Add part_degree/2 to match near degree to dir.
    dir = ( degree + part_degree / 2 ) / part_degree;

    // Over will be set to 0.
    if(dir > parts - 1) dir = 0;

    return  dir;
}


//�\�� : �ھګ̹����׭p���V���޸�(�̹��y�Шt)
//�Ѽ� : SLONG  degree  ->  �̹�����, [0, 36000]
//       SLONG  parts   ->  ��P��V�`��.
//�^�� : ��V���ޭ�, �� [0, parts-1].
SLONG	approach_screen_axis_degree_dir_ex(SLONG degree, SLONG parts)
{
    SLONG   dir, part_degree;

    if(parts <= 0)
        return  0;

    part_degree = 36000 / parts;

    // Add part_degree/2 to match near degree to dir.
    dir = ( degree + part_degree / 2 ) / part_degree;

    // Over will be set to 0.
    if(dir > parts - 1) dir = 0;

    return  dir;
}



//�\�� : �p����Ӥ@�w���ǥѤ��V�~��¶�T�w�I����n�I���۹�y��.
//       �Ӷ��Ǧp�H�U�ϥ�:
//                    |
//                    |
//             24 23 22 21 20
//             19  8  7  6 18
//----------   17  5  0  4 16   --------------------> (X)
//             15  3  2  1 14
//             13 12 11 10  9
//                    |
//                    |    
//                    V (Y)
//
//�Ѽ� : SLONG  n       ->  ��n�I(n = 0,1,2,3,...)
//       SLONG  *x      ->  �s���^���۹�y�Ф� X.
//       SLONG  *y      ->  �s���^���۹�y�Ф� Y.
//�^�� : ���\���^ TTN_OK, �ñN�۹�y�Цs��b (*x, *y) ��.
SLONG	winding_axis_position(SLONG n, SLONG *x, SLONG *y)
{
	SLONG	k, r, under, top, rest;

	//________________________________________________________________
	//(n)
	//                    |
	//                    |
	//             24 23 22 21 20
	//             19  8  7  6 18
	//----------   17  5  0  4 16   --------------------> (X)
	//             15  3  2  1 14
	//             13 12 11 10  9
	//                    |
	//                    |    
	//                    V (Y)
	//                    
	//________________________________________________________________
	//(x)
	//                    |
	//                    |
	//             -2 -1  0  1  2
	//             -2 -1  0  1  2
	//----------   -2 -1  0  1  2   --------------------> (X)
	//             -2 -1  0  1  2
	//             -2 -1  0  1  2
	//                    |
	//                    |    
	//                    V (Y)
	//
	//
	//________________________________________________________________
	//(y)
	//                    |
	//                    |
	//             -2 -2 -2 -2 -2
	//             -1 -1 -1 -1 -1
	//----------    0  0  0  0  0   --------------------> (X)
	//              1  1  1  1  1
	//              2  2  2  2  2
	//                    |
	//                    |    
	//                    V (Y)
	//

	if(n == 0)
	{
		*x = 0;
		*y = 0;
		return	TTN_OK;
	}

	k = (SLONG) sqrt(n);
	k = (k + 1) / 2 * 2 + 1;
	r = k / 2;
	under = (k - 2) * (k - 2);
	top = k * k;

	if(n < under + k)
	{
		*x = under + r - n;
		*y = r;
		return	TTN_OK;
	}

	if( n >= top - k)
	{
		*x = (top-1) - n - r;
		*y = -r;
		return	TTN_OK;
	}

	rest = n - (under + k);
	*x = (rest % 2) ? -r : r;
	*y = (r - 1) - rest / 2;

	return	TTN_OK;
}



//�\�� : �p����Ӥ@�w����¶�T�w�I�Ѥ��V�~����n�ӧ����I���۹�y��.
//       �Ӷ��Ǧp�U�ҥ�:
//                        |                                       
//                        |                                       
//             35  34  33 | 32  31  30                            
//             29  15  14 | 13  12  28                            
//             27  11  02 | 03  10  26                            
//------------------------+---------------------------> (X)       
//             25  09  01 | 00  08  24                                 
//             23  07  06 | 05  04  22                                 
//             21  20  19 | 18  17  16                               
//                        |                                       
//                        |                                        
//                        V (Y)                                        
//
//�Ѽ� : SLONG n        ->  ��n�ӧ����I�I
//       SLONG *x       ->  �s���^���۹�y��x
//       SLONG *y       ->  �s���^���۹�y��y
//�^�� : ���\���^ TTN_OK, �ñN�۹�y�Цs��b (*x, *y) ��.
SLONG	winding_attack_axis_position(SLONG n, SLONG *x, SLONG *y)
{
	SLONG	k, r, under, top, rest;

	//________________________________________________________________
	// N = F(X, Y)                                                    
	//                                                                
	//                                                                
	//                        |                                       
	//                        |                                       
	//             35  34  33 | 32  31  30                            
	//             29  15  14 | 13  12  28                            
	//             27  11  02 | 03  10  26                            
	//------------------------+---------------------------> (X)       
	//             25  09  01 | 00  08  24                                 
	//             23  07  06 | 05  04  22                                 
	//             21  20  19 | 18  17  16                               
	//                        |                                       
	//                        |                                        
	//                        V (Y)                                        
	//________________________________________________________________
	//(x)
	//                                                                
	//                                                                
	//                        |                                       
	//                        |                                       
	//            -5  -3  -1  |  1  3  5                            
	//            -5  -3  -1  |  1  3  5                            
	//            -5  -3  -1  |  1  3  5                            
	//------------------------+---------------------------> (X)       
	//            -5  -3  -1  |  1  3  5                                 
	//            -5  -3  -1  |  1  3  5                                 
	//            -5  -3  -1  |  1  3  5                               
	//                        |                                        
	//                        |                                        
	//                        V (Y)                                        
	//________________________________________________________________
	//(y)
	//                                                                
	//                        |                                       
	//                        |                                       
	//            -5  -5  -5  | -5 -5 -5                            
	//            -3  -3  -3  | -3 -3 -3                            
	//            -1  -1  -1  | -1 -1 -1                            
	//------------------------+---------------------------> (X)       
	//             1   1   1  |  1  1  1                                 
	//             3   3   3  |  3  3  3                                 
	//             5   5   5  |  5  5  5                               
	//                        |                                        
	//                        |                                        
	//                        V (Y)                                        
	//

	if(n < 0)
	{
		*x = 0;
		*y = 0;
		return	TTN_OK;
	}

	//�p�� n ����ĴX�餤
	k = (SLONG) sqrt(n);
	k = k / 2 * 2 + 2;	//�C��(�C)���ƭȪ��Ӽ�(��}���j�p)

	under = (k - 2) * (k - 2);	//�̩��U�@�檺�_�l��
	top = k * k - 1;			//�̳��W�@�檺�̲׭�
	r = k / 2 * 2 - 1;	//�����I��(X/Y)�ƭ�

	//���̩��U�@��
	if(n < under + k)	
	{
		*x = r + (under - n) * 2 ;
		*y = r;
		return	TTN_OK;
	}

	//���̳��W�@��
	if( n > top - k)
	{
		*x = (top - n) * 2 - r;
		*y = -r;
		return	TTN_OK;
	}

	//��󥪥k�ⰼ
	rest = n - (under + k);
	*x = (rest % 2) ? -r : r;
	*y = (r - 2) - rest / 2 * 2;

	return	TTN_OK;
}

/******************************************************************************************************************/
/* ���ը��                                                                                                       */
/******************************************************************************************************************/
void    debug_test_shipfunc(void)
{
    //test function approach_screen_axis_degree_dir_ex()
    {
        SLONG   i, dir;
        
        log_error(1, "test function approach_screen_axis_degree_dir_ex()");
        log_error(1, "degree          dir     ");
        log_error(1, "------------------------");
        for(i=0; i<36000; i+=100)
        {
            dir = approach_screen_axis_degree_dir_ex(i, 16);
            log_error(1, "%-16d, %-8d", i, dir);
        }
    }
}



/******************************************************************************************************************/
/* WINDOWS�ŶK�O���                                                                                              */
/******************************************************************************************************************/
//�\��: �q�ŶK�O��������r
//�Ѽ�: HWND hWnd       --> �}�ҰŶK�O�����f�y�`
//      USTR *buffer    --> �s���r���w�İϫ���
//      SLONG len       --> ��������r���̪�����
//��^: ��^�ƻs�쪺��r�r�`����.
EXPORT  SLONG   FNBACK  copy_text_from_clipboard(HWND hWnd, USTR *buffer, SLONG len)
{
    HANDLE  hGlobalMemory;
    LPVOID  pGlobalMemory;
    BOOL    bAvailable;
    LONG    lMemorySize;
    SLONG   copy_size, clip_size;

    copy_size = 0;
    bAvailable = IsClipboardFormatAvailable(CF_TEXT);
    if(bAvailable)
    {
        OpenClipboard(hWnd);
        hGlobalMemory = GetClipboardData(CF_TEXT);
        lMemorySize = GlobalSize(hGlobalMemory);
        pGlobalMemory = GlobalLock(hGlobalMemory);
        copy_size = min(len-1, lMemorySize);
        clip_size = find_word_clip_position((char *)pGlobalMemory, 0, copy_size);
        memcpy(buffer, pGlobalMemory, copy_size);
        buffer[copy_size] = 0x00;
        GlobalUnlock(hGlobalMemory);
        CloseClipboard();
    }
    return  copy_size;
}


//�\��: ������r��ŶK�O��
//�Ѽ�: HWND hWnd       --> �}�ҰŶK�O�����f�y�`
//      USTR *buffer    --> ��r���w�İϫ���
//��^: ��^�ƻs����r�r�`����.
EXPORT  SLONG   FNBACK  copy_text_to_clipboard(HWND hWnd, USTR *buffer)
{
    LONG    lLength;
    HANDLE  hGlobalMemory;
    LPVOID  pGlobalMemory;
    SLONG   copy_len;

    copy_len = 0;
    lLength = strlen((const char *)buffer);
    hGlobalMemory = GlobalAlloc(GHND, lLength+1);
    if(hGlobalMemory)
    {
        pGlobalMemory = GlobalLock(hGlobalMemory);
        strcpy((char *)pGlobalMemory, (const char *)buffer);
        GlobalUnlock(hGlobalMemory);

        OpenClipboard(hWnd);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hGlobalMemory);
        CloseClipboard();

        copy_len = lLength;
    }
    return  copy_len;
}


/******************************************************************************************************************/
/* �@�Ǧr��ާ@���                                                                                               */
/******************************************************************************************************************/
//�\�� : �M��r�ꤤ���Ыe�@�Ӧr(�~�r�Ϊ̦r��)����m
//�Ѽ� : char *str              -> �ݾާ@���r��.
//       SLONG now_position     -> 
//��^ : char *         -> ���G�r��.
EXPORT  SLONG   FNBACK  find_prev_word_position(char *str, SLONG now_position)
{
    SLONG   len;
    char *curr, *prev;

    len = strlen((const char *)str);
    curr = str + now_position;
    prev = CharPrev(str, curr);
    return  (SLONG)(prev - str);
}


//�\�� : �M��r�ꤤ���Ы�@�Ӧr(�~�r�Ϊ̦r��)����m
//�Ѽ� : char *str              -> �ݾާ@���r��.
//       SLONG now_position     -> 
//��^ : char *         -> ���G�r��.
EXPORT  SLONG   FNBACK  find_next_word_position(char *str, SLONG now_position)
{
    SLONG   len;
    char *curr, *next;

    len = strlen((const char *)str);
    curr = str + now_position;
    next = CharNext(curr);
    return  (SLONG)(next - str);
}


//�\�� : �R�����Ы᪺�@�Ӧr
//�Ѽ� : char *str              -> �ݾާ@�r��, �ާ@�����ɦP�ɦs��ާ@���G
//       SLONG now_position     -> ���з�e��m
//��^ : ��^�R���F�h�֦r�`.
EXPORT  SLONG   FNBACK  delete_after_cursor_word(char *str, SLONG now_position)
{
    char    *curr, *next;

    curr = str + now_position;
    next = CharNext(curr);
    memmove(curr, next, strlen(next) + 1);
    return  next - curr;
}



//�\�� : �R�����Ыe���@�Ӧr
//�Ѽ� : char *str              -> �ݾާ@�r��, �ާ@�����ɦP�ɦs��ާ@���G
//       SLONG now_position     -> ���з�e��m
//��^ : ��^�R���F�h�֦r�`.
EXPORT  SLONG   FNBACK  delete_before_cursor_word(char *str, SLONG now_position)
{
    char    *curr, *prev;

    curr = str + now_position;
    prev = CharPrev(str, curr);
    memmove(prev, curr, strlen(curr) + 1);
    return  curr - prev;
}


//�\�� : �b���Ц�m���J�r��
//�Ѽ� : char *str              -> �ݾާ@�r��, �ާ@�����ɦs��s���r��
//       char *insert_str       -> �ݴ��J���r��
//       SLONG now_position     -> ��e���Ц�m
//��^ : ��^���J�F�h�֦r�`.
EXPORT  SLONG   FNBACK  insert_string_at_cursor(char *str, char *insert_str, SLONG now_position)
{
    SLONG   insert_len;
    char    *curr;

    curr = str + now_position;
    insert_len = strlen((const char *)insert_str);
    memmove(curr+insert_len, curr, strlen(curr) + 1);
    memcpy(curr, insert_str, insert_len);
    return  insert_len;
}


//�\�� : �M��r�ꤤ���Ыe�@�w�r�`����r�����I����m.
//�Ѽ� : char *str              -> �ؼЦr��
//       SLONG now_position     -> ��e���Ц�m
//       SLONG before_length    -> ���Ыe�r�`����
EXPORT  SLONG   FNBACK  find_before_cursor_position(char *str, SLONG now_position, SLONG before_length)
{
    SLONG   len;
    char *curr, *prev;

    len = strlen((const char *)str);
    prev = curr = str + now_position;
    while(curr - prev < before_length)
    {
        prev = CharPrev(str, prev);
        if(prev == str)
            break;
    }
    return  (SLONG)(prev - str);
}


//�\�� : �M��r�ꤤ���Ы�@�w�r�`����r�����I����m.
//�Ѽ� : char *str              -> �ؼЦr��
//       SLONG now_position     -> ��e���Ц�m
//       SLONG after_length     -> ���Ы�r�`����
EXPORT  SLONG   FNBACK  find_after_cursor_position(char *str, SLONG now_position, SLONG after_length)
{
    SLONG   len;
    char *curr, *next;

    len = strlen((const char *)str);
    next = curr = str + now_position;
    while(next - curr < after_length)
    {
        next = CharNext(next);
        if(next == str + len)
            break;
    }
    return  (SLONG)(next - str);
}


extern  SLONG   copy_text_from_clipboard(HWND hWnd, USTR *buffer, SLONG len);
extern  SLONG   copy_text_to_clipboard(HWND hWnd, USTR *buffer);
extern  SLONG   find_prev_word_position(char *str, SLONG now_position);
extern  SLONG   find_next_word_position(char *str, SLONG now_position);
extern  SLONG   delete_after_cursor_word(char *str, SLONG now_position);
extern  SLONG   delete_before_cursor_word(char *str, SLONG now_position);
extern  SLONG   insert_string_at_cursor(char *str, char *insert_str, SLONG now_position);
extern  SLONG   find_before_cursor_position(char *str, SLONG now_position, SLONG before_length);
extern  SLONG   find_after_cursor_position(char *str, SLONG now_position, SLONG after_length);
//
void    find_appropriate_window_position(SLONG stand_win_sx, SLONG stand_win_sy, SLONG stand_win_xl, SLONG stand_win_yl,
                                         SLONG range_win_xl, SLONG range_win_yl, SLONG find_win_xl, SLONG find_win_yl,
                                         SLONG *find_win_sx, SLONG *find_win_sy)
{
    SLONG   stand_win_ex, stand_win_ey;
    SLONG   find_sx, find_sy;

    stand_win_ex = stand_win_sx + stand_win_xl;
    stand_win_ey = stand_win_sy + stand_win_yl;

    //find window start y position ----------------------------------
    if(stand_win_sy > range_win_yl - stand_win_ey)
    {
        if(stand_win_sy >= find_win_yl)
        {
            find_sy = stand_win_sy - find_win_yl;
        }
        else if(range_win_yl - stand_win_ey >= find_win_yl)
        {
            find_sy = stand_win_ey;
        }
        else
        {
            find_sy = stand_win_sy;
        }
    }
    else
    {
        if(stand_win_sy >= find_win_yl)
        {
            find_sy = stand_win_sy - find_win_yl;
        }
        else if(range_win_yl - stand_win_ey >= find_win_yl)
        {
            find_sy = stand_win_ey;
        }
        else
        {
            find_sy = stand_win_sy;
        }
    }

    if(find_sy + find_win_yl > range_win_yl)
    {
        find_sy = range_win_yl - find_win_yl;
    }
    if(find_sy < 0)
    {
        find_sy = 0;
    }

    //find window start x position ----------------------------------
    find_sx = stand_win_sx + stand_win_xl / 2 - find_win_xl / 2;
    if(find_sx + find_win_xl > range_win_xl)
    {
        find_sx = range_win_xl - find_win_xl;
    }
    if(find_sx < 0)
    {
        find_sx = 0;
    }

    *find_win_sx = find_sx;
    *find_win_sy = find_sy;
}


/*
int     init_magic_part(void)
{
    SLONG   i;

    for(i = 0; i < HEAD_GAME_MAGIC_PART; i++)
    {
        magic_part[i].next = i;
        magic_part[i].tail = i;
    }

    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART; i++)
    {
        magic_part[i].flag = 0;
        //
        magic_part[i].next = -1;
    }
    return 0;
}


void    free_magic_part(void)
{
}


void    reset_magic_part(void)
{
    SLONG   i;

    for(i = 0; i < HEAD_GAME_MAGIC_PART; i ++)
    {
        magic_part[i].next = i;
        magic_part[i].tail = i;
    }

    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART; i++)
    {
        magic_part[i].flag = 0;
        //
        magic_part[i].next = -1;
    }
}



void    clear_magic_part_object_index(void)
{
    SLONG   i;

    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART;  i++)
    {
        magic_part[i].object_index = -1;
    }
}


SLONG   find_usable_magic_part(void)
{
    SLONG   find_index;
    SLONG   i;

    find_index = -1;
    for(i = HEAD_GAME_MAGIC_PART; i < MAX_GAME_MAGIC_PART; i++)
    {
        if(0 == magic_part[i].flag)
        {
            find_index = i;
            break;
        }
    }
    return find_index;
}


SLONG   add_magic_part(SLONG map_no, MAGIC_PART *part )
{
    SLONG   index, tail;

    index = find_usable_magic_part();
    if(index >= 0)
    {
        //update magic_part's data
        magic_part[index].flag = 1;
        copy_magic_part_data( &magic_part[index], part);

        //insert this node to circulated-link
        magic_part[index].next = map_no;
        tail = magic_part[map_no].tail;
        magic_part[tail].next = index;
        magic_part[map_no].tail = index;
    }
    return index;
}


void    del_magic_part(SLONG map_no, SLONG part_no)
{
    SLONG   p, s;

    s = map_no;
    p = magic_part[map_no].next;
    while(p != map_no)
    {
        if(p == part_no)
        {
            //delete this node from circulated-link.
            magic_part[s].next = magic_part[p].next;
            if(magic_part[s].next == map_no)
                magic_part[map_no].tail = s;

            //update this node's data.
            magic_part[p].flag = 0;
            break;
        }
        else
        {
            s = p;
            p = magic_part[p].next;
        }
    }
    return;
}


void    reduce_void_magic_part( SLONG map_no )
{
    SLONG   p, s;

    s = map_no;
    p = magic_part[map_no].next;
    while(p != map_no)
    {
        if(! magic_part[p].flag )
        {
            //delete this node from circulated-link.
            magic_part[s].next = magic_part[p].next;
            if(magic_part[s].next == map_no)
                magic_part[map_no].tail = s;

            //update this node's data.
            magic_part[p].flag = 0;

            //get the new p for the next loop.
            p = magic_part[s].next;
        }
        else
        {
            s = p;
            p = magic_part[p].next;
        }
    }
    return;
}


SLONG   count_map_magic_parts(SLONG map_no)
{
    SLONG   total;
    SLONG   p;

    total = 0;
    p = magic_part[map_no].next;
    while(p != map_no)
    {
        total ++;
        p = magic_part[p].next;
    }
    return total;
}


void    copy_magic_part_data( MAGIC_PART *dest_part, MAGIC_PART *src_part)
{
    SLONG   back_flag, back_next;

    back_flag = dest_part->flag;
    back_next = dest_part->next;
    memcpy( dest_part, src_part, sizeof(MAGIC_PART) );
    dest_part->flag = back_flag;
    dest_part->next = back_next;
}


void    append_break_parts(SLONG map_no)
{
    SLONG   i, part_index;

    LOCK_MAGIC(0);
    for(i=0; i<max_break_part; i++)
    {
        part_index = add_magic_part(map_no, &break_part[i]);
    }
    UNLOCK_MAGIC(0);
}

*/

	static	RGB_DATA	rgb_data[7] = 
	{
		{0x74, 0x0e, 0x22, 0x8a, 0x00},
		{0x72, 0xb4, 0x34, 0x85, 0x00},
		{0x72, 0x8b, 0x56, 0x74, 0x00},
		{0x72, 0xd9, 0xf1, 0x75, 0x00},
		{0x72, 0x9a, 0x6f, 0xbf, 0x00},
		{0x72, 0xad, 0xc9, 0xb1, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00},

		/*
		{0x04, 0x0e, 0x22, 0x8a, 0x00},
		{0x02, 0xb4, 0x34, 0x85, 0x00},
		{0x02, 0x8b, 0x56, 0x74, 0x00},
		{0x02, 0xd9, 0xf1, 0x75, 0x00},
		{0x02, 0x9a, 0x6f, 0xbf, 0x00},
		{0x02, 0xad, 0xc9, 0xb1, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00},
		*/
	};

// �����H�����
void  redraw_swap_screen_with_block_rand(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum BLOCK_DATAS
    {    BLOCK_WIDTH     =   20,
    BLOCK_HEIGHT         =   20,
    SCREEN_BLOCK_XX      =   SCREEN_WIDTH/BLOCK_WIDTH,
    SCREEN_BLOCK_YY      =   SCREEN_HEIGHT/BLOCK_HEIGHT,
    SCREEN_BLOCK_COUNT   =   SCREEN_BLOCK_XX * SCREEN_BLOCK_YY,
    RAND_MAXIMIZE        =   SCREEN_BLOCK_COUNT
    };
    BMP  *block = NULL;
    ULONG *table=NULL,i=0,offset1,data1,offset2,data2;
    SLONG x,y;
    
    block = create_bitmap(BLOCK_WIDTH, BLOCK_HEIGHT);
    if(NULL == block)
        return;
    
    table = (ULONG *)malloc(SCREEN_BLOCK_COUNT*sizeof(ULONG));
    if(NULL == table)
        return;
    
    for(i=0;i<SCREEN_BLOCK_COUNT;i++)
        *((ULONG *)(table+i))=i;
    
    for(i=0; i<RAND_MAXIMIZE;i++)
    {
        offset1 = rand()%SCREEN_BLOCK_COUNT;
        offset2 = rand()%SCREEN_BLOCK_COUNT;
        data1 = *((ULONG *)(table+offset1));
        data2 = *((ULONG *)(table+offset2));
        *((ULONG *)(table+offset1)) = data2;
        *((ULONG *)(table+offset2)) = data1;
    }
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    set_data_file(packed_sound_file);
    play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_BLOCK_RAND);
    
    timer_tick00 = 0;;
    for(i=0; i<SCREEN_BLOCK_COUNT; i++)
    {
        IDLE_LOOP();
        
        offset1 = *((ULONG *)(table+i));
        y = (offset1/SCREEN_BLOCK_XX)*BLOCK_HEIGHT;
        x = (offset1%SCREEN_BLOCK_XX)*BLOCK_WIDTH;
        get_bitmap(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, block, dest_bitmap);
        put_bitmap(x, y, block, screen_buffer);
        if(i % 20 == 19)
        {
            update_screen(screen_buffer);
            timer_tick00 = 0;
            //while(timer_tick00 < 1)
              //  IDLE_LOOP();
        }
    }
    put_bitmap(0, 0, dest_bitmap, screen_buffer);
    update_screen(screen_buffer);
    
    destroy_bitmap(&block);
    if(table)    free(table);
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
}


//�Y�����
void    redraw_swap_screen_with_scale(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum SCALE_DATAS
    {
        SCALE_STEPS = 15
    };
    SLONG    sx,sy,scale_x,scale_y,i;
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    set_data_file(packed_sound_file);
    play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_SCALE_A);
    
    for(i=0;i<SCALE_STEPS;i++)
    {
        IDLE_LOOP();
        timer_tick00 = 0;;
        sx = SCREEN_WIDTH*i/SCALE_STEPS/2;
        sy = SCREEN_HEIGHT*i/SCALE_STEPS/2;
        scale_x = SCREEN_WIDTH*(SCALE_STEPS-i)/SCALE_STEPS;
        scale_y = SCREEN_HEIGHT*(SCALE_STEPS-i)/SCALE_STEPS;
        
        clear_bitmap(screen_buffer);
        scale_put_bitmap(sx, sy, scale_x, scale_y, src_bitmap, screen_buffer);
        update_screen(screen_buffer);
        
        //while(timer_tick00<1)
          //  IDLE_LOOP();
    }
    
    clear_bitmap(screen_buffer);
    update_screen(screen_buffer);
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    set_data_file(packed_sound_file);
    play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_SCALE_B);
    
    for(i=SCALE_STEPS-1;i>=0;i--)
    {
        IDLE_LOOP();
        timer_tick00 = 0;;
        sx = SCREEN_WIDTH*i/SCALE_STEPS/2;
        sy = SCREEN_HEIGHT*i/SCALE_STEPS/2;
        scale_x = SCREEN_WIDTH*(SCALE_STEPS-i)/SCALE_STEPS;
        scale_y = SCREEN_HEIGHT*(SCALE_STEPS-i)/SCALE_STEPS;
        clear_bitmap(screen_buffer);
        scale_put_bitmap(sx, sy, scale_x, scale_y, dest_bitmap, screen_buffer);
        update_screen(screen_buffer);
        //while(timer_tick00<1)
          //  IDLE_LOOP();
    }
    put_bitmap(0, 0, dest_bitmap, screen_buffer);
    update_screen(screen_buffer);
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
}


//���ۧΤ���
void  redraw_swap_screen_with_helix(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum HELIX_DATAS
    {    ANGLE_COUNT =   4,
    ANGLE_DIR_LU     =   0,
    ANGLE_DIR_RU     =   1,
    ANGLE_DIR_RD     =   2,
    ANGLE_DIR_LD     =   3,
    SAMPLE_COUNT     =   11,
    IMAGE_WIDTH      =   SCREEN_WIDTH/2,
    IMAGE_HEIGHT     =   SCREEN_HEIGHT/2,
    IMAGE_SIZE       =   IMAGE_WIDTH*IMAGE_HEIGHT+4,
    CLEAR_SCREEN     =   0
    };
    static POINT helix_pp[ANGLE_COUNT][SAMPLE_COUNT]=
    {
        {
            {320,240},
            {304,224},{272,240},{264,288},{320,336},{408,328},
            {464,240},{440,120},{320, 48},{168, 88},{ 80,240}
        },
        {
            {320,240},
            {336,224},{320,192},{272,184},{224,240},{240,328},
            {320,384},{440,360},{512,240},{472, 88},{320,  0}
        },
        {
            {320,240},
            {336,256},{368,240},{376,192},{320,144},{232,160},
            {176,240},{200,360},{320,432},{472,392},{560,240}
        },
        {
            {320,240},
            {304,256},{320,288},{376,288},{416,240},{408,152},
            {320, 96},{200,120},{128,240},{168,392},{320,480}
        }
    };
    static POINT image_rpp[ANGLE_COUNT]=
    {
        {-320,-240},{   0,-240},{   0,   0},{-320,   0}
    };
    BMP  *image[ANGLE_COUNT] = {NULL,NULL,NULL,NULL};
    SLONG i,j;
    
    for(i=0;i<ANGLE_COUNT;i++)
    {
        image[i] = NULL;
    }
    for(i=0;i<ANGLE_COUNT;i++)
    {
        image[i] = copy_bitmap(helix_pp[i][0].x+image_rpp[i].x, helix_pp[i][0].y+image_rpp[i].y,
            IMAGE_WIDTH, IMAGE_HEIGHT, src_bitmap);
        if(NULL == image[i])
            goto  _error;
    }
    
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    set_data_file(packed_sound_file);
    play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_HELIX_A);
    
    for(j=0;j<SAMPLE_COUNT;j++)
    {
        IDLE_LOOP();
        timer_tick00 = 0;;
        if(CLEAR_SCREEN)
            clear_bitmap(screen_buffer);
        for(i=0;i<ANGLE_COUNT;i++)
        {
            put_bitmap(helix_pp[i][j].x+image_rpp[i].x, helix_pp[i][j].y+image_rpp[i].y, image[i],screen_buffer);
        }
        update_screen(screen_buffer);
        //while(timer_tick00<10)
          //  IDLE_LOOP();
    }
    if(CLEAR_SCREEN)
    {
        clear_bitmap(screen_buffer);
        update_screen(screen_buffer);
    }
    
    for(i=0;i<ANGLE_COUNT;i++)
    {
        get_bitmap(helix_pp[i][0].x+image_rpp[i].x, helix_pp[i][0].y+image_rpp[i].y,
            IMAGE_WIDTH, IMAGE_HEIGHT,image[i],dest_bitmap);
    }
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    set_data_file(packed_sound_file);
    play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_HELIX_B);
    
    for(j=SAMPLE_COUNT-1;j>=0;j--)
    {
        IDLE_LOOP();
        timer_tick00 = 0;
        if(CLEAR_SCREEN)
            clear_bitmap(screen_buffer);
        
        for(i=0;i<ANGLE_COUNT;i++)
        {
            put_bitmap(helix_pp[i][j].x+image_rpp[i].x, helix_pp[i][j].y+image_rpp[i].y, image[i], screen_buffer);
        }
        update_screen(screen_buffer);
        //while(timer_tick00<10)
          //  IDLE_LOOP();
    }
    put_bitmap(0, 0, dest_bitmap, screen_buffer);
    update_screen(screen_buffer);
    stop_voice(SWAPSCR_VOICE_CHANNEL);
    
_error:
    for(i=0;i<4;i++)
    {
        if(image[i]) destroy_bitmap(&image[i]);
    }
}


static	void	chat_command_show_gm_window(void)
{
	SLONG	is_show;

	is_show = IsGMWindowVisible();
	ShowGameManagerWindow(1 - is_show);
}

void init_ui_store_store_item(void)
{
	SLONG test_base_id[MAX_UISTORE_STORE_ITEM]=
	{
		1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 
		1600, 1601, 1602, 1603, 1604, 1605, 1606, 1607, 1608, 
		1650, 1651, 1652, 1653, 1654, 1655, 1656, 1657, 1658, 
		1750, 1751, 1752, 1753, 1754, 1755, 1756, 1757, 1758,
			
		1750, 1751, 1752, 1753, 1754, 1755, 1756, 1757, 1758,
		1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 
		1600, 1601, 1602, 1603, 1604, 1605, 1606, 1607, 1608, 
		1650, 1651, 1652, 1653, 1654, 1655, 1656, 1657, 1658, 
			
	};
	SLONG i;
	
	
	for(i=0;i<MAX_UISTORE_STORE_ITEM;i++)
	{
		SetItemBaseID(&uistore_store_item[i], (UHINT)test_base_id[i]);
	}
	
	
}


void init_ui_store_user_item(void)
{
	SLONG test_base_id[MAX_UISTORE_USER_ITEM]={
		1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 
			1600, 1601, 1602, 1603, 1604, 1605, 1606, 1607, 1608, 
			1650, 1651, 1652, 1653, 1654, 1655, 1656, 1657, 1658, 
			
	};
	SLONG i;
	
	for(i=0;i<MAX_UISTORE_USER_ITEM;i++)
	{
		if(i<MAX_UISTORE_USER_ITEM/2)
			SetItemBaseID(&uistore_user_item[i], (UHINT)test_base_id[i]);
		else
			SetItemNone(&uistore_user_item[i]);
	}
}


    SLONG   mouse_x, mouse_y, event_type, event_id;
	
    switch(message)
    {
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'A': case 'a':
				open_ui_store(1 - is_ui_store_open());
				break;
			case '1':
				set_ui_store_type(UISTORE_TYPE_STORE);
				break;
			case '2':
				set_ui_store_type(UISTORE_TYPE_BANK);
				break;
			case '3':
				set_ui_store_type(UISTORE_TYPE_STOREBOX);
				break;
			case '4':
				set_ui_store_type(UISTORE_TYPE_STRONGBOX);
				break;
			}
		}
		break;

	case WM_MOUSEMOVE:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		
		uistore_data.mouse_x=mouse_x;
		uistore_data.mouse_y=mouse_y;
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		uistore_data.task_id = event_id;
		uistore_data.active_task_id=-1;
		break;

	case WM_LBUTTONDOWN:
		{
			mouse_x = GET_X_LPARAM(lParam);
			mouse_y = GET_Y_LPARAM(lParam);
			uistore_data.mouse_x=mouse_x;
			uistore_data.mouse_y=mouse_y;
			event_type = event_id = 0;
			game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
			uistore_data.task_id = event_id;
			uistore_data.active_task_id= event_id;
			switch(event_id)
			{
			case UISTORE_EVENTID_PGUP:
				break;
			case UISTORE_EVENTID_PGDN:
				break;
			case UISTORE_EVENTID_CLOSE:
				break;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			uistore_data.active_task_id= -1;
			mouse_x = GET_X_LPARAM(lParam);
			mouse_y = GET_Y_LPARAM(lParam);
			uistore_data.mouse_x=mouse_x;
			uistore_data.mouse_y=mouse_y;
			event_type = event_id = 0;
			game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
			uistore_data.task_id = event_id;
			uistore_data.active_task_id= event_id;
			switch(event_id)
			{
			case UISTORE_EVENTID_PGUP:
				ui_store_page_up();
				break;
			case UISTORE_EVENTID_PGDN:
				ui_store_page_down();
				break;
			case UISTORE_EVENTID_CLOSE:
				open_ui_store(FALSE);
				break;
			}
		}
		break;
    }

void    redraw_ui_store(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
	SLONG x,y;
	SLONG i,j,icon_index;
	SLONG event,id;
	CAKE_FRAME *cf;
	TPOS_ITEM item;
	SLONG store_item_index;
	
	if(uistore_data.uistore_enabled != UISTORE_ENABLE)
		return;
	event = UISTORE_EVENT;
	
	// --------------(0)  draw body
	cf=uistore_data.cf[UISTORE_FRAME_BODY];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	
	// --------------(0-1) Button
	if(uistore_data.active_task_id==UISTORE_EVENTID_PGUP)
		cf=uistore_data.cf[UISTORE_FRAME_PAGEUP_PRESS];
	else if(uistore_data.task_id==UISTORE_EVENTID_PGUP)
		cf=uistore_data.cf[UISTORE_FRAME_PAGEUP_SELECT];
	else
		cf=uistore_data.cf[UISTORE_FRAME_PAGEUP_BASE];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	
	cf=uistore_data.cf[UISTORE_FRAME_PAGEUP_BASE];
	id=UISTORE_EVENTID_PGUP;
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	
	if(uistore_data.active_task_id==UISTORE_EVENTID_PGDN)
		cf=uistore_data.cf[UISTORE_FRAME_PAGEDOWN_PRESS];
	else if(uistore_data.task_id==UISTORE_EVENTID_PGDN)
		cf=uistore_data.cf[UISTORE_FRAME_PAGEDOWN_SELECT];
	else
		cf=uistore_data.cf[UISTORE_FRAME_PAGEDOWN_BASE];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	
	cf=uistore_data.cf[UISTORE_FRAME_PAGEDOWN_BASE];
	id=UISTORE_EVENTID_PGDN;
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	
	if(uistore_data.task_id==UISTORE_EVENTID_CLOSE)
		cf=uistore_data.cf[UISTORE_FRAME_CLOSE_SELECT];
	else
		cf=uistore_data.cf[UISTORE_FRAME_CLOSE_BASE];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	
	cf=uistore_data.cf[UISTORE_FRAME_CLOSE_BASE];
	id=UISTORE_EVENTID_CLOSE;
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	
	// -------------- draw title 
	switch(uistore_data.uistore_type)
	{
	case UISTORE_TYPE_STORE:						// �ө�
		cf=uistore_data.cf[UISTORE_FRAME_STORE_MARK];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		break;

	case UISTORE_TYPE_BANK:							// �Ȧ�
		cf=uistore_data.cf[UISTORE_FRAME_BANK_MARK];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		cf=uistore_data.cf[UISTORE_FRAME_GOLDBASE];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		// ------- display player money
		break;

	case UISTORE_TYPE_STOREBOX:						// �x���c
		cf=uistore_data.cf[UISTORE_FRAME_STOREBOX_MARK];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		cf=uistore_data.cf[UISTORE_FRAME_GOLDBASE];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		break;
	case UISTORE_TYPE_STRONGBOX:					// �O�I�c
		cf=uistore_data.cf[UISTORE_TYPE_STRONGBOX];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		cf=uistore_data.cf[UISTORE_FRAME_GOLDBASE];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		break;
	default:
		return;
	}
	
	
	
	
	// -------------- draw Store item
	// -------------- Set box game_range
	id=100;
	store_item_index=uistore_data.active_page*MAX_STORE_DISPLAY;
	for(i=0;i<4;i++)				// draw Up box
	{
		for(j=0;j<9;j++)
		{
			x=sx+32+j*34;
			y=sy+162+i*34;
			game_range.add(x, y, 30, 30, event, id);
			id++;
			
			if(store_item_index<MAX_UISTORE_STORE_ITEM)
			{
				item.BaseID=uistore_store_item[store_item_index].BaseID;
				if(!IsItemNone(&item))
				{
					icon_index = GetItemIconIndex(&item);
					redraw_item_icon_image(x+15, y+15, icon_index, bitmap);
				}
			}
			store_item_index++;
		}
	}
	
	// -------------- draw User item
	id=1000;
	for(i=0;i<3;i++)				// draw Down box
	{
		for(j=0;j<9;j++)
		{
			x=sx+32+j*34;
			y=sy+358+i*34;
			game_range.add(x, y, 30, 30, event, id);
			id++;
			item.BaseID=uistore_user_item[i*9+j].BaseID;
			if(!IsItemNone(&item))
			{
				icon_index = GetItemIconIndex(&item);
				redraw_item_icon_image(x+15, y+15, icon_index, bitmap);
			}
		}
	}
	
	// -------- For DEBUG
#ifdef STORE_DEBUG
	sprintf((char *)print_rec,"Mouse:(%d,%d) Task:%d Page:%d",uistore_data.mouse_x,
		uistore_data.mouse_y,
		uistore_data.task_id,
		uistore_data.active_page);
	print16(0,0,print_rec,COPY_PUT,bitmap);
#endif
	
}

void	ask_buy_item_at_item_store_callback(DWORD param, SLONG result)
{
	UIMB_PARAM *p;
	SLONG	store_index, item_index;

	switch(result)
	{
	case MSG_BOX_ID_YES:
		p = (UIMB_PARAM *)param;
		store_index = p->param1;
		item_index = p->param2;
		client_cmd_left_hit_item_store_item(store_index, item_index);
		break;

	case MSG_BOX_ID_NO:
		break;
	}
}



extern	void	ask_buy_item_at_item_store_callback(DWORD param, SLONG result);

		/*
		MouseData.fwKeys = GET_KEYSTATE_WPARAM(wParam);
		MouseData.xPos = GET_X_LPARAM(lParam)-MouseData.nWindowXOffset;
		MouseData.yPos = GET_Y_LPARAM(lParam)-MouseData.nWindowYOffset;
		if(wParam & MK_LBUTTON) MouseData.cEvent = MS_LDrag;
		else if(wParam & MK_RBUTTON) MouseData.cEvent = MS_RDrag;
		else if(wParam & MK_MBUTTON) MouseData.cEvent = MS_MDrag;
		else MouseData.cEvent = MS_Move;
		SetCursor(MouseData.hNowCursor);
		if(! MouseData.bInClientArea )
		{
			MouseData.bInClientArea = TRUE;
			if(MouseData.cShow & SHOW_WINDOW_CURSOR)
				ShowCursor(TRUE);
			else
				ShowCursor(FALSE);
		}
		*/
		//fnMouseInterrupt(Msg, wParam, lParam);

//---------------------------------------------------------------------------------------
#endif//0 ////////////////////////////////////////////////////////////////////////////////
