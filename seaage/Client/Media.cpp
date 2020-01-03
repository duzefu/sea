/*
**	Media.cpp 
**	Media file access functions.
**
**	Stephen, 2002.7.1.
**		Created.
**
**	Jack, 2003.1.21.
**		Added for SeaAge Editor.
**
*/

#include "MainFun.h"
#include "media.h"


// ------------- Extern routinue ---------------
//void display_message(UCHR *message,bool wait_key_flag);
#define	display_message(a,b)	log_error(1, a)


UCHR *system_palette=NULL;
UCHR r_full_palette[768];
UCHR g_full_palette[768];
UCHR b_full_palette[768];
UCHR yellow_full_palette[768];
UCHR black_full_palette[768];
UCHR white_full_palette[768];
UCHR change_color_palette[768];			// Change color temp palette
SLONG change_color_flag=1;				// change color action flag
// 0 -> None
// 1 -> Rebuild change color & source palette
SLONG goto_frame=-1;
SLONG attack_start=0;
SLONG attack_value=0;
SLONG front_start=0;
SLONG magic_start=0;
SLONG AssemMaxDir=0;
SLONG AssemMaxPart=0;


// Jack, remark for cancel the voice play for SeaAge. [1/21/2003]
//UCHR voice_filename[MAX_SOUND_CHANNELS][255];
//SLONG voice_loop[MAX_SOUND_CHANNELS];
//ULONG channel_timer[MAX_SOUND_CHANNELS]; 

// ------------- Globe variable -------------------
SLONG total_mda_group=0;
MDA_GROUP *mda_group=NULL;
ULONG mda_handle_count=0;




/*******************************************************************************************}
{																							}
********************************************************************************************/
SLONG mda_group_open(UCHR *filename,SLONG *handle)
{
    SLONG mda_group_index;
    PACK_FILE *fp;
    SLONG file_size;
    MDA_HEAD temp_mda_head;
    UCHR *data_buffer;
    //UCHR text[255];


    *handle=-1;
    // Jack, remark [1/22/2003]
    /*
    if(check_file_exist(filename)!=TTN_OK)
    {
    sprintf((char *)text,"File %s Open error",filename);
    display_message(text,true);
    return(TTN_NOT_OK);
    }
    if(check_is_mda_file(filename)!=TTN_OK)
    {
    sprintf((char *)text,"File %s not MDA file",filename);
    display_message(text,true);
    return(TTN_NOT_OK);
    }
    */

    // Jack, Add reference control here. [1/24/2003]
    mda_group_index = found_exist_mda_group(filename);
    if(mda_group_index >= 0)
    {
        *handle = mda_group[mda_group_index].handle;
        mda_group[mda_group_index].references ++;
        return	TTN_OK;
    }


    // ---- alloc mda struct 
    mda_group_index = add_mda_group();
    if(mda_group_index<0)
    {
        display_message((UCHR *)"MDA Create Error",true);
        return(TTN_NOT_OK);
    }
    *handle = mda_group[mda_group_index].handle;
    strcpy((CHAR *)mda_group[mda_group_index].filename,(char *)filename);
    fp = pack_fopen((char *)filename,"rb");
    if(fp==NULL)
        return(TTN_NOT_OK);	
    file_size = pack_fsize(fp);
    mda_group[mda_group_index].body = (UCHR *)malloc(sizeof(UCHR)*file_size);
    if(mda_group[mda_group_index].body==NULL)
    {
        display_message((UCHR *)"Memory error(MDA file load)",true);
        pack_fclose(fp);
        return(TTN_NOT_OK);
    }
    pack_fread(mda_group[mda_group_index].body,1,file_size,fp);
    pack_fclose(fp);
    memcpy(&temp_mda_head,mda_group[mda_group_index].body,sizeof(struct MDA_HEAD_STRUCT));
    mda_group[mda_group_index].total_database=temp_mda_head.total_database_frame;
    data_buffer=&mda_group[mda_group_index].body[temp_mda_head.ani_start_offset];
    mda_group[mda_group_index].total_ani_command = get_total_ani_command(data_buffer,mda_group_index);
    mda_group[mda_group_index].database_start_offset = temp_mda_head.data_start_offset;
    mda_group[mda_group_index].command_start_offset = temp_mda_head.ani_start_offset;

    // init frame parameter
    mda_group[mda_group_index].img256_head=NULL;

    // ---- Decode database index
    if(temp_mda_head.total_database_frame>0)
    {
        mda_group[mda_group_index].database_index=
            (struct INDEX_OFFSET_SIZE_STRUCT *)malloc(sizeof(struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame);
        if(mda_group[mda_group_index].database_index==NULL)
        {
            display_message((UCHR *)"Memory error(DATABASE index)",true);
            return(TTN_NOT_OK);
        }
        memcpy(mda_group[mda_group_index].database_index,&mda_group[mda_group_index].body[sizeof(struct MDA_HEAD_STRUCT)],
            sizeof(struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame);
    }

    // Make command tree 
    if(temp_mda_head.total_ani_frame>0)
    {
        mda_group[mda_group_index].total_ani_command=get_total_ani_command(data_buffer,mda_group_index);
        data_buffer=&mda_group[mda_group_index].body[temp_mda_head.ani_start_offset];
        make_mda_command_tree(data_buffer,mda_group_index,temp_mda_head.total_ani_frame);
    }
    else
    {
        mda_group[mda_group_index].total_ani_frame=0;
        mda_group[mda_group_index].total_node=0;
    }

    // Jack, Add reference control here. [1/24/2003]
    mda_group[mda_group_index].references = 1;

    return(TTN_OK);
}


SLONG	mda_group_open_with_position(UCHR *filename, SLONG *handle)
{
    SLONG mda_group_index;
    PACK_FILE *fp;
    SLONG file_size;
    MDA_HEAD temp_mda_head;
    UCHR *data_buffer;
    //UCHR text[255];


    *handle=-1;
    // Jack, remark [1/22/2003]
    /*
    if(check_file_exist(filename)!=TTN_OK)
    {
    sprintf((char *)text,"File %s Open error",filename);
    display_message(text,true);
    return(TTN_NOT_OK);
    }
    if(check_is_mda_file(filename)!=TTN_OK)
    {
    sprintf((char *)text,"File %s not MDA file",filename);
    display_message(text,true);
    return(TTN_NOT_OK);
    }
    */

    // Jack, Add reference control here. [1/24/2003]
    mda_group_index = found_exist_mda_group(filename);
    if(mda_group_index >= 0)
    {
        *handle = mda_group[mda_group_index].handle;
        mda_group[mda_group_index].references ++;
        return	TTN_OK;
    }



    // ---- alloc mda struct 
    mda_group_index = add_mda_group();
    if(mda_group_index<0)
    {
        display_message((UCHR *)"MDA Create Error",true);
        return(TTN_NOT_OK);
    }
    *handle = mda_group[mda_group_index].handle;
    strcpy((CHAR *)mda_group[mda_group_index].filename,(char *)filename);
    fp = pack_fopen((char *)filename,"rb");
    if(fp==NULL)
        return(TTN_NOT_OK);	
    file_size = pack_fsize(fp);
    mda_group[mda_group_index].body = (UCHR *)malloc(sizeof(UCHR)*file_size);
    if(mda_group[mda_group_index].body==NULL)
    {
        display_message((UCHR *)"Memory error(MDA file load)",true);
        pack_fclose(fp);
        return(TTN_NOT_OK);
    }
    pack_fread(mda_group[mda_group_index].body,1,file_size,fp);
    pack_fclose(fp);

    memcpy(&temp_mda_head,mda_group[mda_group_index].body,sizeof(struct MDA_HEAD_STRUCT));
    mda_group[mda_group_index].total_database=temp_mda_head.total_database_frame;
    data_buffer=&mda_group[mda_group_index].body[temp_mda_head.ani_start_offset];
    mda_group[mda_group_index].total_ani_command = get_total_ani_command(data_buffer,mda_group_index);
    mda_group[mda_group_index].database_start_offset = temp_mda_head.data_start_offset;
    mda_group[mda_group_index].command_start_offset = temp_mda_head.ani_start_offset;

    // init frame parameter
    mda_group[mda_group_index].img256_head=NULL;

    // ---- Decode database index
    if(temp_mda_head.total_database_frame>0)
    {
        mda_group[mda_group_index].database_index=
            (struct INDEX_OFFSET_SIZE_STRUCT *)malloc(sizeof(struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame);
        if(mda_group[mda_group_index].database_index==NULL)
        {
            display_message((UCHR *)"Memory error(DATABASE index)",true);
            return(TTN_NOT_OK);
        }
        memcpy(mda_group[mda_group_index].database_index,&mda_group[mda_group_index].body[sizeof(struct MDA_HEAD_STRUCT)],
            sizeof(struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame);
    }

    // Make command tree 
    if(temp_mda_head.total_ani_frame>0)
    {
        mda_group[mda_group_index].total_ani_command=get_total_ani_command(data_buffer,mda_group_index);
        data_buffer=&mda_group[mda_group_index].body[temp_mda_head.ani_start_offset];
        make_mda_command_tree(data_buffer,mda_group_index,temp_mda_head.total_ani_frame);
    }
    else
    {
        mda_group[mda_group_index].total_ani_frame=0;
        mda_group[mda_group_index].total_node=0;
    }

    mda_group[mda_group_index].offset_x = 0;
    mda_group[mda_group_index].offset_y = 0;
    mda_group[mda_group_index].with_offset = 0;

    // Jack, Added for read position file. [1/22/2003]
    USTR	position_filename[_MAX_FNAME];
    SLONG	offset_x, offset_y;

    change_file_extension((USTR*)position_filename, filename, (USTR*)".mdr");
    fp = pack_fopen((const char *)position_filename, "rb");
    if(fp)
    {
        pack_fread(&offset_x, 1, sizeof(SLONG), fp);
        pack_fread(&offset_y, 1, sizeof(SLONG), fp);
        pack_fclose(fp);
        mda_group[mda_group_index].offset_x = offset_x;
        mda_group[mda_group_index].offset_y = offset_y;
        mda_group[mda_group_index].with_offset = 1;
    }

    // Jack, Add reference control here. [1/24/2003]
    mda_group[mda_group_index].references = 1;

    return(TTN_OK);
}


SLONG add_mda_group(void)
{
    MDA_GROUP *temp_mda_group=NULL;
    SLONG new_total_mda_group;
    SLONG i;
    SLONG new_handle;

    // ---- alloc new buffer
    new_total_mda_group=total_mda_group+1;
    new_handle=total_mda_group;
    temp_mda_group=(MDA_GROUP *)malloc(sizeof(MDA_GROUP_STRUCT)*new_total_mda_group);
    if(temp_mda_group==NULL)
    {
        display_message((UCHR *)"Memory Error (MDA_GROUP)",true);
        return(TTN_NOT_OK);
    }

    // ---- Copy to temp
    for(i=0;i<total_mda_group;i++)
        memcpy(&temp_mda_group[i],&mda_group[i],sizeof(struct MDA_GROUP_STRUCT));

    // ---- Free old mda_group
    if(mda_group!=NULL)
        free(mda_group);

    // ---- Copy temp to mda_group
    total_mda_group=new_total_mda_group;
    mda_group=(MDA_GROUP *)malloc(sizeof(MDA_GROUP_STRUCT)*total_mda_group);
    if(mda_group==NULL)
    {
        display_message((UCHR *)"Memory Error (MDA_GROUP)",true);
        return(TTN_NOT_OK);
    }
    for(i=0;i<total_mda_group;i++)
        memcpy(&mda_group[i],&temp_mda_group[i],sizeof(struct MDA_GROUP_STRUCT));

    free(temp_mda_group);
    // ---- Initial new mda_group parameter
    mda_group[new_handle].body=NULL;
    mda_group[new_handle].handle=mda_handle_count;
    mda_group[new_handle].database_index=NULL;
    mda_group[new_handle].command_node=NULL;
    mda_group[new_handle].now_frame=NULL;
    mda_group[new_handle].total_frame=NULL;
    mda_group[new_handle].dire_frame_node=NULL;
    // stephen need to change (initialize 128)
    memset(mda_group[new_handle].sea_rgb_data,0x00,sizeof(struct RGB_DATA_STRUCT)*SEA_CHANGE_COLOR_TYPE);

    // Jack, Add reference control here. [1/24/2003]
    mda_group[new_handle].references = 0;

    mda_handle_count=find_next_mda_handle();
    return(new_handle);
}


ULONG find_next_mda_handle(void)
{
    SLONG i;
    ULONG find_handle;
    SLONG main_pass=0;
    bool find;

    find_handle=total_mda_group;
    while(main_pass==0)
    {
        find=false;
        for(i=0;i<total_mda_group;i++)
        {
            if(mda_group[i].handle==find_handle)
            {
                find=true;
                i=total_mda_group;
            }
        }
        if(find==false)
        {	
            return(find_handle);
        }
        else
        {
            find_handle++;
            if(find_handle>1000000)
                find_handle=0;
        }
    }
    return(TTN_NOT_OK);
}


void mda_group_reset(SLONG handle)
{
    SLONG mda_index;
    SLONG i;

    if(handle<0)return;
    mda_index=get_mda_index(handle);

    for(i=0;i<mda_group[mda_index].total_ani_command;i++)
        mda_group[mda_index].now_frame[i]=0;

}


void mda_group_reset_single(SLONG handle,SLONG ani_idx)
{
    SLONG mda_index;

    if(handle<0)return;
    mda_index=get_mda_index(handle);
    if(mda_index<0)return;
    if((ani_idx<0)||(ani_idx>=mda_group[mda_index].total_ani_command))
        return;
    mda_group[mda_index].now_frame[ani_idx]=0;
}


void mda_group_close(SLONG *handle)
{
    ULONG mda_group_index;
    SLONG new_total_mda_group;
    SLONG i,j;
    MDA_GROUP *temp_mda_group=NULL;

    // Jack, Add reference control here. [1/24/2003]
    //
    // We check the mda's reference count, if it's more than 1, what we need to do is just decrease 
    // the reference count. Otherwise, do free mda processing.
    //
    mda_group_index = get_mda_index(*handle);
    if(mda_group_index==TTN_NOT_OK)
        return;
    mda_group[mda_group_index].references --;
    if(mda_group[mda_group_index].references > 0)
        return;
    //---------------------------------

    if(total_mda_group==1)
    {
        free_mda_group();
        total_mda_group=0;
        *handle=-1;				
        return;
    }
    // ---- get mda_group_index
    mda_group_index=get_mda_index(*handle);
    if(mda_group_index==TTN_NOT_OK)return;

    // ---- 
    new_total_mda_group=total_mda_group-1;
    temp_mda_group=(MDA_GROUP *)malloc(sizeof(struct MDA_GROUP_STRUCT)*new_total_mda_group);
    if(temp_mda_group==NULL)
    {
        display_message((UCHR *)"Memory Error (MDA_GROUP)",true);
        return;
    }

    // -------- Copy to temp
    for(i=0,j=0;i<total_mda_group;i++)
    {
        if(i==(SLONG)mda_group_index)
        {
            if(mda_group[i].body!=NULL)
                free(mda_group[i].body);
            mda_group[i].body=NULL;
            if(mda_group[i].command_node!=NULL)
                free(mda_group[i].command_node);
            mda_group[i].command_node=NULL;
            if(mda_group[i].now_frame!=NULL)
                free(mda_group[i].now_frame);
            mda_group[i].now_frame=NULL;
            if(mda_group[i].total_frame!=NULL)
                free(mda_group[i].total_frame);
            mda_group[i].total_frame=NULL;
            if(mda_group[i].database_index!=NULL)
                free(mda_group[i].database_index);
            mda_group[i].database_index=NULL;
            if(mda_group[i].dire_frame_node!=NULL)
                free(mda_group[i].dire_frame_node);
            mda_group[i].dire_frame_node=NULL;
            continue;
        }
        memcpy(&temp_mda_group[j],&mda_group[i],sizeof(struct MDA_GROUP_STRUCT));
        j++;
    }

    // ---- Free old mda_group
    if(mda_group!=NULL)
        free(mda_group);

    // ---- Copy temp to mda_group
    total_mda_group=new_total_mda_group;
    mda_group=(MDA_GROUP *)malloc(sizeof(struct MDA_GROUP_STRUCT)*total_mda_group);
    if(mda_group==NULL)
    {
        display_message((UCHR *)"Memory Error (MDA_GROUP)",true);
        return;
    }
    for(i=0;i<total_mda_group;i++)
        memcpy(&mda_group[i],&temp_mda_group[i],sizeof(struct MDA_GROUP_STRUCT));

    free(temp_mda_group);
    *handle=-1;				
}


SLONG get_mda_index(ULONG mda_handle)
{
    SLONG i;

    for(i=0;i<total_mda_group;i++)
    {
        if(mda_group[i].handle==mda_handle)
            return(i);
    }
    return(TTN_NOT_OK);
}


void free_mda_group(void)
{
    SLONG i;

    if(mda_group==NULL)return;
    for(i=0;i<total_mda_group;i++)
    {
        if(mda_group[i].body!=NULL)
        {
            free(mda_group[i].body);
            mda_group[i].body=NULL;
        }
        if(mda_group[i].database_index!=NULL)
        {
            free(mda_group[i].database_index);
            mda_group[i].database_index=NULL;
        }
        if(mda_group[i].command_node!=NULL)
        {
            free(mda_group[i].command_node);
            mda_group[i].command_node=NULL;
        }
        if(mda_group[i].now_frame!=NULL)
            free(mda_group[i].now_frame);
        mda_group[i].now_frame=NULL;
        if(mda_group[i].total_frame!=NULL)
            free(mda_group[i].total_frame);
        mda_group[i].total_frame=NULL;
        if(mda_group[i].dire_frame_node!=NULL)
            free(mda_group[i].dire_frame_node);
        mda_group[i].dire_frame_node=NULL;
    }
    free(mda_group);
    total_mda_group=0;
    mda_group=NULL;
}



SLONG get_file_size(UCHR *filename)
{
    FILE *fp;
    SLONG size;
    int handle;
    UCHR tt[255];
    UCHR message[255];

    fp=fopen((char *)filename,"r+b");
    if(fp==NULL)
    {
        getcwd((char *)tt, 255);
        sprintf((char *)message,"File %s\\%s open error",tt,filename);
        display_message(message,true);
        return(0);
    }
    handle = fileno(fp);
    size=filelength(handle);
    fclose(fp);
    return(size);
}



SLONG get_total_ani_command(UCHR *body,SLONG mda_group_index)
{
    SLONG body_size;
    UCHR *ani_buffer;
    SLONG decode_index;
    SLONG main_pass;
    SLONG command_level,command_length;
    SLONG total_ani_command;

    body_size=*(SLONG *)&body[0];
    if(body_size==0)return(0);
    ani_buffer=&body[4];

    total_ani_command=0;
    decode_index=0;			
    main_pass=0;
    while(main_pass==0)
    {
        command_level=(SLONG)ani_buffer[decode_index];
        command_length=(SLONG)ani_buffer[decode_index+1];
        switch(command_level)
        {
        case ANI_MAIN_COMMAND:					// Main Command
            total_ani_command++;
            break;
        }
        decode_index=decode_index+command_length;
        if(decode_index>=body_size)
            main_pass=1;
    }
    return(total_ani_command);
}



void make_mda_command_tree(UCHR *body,SLONG mda_group_index,SLONG total_ani_node)
{
    SLONG total_ani_command;
    SLONG total_database_frame;
    SLONG body_size;
    UCHR *ani_buffer;

    SLONG total_node;
    SLONG i,j;
    SLONG main_pass;
    SLONG decode_index;
    SLONG command_level,command_length;

    ULONG father_node,child_node;
    // ULONG equ_node;
    ULONG database_node,effect_node1,effect_node2;
    SLONG node_idx;

    SLONG main_command_index;
    SLONG total_ani_frame=0;
    SLONG start_frame_count=0;
    UCHR command_text[255];
    ULONG *temp_total_frame=NULL;

    //UCHR no_text[255];


    // ---- Step(0) 配置 ani_commane 的 frame 參數
    total_ani_command=mda_group[mda_group_index].total_ani_command;
    if(total_ani_command<=0)return;

    // ---- Alloc memory 
    mda_group[mda_group_index].total_frame=(SLONG *)malloc(sizeof(SLONG)*total_ani_command);
    mda_group[mda_group_index].now_frame=(SLONG *)malloc(sizeof(SLONG)*total_ani_command);
    if((mda_group[mda_group_index].total_frame==NULL)||
        (mda_group[mda_group_index].now_frame==NULL))
    {
        display_message((UCHR *)"Memory Error(total_frame)",true);
        return;
    }

    temp_total_frame=(ULONG *)malloc(sizeof(ULONG)*total_ani_node);
    if(temp_total_frame==NULL)
    {
        display_message((UCHR *)"Memory Error(total_frame)",true);
        return;
    }

    // ----- Reset now frame & total frame
    for(i=0;i<total_ani_command;i++)
    {
        mda_group[mda_group_index].now_frame[i]=0;
        mda_group[mda_group_index].total_frame[i]=0;
    }
    body_size=*(SLONG *)&body[0];
    ani_buffer=&body[4];

    // ---- Step(1) 配置總共所需要的Node
    // ---------------- 計算總共有多少 Node 
    total_node=0;
    decode_index=0;			
    main_pass=0;
    while(main_pass==0)
    {
        command_length=(SLONG)ani_buffer[decode_index+1];
        decode_index=decode_index+command_length;
        total_node=total_node+1;
        if(decode_index>=body_size)
            main_pass=1;
    }
    mda_group[mda_group_index].total_node=total_node;
    // ----------------- 配置 memory
    if(total_node<=0)return;
    mda_group[mda_group_index].command_node=(MDA_NODE *)malloc(sizeof(struct MDA_NODE_STRUCT)*total_node);
    if(mda_group[mda_group_index].command_node==NULL)
    {
        display_message((UCHR *)"Memory Error(total_frame)",true);
        return;
    }
    for(i=0;i<total_node;i++)
    {
        mda_group[mda_group_index].command_node[i].body_idx=NULL;
        mda_group[mda_group_index].command_node[i].chind_node=END_NODE;
        mda_group[mda_group_index].command_node[i].equ_node=END_NODE;
        mda_group[mda_group_index].command_node[i].father_node=END_NODE;
        mda_group[mda_group_index].command_node[i].database_idx=-1;
    }
    // ----------------- Fill Node data
    total_database_frame=0;
    total_ani_frame=0;
    main_command_index=-1;
    decode_index=0;			
    main_pass=0;

    father_node=ROOT_NODE,
        child_node=ROOT_NODE,

        database_node=ROOT_NODE;
    effect_node1=ROOT_NODE;
    effect_node2=ROOT_NODE;

    node_idx=0;
    while(main_pass==0)
    {
        command_level=(SLONG)ani_buffer[decode_index];
        command_length=(SLONG)ani_buffer[decode_index+1];
        memcpy(command_text,&ani_buffer[decode_index+2],command_length-2);
        switch(command_level)
        {
        case ANI_MAIN_COMMAND:					// Main Command
            database_node=add_mda_child_node(ROOT_NODE,&node_idx,&ani_buffer[decode_index+2],mda_group_index);

            if(main_command_index>=0)
            {
                mda_group[mda_group_index].total_frame[main_command_index]=
                    total_database_frame;
            }
            total_database_frame=0;
            main_command_index++;
            if(strcmpi((char *)&ani_buffer[decode_index+2],"Initialize")!=0)
                start_frame_count=1;		// 開始計算 Frame
            else
                start_frame_count=0;
            break;
        case ANI_DATABASE:                      // DataBase Command
            if(start_frame_count==1)
            {
                temp_total_frame[total_ani_frame]=node_idx;
                total_ani_frame++;
            }
            if(database_node!=ROOT_NODE)
            {
                effect_node1=add_mda_child_node(database_node,&node_idx,&ani_buffer[decode_index+2],mda_group_index);
            }
            total_database_frame++;
            break;
        case ANI_EFFECT1:                       // Effect Command
            if(effect_node1!=NULL)
            {
                effect_node2=add_mda_child_node(effect_node1,&node_idx,&ani_buffer[decode_index+2],mda_group_index);
            }
            break;
        case ANI_EFFECT2:                       // Effect Command
            if(effect_node2!=NULL)
            {
                add_mda_child_node(effect_node2,&node_idx,&ani_buffer[decode_index+2],mda_group_index);
            }
            break;
        }
        decode_index=decode_index+command_length;
        if(decode_index>=body_size)
            main_pass=1;
    }

    mda_group[mda_group_index].total_frame[main_command_index]=
        total_database_frame;

    // ----- update equ node
    for(i=0;i<total_node;i++)
    {
        if(mda_group[mda_group_index].command_node[i].equ_node==END_NODE)
        {
            father_node=mda_group[mda_group_index].command_node[i].father_node;
            for(j=i+1;j<total_node;j++)		// find start next
            {
                if(mda_group[mda_group_index].command_node[j].father_node==father_node)
                {
                    mda_group[mda_group_index].command_node[i].equ_node=j;
                    j=total_node;
                    break;
                }
            }
        }
    }

    mda_group[mda_group_index].total_ani_frame=total_ani_frame;
    // ---- creat dire frame node
    mda_group[mda_group_index].dire_frame_node=(ULONG *)malloc(sizeof(ULONG)*total_ani_frame);
    if(mda_group[mda_group_index].dire_frame_node==NULL)
    {
        display_message((UCHR *)"Memory Error(total_frame)",true);
        return;
    }
    memcpy(mda_group[mda_group_index].dire_frame_node,
        temp_total_frame,sizeof(ULONG)*total_ani_frame);
    free(temp_total_frame);


    // ------
    /* 除錯用
    for(i=0;i<total_node;i++)
    {
    sprintf((char *)print_rec,"%d Father:%d Child:%d EQu:%d Str:%s %d",
    i,
    mda_group[mda_group_index].command_node[i].father_node,
    mda_group[mda_group_index].command_node[i].chind_node,
    mda_group[mda_group_index].command_node[i].equ_node,
    mda_group[mda_group_index].command_node[i].body_idx,
    mda_group[mda_group_index].command_node[i].database_idx);
    log_error(1,print_rec);
    }
    */

}


ULONG add_mda_child_node(ULONG father_node,SLONG *node_idx,UCHR *body_index,SLONG mda_group_index)
{
    ULONG index;
    UCHR database_filename[256];
    SLONG database_no;

    index=(ULONG)*node_idx;
    mda_group[mda_group_index].command_node[index].father_node=father_node;
    mda_group[mda_group_index].command_node[index].chind_node=END_NODE;
    mda_group[mda_group_index].command_node[index].equ_node=END_NODE;
    mda_group[mda_group_index].command_node[index].body_idx=body_index;
    strcpy((char *)database_filename,(char *)body_index);
    database_no=find_database(mda_group_index,database_filename);
    if(database_no!=TTN_NOT_OK)
        mda_group[mda_group_index].command_node[index].database_idx=database_no;

    if(father_node!=ROOT_NODE)
    {
        if(mda_group[mda_group_index].command_node[father_node].chind_node==END_NODE)
        {
            mda_group[mda_group_index].command_node[father_node].chind_node=index;
        }
    }

    if(index>0)
    {
        if(mda_group[mda_group_index].command_node[index-1].father_node==
            mda_group[mda_group_index].command_node[index].father_node)
        {
            mda_group[mda_group_index].command_node[index-1].equ_node=index;
        }
    }


    *node_idx=index+1;
    return(index);
}



SLONG mda_group_exec(SLONG handle,UCHR *command,SLONG x,SLONG y,BMP *bitmap,SLONG mda_command,SLONG value,SLONG alpha_value,SLONG frame_value)
{
    SLONG mda_group_index;
    SLONG command_no;
    SLONG database_no;
    SLONG now_frame;
    UCHR database_text[255];
    SLONG offset,size;
    SLONG media_type;
    UCHR *data_buffer=NULL;
    SLONG ret_val;
    SLONG i;
    SLONG x_off,y_off;
    UCHR backup_palette[768];
    bool zoom_flag=false;
    bool next_frame_flag=false;
    bool first_frame_flag=false;
    bool last_frame_flag=false;
    bool loop_frame_flag=false;
    bool alpha_flag=false;
    bool hight_light_flag=false;
    bool assign_flag=false;
    bool palette_flag=false;
    bool palette_or_flag=false;
    bool palette_and_flag=false;
    UCHR message[255];
    ULONG maincommand_node;
    ULONG database_node;
    ULONG effect_node;
    ULONG temp_node;

    if(handle<0)return(MDA_EXEC_ERROR);
    goto_frame=-1;

    // ---- decode mda command
    if(mda_command&MDA_COMMAND_ZOOM)
        zoom_flag=true;
    if(mda_command&MDA_COMMAND_NEXT_FRAME)
        next_frame_flag=true;
    if(mda_command&MDA_COMMAND_FIRST)
        first_frame_flag=true;
    if(mda_command&MDA_COMMAND_LAST)
        last_frame_flag=true;
    if(mda_command&MDA_COMMAND_LOOP)
        loop_frame_flag=true;
    if(mda_command&MDA_COMMAND_ALPHA)
        alpha_flag=true;
    if(mda_command&MDA_COMMAND_HIGHTLIGHT)
        hight_light_flag=true;
    if(mda_command&MDA_COMMAND_ASSIGN)
        assign_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE)
        palette_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE_OR)
        palette_or_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE_AND)
        palette_and_flag=true;



    // ---- Get mda_group index
    mda_group_index=get_mda_index(handle);
    if(mda_group_index<0)return(MDA_EXEC_ERROR);
    if(mda_group[mda_group_index].total_ani_command<=0)
        return(MDA_EXEC_OK);
    // ---- OK ! next get 
    if(command!=NULL)	
    {
        command_no=get_maincommand_no(command,ROOT_NODE,mda_group_index,&maincommand_node);

        if(command_no<0)
        {
            sprintf((char *)message,"%s command error",command);
            display_message(message,true);
            return(MDA_EXEC_ERROR);
        }
        if(first_frame_flag)
            mda_group[mda_group_index].now_frame[command_no]=0;
        if(last_frame_flag)
            mda_group[mda_group_index].now_frame[command_no]=mda_group[mda_group_index].total_frame[command_no]-1;
        if(assign_flag)
            mda_group[mda_group_index].now_frame[command_no]=frame_value;

        now_frame=mda_group[mda_group_index].now_frame[command_no];

        database_node=get_database_no(now_frame,maincommand_node,mda_group_index,database_text);
        database_no=mda_group[mda_group_index].command_node[database_node].database_idx;
    }
    else
    {
        command_no=0;
        now_frame=0;
        if(frame_value>=mda_group[mda_group_index].total_ani_frame)
            return(MDA_EXEC_ERROR);
        database_node=mda_group[mda_group_index].dire_frame_node[frame_value];
        database_no=mda_group[mda_group_index].command_node[database_node].database_idx;
        strcpy((char *)database_text,(char *)mda_group[mda_group_index].command_node[database_node].body_idx);
    }



    if(database_node==TTN_NOT_OK)
    {
        sprintf((char *)message,"DataBase Frame Error(%d)",now_frame);
        display_message(message,true);
        return(MDA_EXEC_ERROR);
    }

    if(database_text[0]=='*')		// System command
    {
        temp_node=mda_group[mda_group_index].command_node[database_node].chind_node;
        i=0;
        while(temp_node!=END_NODE)
        {
            database_no=mda_group[mda_group_index].command_node[temp_node].database_idx;
            if(database_no>=0)
            {
                offset=mda_group[mda_group_index].database_index[database_no].offset;
                size=mda_group[mda_group_index].database_index[database_no].size;
                data_buffer=&mda_group[mda_group_index].body[offset];
                media_type=check_media_type(data_buffer);
                mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;

                x_off=mda_group[mda_group_index].img256_head->orig_x+mda_group[mda_group_index].img256_head->center_x;
                y_off=mda_group[mda_group_index].img256_head->orig_y+mda_group[mda_group_index].img256_head->center_y;

                // Jack, Added here... [1/22/2003]
                // How to effect x/y to x_off/y_off ???

                // Jack, For change equip npc, add special effect control here. [1/21/2003]
                //
                // PS: Highlight can't compatibel with alpha, so skip alpha control here.
                // Jack, TODO for add blue alpha effect ... [1/24/2003]
                /*
                if((palette_or_flag)||(palette_flag)||(palette_and_flag))
                {
                memcpy(backup_palette,mda_group[mda_group_index].img256_head->palette,768);
                for(i=0;i<768;i++)
                {
                if(palette_flag)
                mda_group[mda_group_index].img256_head->palette[i]=system_palette[i];
                if(palette_or_flag)
                mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]|system_palette[i];
                if(palette_and_flag)
                mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]&system_palette[i];
                }
                }
                */

                if(hight_light_flag)
                {
                    display_rgb_img256_buffer_with_highlight(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap);
                }
                else if(alpha_flag)
                {
                    display_rgb_img256_buffer_with_alpha(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap, alpha_value);
                }
                else
                {
                    display_rgb_img256_buffer(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap);
                }

            }
            i++;
            temp_node=mda_group[mda_group_index].command_node[temp_node].equ_node;
        }

        goto skip_command;
    }

    if(database_no<0)			// It's a user command
    {
        exec_user_command(database_text,data_buffer);
    }
    else
    {
        offset=mda_group[mda_group_index].database_index[database_no].offset;
        size=mda_group[mda_group_index].database_index[database_no].size;

        data_buffer=&mda_group[mda_group_index].body[offset];
        media_type=check_media_type(data_buffer);
        switch(media_type)
        {
        case FILE_TYPE_UNKNOW:
            exec_user_command(database_text,data_buffer);
            break;
        case FILE_TYPE_WAV:
            // Jack, remark for cancel voice play for SeaAge. [1/21/2003]
            //auto_play_buffer_voice(data_buffer,size,0,0);		// vol
            break;
        case FILE_TYPE_IMG:
            mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;
            if((palette_or_flag)||(palette_flag)||(palette_and_flag))
            {
                memcpy(backup_palette,mda_group[mda_group_index].img256_head->palette,768);
                for(i=0;i<768;i++)
                {
                    if(palette_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=system_palette[i];
                    if(palette_or_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]|system_palette[i];
                    if(palette_and_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]&system_palette[i];
                }
            }

            if(hight_light_flag)
            {
                if(zoom_flag)
                    display_hightlight_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                else
                    display_hightlight_img256_buffer(x,y,data_buffer,bitmap);
            }
            else
            {
                if(alpha_flag)
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer_alpha(x,y,data_buffer,bitmap,value,alpha_value);
                    else
                        display_img256_buffer_alpha(x,y,data_buffer,bitmap,alpha_value);
                }
                else
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                    else
                        display_img256_buffer(x,y,data_buffer,bitmap);
                }
            }
            break;
        }
    }



    effect_node=mda_group[mda_group_index].command_node[database_node].chind_node;
    while(effect_node!=END_NODE)
    {
        database_no=mda_group[mda_group_index].command_node[effect_node].database_idx;
        strcpy((char *)database_text,(char *)mda_group[mda_group_index].command_node[effect_node].body_idx);
        if(database_no<0)			// It's a user command
        {
            exec_user_command(database_text,data_buffer);
        }
        else
        {
            offset=mda_group[mda_group_index].database_index[database_no].offset;
            size=mda_group[mda_group_index].database_index[database_no].size;

            data_buffer=&mda_group[mda_group_index].body[offset];
            media_type=check_media_type(data_buffer);
            switch(media_type)
            {
            case FILE_TYPE_UNKNOW:
                exec_user_command(database_text,data_buffer);
                break;
            case FILE_TYPE_WAV:
                // Jack, remark for cancel voice play for SeaAge. [1/21/2003]
                //auto_play_buffer_voice(data_buffer,size,0,0);		// vol
                break;
            case FILE_TYPE_IMG:
                mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;
                if((palette_or_flag)||(palette_flag)||(palette_and_flag))
                {
                    memcpy(backup_palette,mda_group[mda_group_index].img256_head->palette,768);
                    for(i=0;i<768;i++)
                    {
                        if(palette_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=system_palette[i];
                        if(palette_or_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]|system_palette[i];
                        if(palette_and_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]&system_palette[i];
                    }
                }
                if(alpha_flag)
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer_alpha(x,y,data_buffer,bitmap,value,alpha_value);
                    else
                        display_img256_buffer_alpha(x,y,data_buffer,bitmap,alpha_value);
                }
                else
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                    else
                        display_img256_buffer(x,y,data_buffer,bitmap);
                }
                break;
            }
        }
        effect_node=mda_group[mda_group_index].command_node[effect_node].equ_node;
    }



skip_command:	

    ret_val=MDA_EXEC_OK;
    if(now_frame==0)
        ret_val=MDA_EXEC_FIRST;
    // --- Loop control
    if(next_frame_flag)
    {
        now_frame++;
        mda_group[mda_group_index].now_frame[command_no]=now_frame;

        if(now_frame>=mda_group[mda_group_index].total_frame[command_no])
        {
            ret_val=MDA_EXEC_LAST;
            if(loop_frame_flag)
                mda_group[mda_group_index].now_frame[command_no]=0;
            else
                mda_group[mda_group_index].now_frame[command_no]=mda_group[mda_group_index].total_frame[command_no]-1;
        }
    }

    // -----User command
    if((goto_frame>=0)&&(goto_frame<=mda_group[mda_group_index].total_frame[command_no]-1))
        mda_group[mda_group_index].now_frame[command_no]=goto_frame;

    if((palette_or_flag)||(palette_flag)||(palette_and_flag))
        memcpy(mda_group[mda_group_index].img256_head->palette,backup_palette,768);

    return(ret_val);
}


SLONG mda_group_exec_with_position(SLONG handle,UCHR *command,SLONG x,SLONG y,BMP *bitmap,SLONG mda_command,SLONG value,SLONG alpha_value,SLONG frame_value)
{
    SLONG mda_group_index;
    SLONG command_no;
    SLONG database_no;
    SLONG now_frame;
    UCHR database_text[255];
    SLONG offset,size;
    SLONG media_type;
    UCHR *data_buffer=NULL;
    SLONG ret_val;
    SLONG i;
    SLONG x_off,y_off;
    UCHR backup_palette[768];
    bool zoom_flag=false;
    bool next_frame_flag=false;
    bool first_frame_flag=false;
    bool last_frame_flag=false;
    bool loop_frame_flag=false;
    bool alpha_flag=false;
    bool hight_light_flag=false;
    bool assign_flag=false;
    bool palette_flag=false;
    bool palette_or_flag=false;
    bool palette_and_flag=false;
    UCHR message[255];
    ULONG maincommand_node;
    ULONG database_node;
    ULONG effect_node;
    ULONG temp_node;

    if(handle<0)return(MDA_EXEC_ERROR);
    goto_frame=-1;

    // ---- decode mda command
    if(mda_command&MDA_COMMAND_ZOOM)
        zoom_flag=true;
    if(mda_command&MDA_COMMAND_NEXT_FRAME)
        next_frame_flag=true;
    if(mda_command&MDA_COMMAND_FIRST)
        first_frame_flag=true;
    if(mda_command&MDA_COMMAND_LAST)
        last_frame_flag=true;
    if(mda_command&MDA_COMMAND_LOOP)
        loop_frame_flag=true;
    if(mda_command&MDA_COMMAND_ALPHA)
        alpha_flag=true;
    if(mda_command&MDA_COMMAND_HIGHTLIGHT)
        hight_light_flag=true;
    if(mda_command&MDA_COMMAND_ASSIGN)
        assign_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE)
        palette_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE_OR)
        palette_or_flag=true;
    if(mda_command&MDA_COMMAND_PALETTE_AND)
        palette_and_flag=true;



    // ---- Get mda_group index
    mda_group_index=get_mda_index(handle);
    if(mda_group_index<0)return(MDA_EXEC_ERROR);
    if(mda_group[mda_group_index].total_ani_command<=0)
        return(MDA_EXEC_OK);
    // ---- OK ! next get 
    if(command!=NULL)	
    {
        command_no=get_maincommand_no(command,ROOT_NODE,mda_group_index,&maincommand_node);

        if(command_no<0)
        {
            sprintf((char *)message,"%s command error",command);
            display_message(message,true);
            return(MDA_EXEC_ERROR);
        }
        if(first_frame_flag)
            mda_group[mda_group_index].now_frame[command_no]=0;
        if(last_frame_flag)
            mda_group[mda_group_index].now_frame[command_no]=mda_group[mda_group_index].total_frame[command_no]-1;
        if(assign_flag)
            mda_group[mda_group_index].now_frame[command_no]=frame_value;

        now_frame=mda_group[mda_group_index].now_frame[command_no];

        database_node=get_database_no(now_frame,maincommand_node,mda_group_index,database_text);
        database_no=mda_group[mda_group_index].command_node[database_node].database_idx;
    }
    else
    {
        command_no=0;
        now_frame=0;
        if(frame_value>=mda_group[mda_group_index].total_ani_frame)
            return(MDA_EXEC_ERROR);
        database_node=mda_group[mda_group_index].dire_frame_node[frame_value];
        database_no=mda_group[mda_group_index].command_node[database_node].database_idx;
        strcpy((char *)database_text,(char *)mda_group[mda_group_index].command_node[database_node].body_idx);
    }



    if(database_node==TTN_NOT_OK)
    {
        sprintf((char *)message,"DataBase Frame Error(%d)",now_frame);
        display_message(message,true);
        return(MDA_EXEC_ERROR);
    }

    if(database_text[0]=='*')		// System command
    {
        temp_node=mda_group[mda_group_index].command_node[database_node].chind_node;
        i=0;
        while(temp_node!=END_NODE)
        {
            database_no=mda_group[mda_group_index].command_node[temp_node].database_idx;
            if(database_no>=0)
            {
                offset=mda_group[mda_group_index].database_index[database_no].offset;
                size=mda_group[mda_group_index].database_index[database_no].size;
                data_buffer=&mda_group[mda_group_index].body[offset];
                media_type=check_media_type(data_buffer);
                mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;

                x_off = mda_group[mda_group_index].img256_head->orig_x+mda_group[mda_group_index].img256_head->center_x;
                y_off = mda_group[mda_group_index].img256_head->orig_y+mda_group[mda_group_index].img256_head->center_y;

                // Jack, add mda group effect here. [1/22/2003]
                x_off += x - mda_group[mda_group_index].offset_x;
                y_off += y - mda_group[mda_group_index].offset_y;

                // Jack, For change equip npc, add special effect control here. [1/21/2003]
                //
                // PS: Highlight can't compatibel with alpha, so skip alpha control here.
                if(hight_light_flag)
                {
                    display_rgb_img256_buffer_with_highlight(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap);
                }
                else if(alpha_flag)
                {
                    display_rgb_img256_buffer_with_alpha(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap, alpha_value);
                }
                else
                {
                    display_rgb_img256_buffer(x_off,y_off,&mda_group[mda_group_index].sea_rgb_data[i],data_buffer,bitmap);
                }
            }
            i++;
            temp_node=mda_group[mda_group_index].command_node[temp_node].equ_node;
        }

        goto skip_command;
    }

    if(database_no<0)			// It's a user command
    {
        exec_user_command(database_text,data_buffer);
    }
    else
    {
        offset=mda_group[mda_group_index].database_index[database_no].offset;
        size=mda_group[mda_group_index].database_index[database_no].size;

        data_buffer=&mda_group[mda_group_index].body[offset];
        media_type=check_media_type(data_buffer);
        switch(media_type)
        {
        case FILE_TYPE_UNKNOW:
            exec_user_command(database_text,data_buffer);
            break;
        case FILE_TYPE_WAV:
            // Jack, remark for cancel voice play for SeaAge. [1/21/2003]
            //auto_play_buffer_voice(data_buffer,size,0,0);		// vol
            break;
        case FILE_TYPE_IMG:
            mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;
            if((palette_or_flag)||(palette_flag)||(palette_and_flag))
            {
                memcpy(backup_palette,mda_group[mda_group_index].img256_head->palette,768);
                for(i=0;i<768;i++)
                {
                    if(palette_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=system_palette[i];
                    if(palette_or_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]|system_palette[i];
                    if(palette_and_flag)
                        mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]&system_palette[i];
                }
            }

            if(hight_light_flag)
            {
                if(zoom_flag)
                    display_hightlight_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                else
                    display_hightlight_img256_buffer(x,y,data_buffer,bitmap);
            }
            else
            {
                if(alpha_flag)
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer_alpha(x,y,data_buffer,bitmap,value,alpha_value);
                    else
                        display_img256_buffer_alpha(x,y,data_buffer,bitmap,alpha_value);
                }
                else
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                    else
                        display_img256_buffer(x,y,data_buffer,bitmap);
                }
            }
            break;
        }
    }



    effect_node=mda_group[mda_group_index].command_node[database_node].chind_node;
    while(effect_node!=END_NODE)
    {
        database_no=mda_group[mda_group_index].command_node[effect_node].database_idx;
        strcpy((char *)database_text,(char *)mda_group[mda_group_index].command_node[effect_node].body_idx);
        if(database_no<0)			// It's a user command
        {
            exec_user_command(database_text,data_buffer);
        }
        else
        {
            offset=mda_group[mda_group_index].database_index[database_no].offset;
            size=mda_group[mda_group_index].database_index[database_no].size;

            data_buffer=&mda_group[mda_group_index].body[offset];
            media_type=check_media_type(data_buffer);
            switch(media_type)
            {
            case FILE_TYPE_UNKNOW:
                exec_user_command(database_text,data_buffer);
                break;
            case FILE_TYPE_WAV:
                // Jack, remark for cancel voice play for SeaAge. [1/21/2003]
                //auto_play_buffer_voice(data_buffer,size,0,0);		// vol
                break;
            case FILE_TYPE_IMG:
                mda_group[mda_group_index].img256_head=(struct IMG256_HEAD_STRUCT *)data_buffer;
                if((palette_or_flag)||(palette_flag)||(palette_and_flag))
                {
                    memcpy(backup_palette,mda_group[mda_group_index].img256_head->palette,768);
                    for(i=0;i<768;i++)
                    {
                        if(palette_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=system_palette[i];
                        if(palette_or_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]|system_palette[i];
                        if(palette_and_flag)
                            mda_group[mda_group_index].img256_head->palette[i]=mda_group[mda_group_index].img256_head->palette[i]&system_palette[i];
                    }
                }
                if(alpha_flag)
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer_alpha(x,y,data_buffer,bitmap,value,alpha_value);
                    else
                        display_img256_buffer_alpha(x,y,data_buffer,bitmap,alpha_value);
                }
                else
                {
                    if(zoom_flag)
                        display_zoom_img256_buffer(x,y,data_buffer,bitmap,value);
                    else
                        display_img256_buffer(x,y,data_buffer,bitmap);
                }
                break;
            }
        }
        effect_node=mda_group[mda_group_index].command_node[effect_node].equ_node;
    }



skip_command:	

    ret_val=MDA_EXEC_OK;
    if(now_frame==0)
        ret_val=MDA_EXEC_FIRST;
    // --- Loop control
    if(next_frame_flag)
    {
        now_frame++;
        mda_group[mda_group_index].now_frame[command_no]=now_frame;

        if(now_frame>=mda_group[mda_group_index].total_frame[command_no])
        {
            ret_val=MDA_EXEC_LAST;
            if(loop_frame_flag)
                mda_group[mda_group_index].now_frame[command_no]=0;
            else
                mda_group[mda_group_index].now_frame[command_no]=mda_group[mda_group_index].total_frame[command_no]-1;
        }
    }

    // -----User command
    if((goto_frame>=0)&&(goto_frame<=mda_group[mda_group_index].total_frame[command_no]-1))
        mda_group[mda_group_index].now_frame[command_no]=goto_frame;

    if((palette_or_flag)||(palette_flag)||(palette_and_flag))
        memcpy(mda_group[mda_group_index].img256_head->palette,backup_palette,768);

    return(ret_val);
}


ULONG get_maincommand_no(UCHR *command,SLONG father_node,SLONG mda_group_index,ULONG *maincommand_node)
{
    SLONG main_pass;
    SLONG now_node;
    SLONG command_no;

    now_node=0;
    main_pass=0;
    command_no=0;
    while(main_pass==0)
    {	
        if(strcmpi((char *)mda_group[mda_group_index].command_node[now_node].body_idx,
            (char *)command)==0)		// Ok Find 
        {
            *maincommand_node=now_node;
            return(command_no);
        }
        now_node=mda_group[mda_group_index].command_node[now_node].equ_node;	// change to next node				
        if(now_node==END_NODE)
        {
            display_message((UCHR *)"Mda tree error!(Main command)",1);
            *maincommand_node=-1;
            return(TTN_NOT_OK);
        }
        command_no++;
    }
    return(TTN_NOT_OK);
}


SLONG get_database_no(SLONG now_frame,ULONG maincommand_node,SLONG mda_group_index,UCHR *database_text)
{
    ULONG now_node;
    SLONG database_no;
    SLONG main_pass;


    now_node=mda_group[mda_group_index].command_node[maincommand_node].chind_node;
    if(now_node==END_NODE)		// Error
    {
        strcpy((char *)database_text,"");
        return(TTN_NOT_OK);
    }

    database_no=0;
    main_pass=0;
    while(main_pass==0)
    {
        if(database_no==now_frame)		// Ok Match find frame no
        {
            strcpy((char *)database_text,(char *)mda_group[mda_group_index].command_node[now_node].body_idx);
            return(now_node);
        }
        now_node=mda_group[mda_group_index].command_node[now_node].equ_node;
        if(now_node==END_NODE)
        {
            display_message((UCHR *)"MDA tree error!!!(database command)",1);
            strcpy((char *)database_text,"");
            main_pass=1;
        }
        database_no++;
    }	
    return(TTN_NOT_OK);
}



SLONG check_media_type(UCHR *data_buffer)
{
    SLONG media_type;

    media_type=FILE_TYPE_UNKNOW;
    if(check_is_wav_type(data_buffer)==TTN_OK)
        media_type=FILE_TYPE_WAV;
    else if (check_is_img256_type(data_buffer)==TTN_OK)
        media_type=FILE_TYPE_IMG;
    else
        media_type=FILE_TYPE_UNKNOW;

    return(media_type);

}


SLONG check_is_mda_file(UCHR *filename)
{
    FILE *fp;
    MDA_HEAD temp_mda_head;

    fp=fopen((char *)filename,"rb");
    if(fp==NULL)
        return(TTN_NOT_OK);
    fread(&temp_mda_head,sizeof(struct MDA_HEAD_STRUCT),1,fp);
    fclose(fp);
    if(strcmpi((char *)temp_mda_head.copyright,"RAYS MEDIA FILE")!=0)
        return(TTN_NOT_OK);
    return(TTN_OK);
}


SLONG check_is_wav_type(UCHR *data_buffer)
{
    UCHR temp[30];

    memcpy(temp,data_buffer,20);
    if((temp[8]!='W')||(temp[9]!='A')||
        (temp[10]!='V')||(temp[11]!='E'))
        return(TTN_NOT_OK);
    return(TTN_OK);
}


SLONG check_is_img256_type(UCHR *data_buffer)
{
    IMG256_HEAD temp_img256_head;

    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    if(strcmpi((char *)temp_img256_head.copyright,"RAYS IMG256 FILE")!=0)
        return(TTN_NOT_OK);
    return(TTN_OK);
}


SLONG find_database(SLONG mda_group_index,UCHR *database_text)
{
    SLONG ret_val;
    SLONG i;

    ret_val=TTN_NOT_OK;
    for(i=0;i<mda_group[mda_group_index].total_database;i++)
    {
        if(strcmpi((char *)mda_group[mda_group_index].database_index[i].name,(char *)database_text)==0)
        {
            ret_val=i;
            return(ret_val);
        }
    }
    return(ret_val);
}


void exec_user_command(UCHR *src_command,UCHR *data_buffer)
{
    SLONG idx;
    UCHR command[255];
    UCHR value[255];
    UCHR message[255];

    goto_frame=-1;
    take_space(src_command);
    idx=0;
    get_part_str(src_command,command,&idx,' ',200);
    if(strcmpi((char *)command,"attack")==0)					// 攻擊開始
    {
        idx++;
        get_part_str(src_command,value,&idx,' ',200);
        attack_start=1;
        attack_value=atoi((char *)value);
    }
    else if(strcmpi((char *)command,"goto")==0)					// Goto Frame
    {
        idx++;
        get_part_str(src_command,value,&idx,' ',200);
        goto_frame=atoi((char *)value);
    }
    else if(strcmpi((char *)command,"front")==0)				// 向前衝開始
        front_start=1;
    else if(strcmpi((char *)command,"magic")==0)				// 開使顯示魔法
        magic_start=1;
    else if(strcmpi((char *)command,"MaxDir")==0)				// Max dir
    {
        idx++;
        get_part_str(src_command,value,&idx,'=',200);
        AssemMaxDir=atoi((char *)value);
    }
    else if(strcmpi((char *)command,"MaxPart")==0)				// Max Part
    {
        idx++;
        get_part_str(src_command,value,&idx,'=',200);
        AssemMaxPart=atoi((char *)value);
    }
    else
    {
        sprintf((char *)message,"Unknow Command :%s",command);
        display_message(message,true);
    }
}



void take_space(UCHR *data)
{
    SLONG i;
    SLONG j;
    SLONG pass;
    UCHR temp[255];

    j=0;
    pass=0;
    memset(temp,0x00,254);
    for(j=0,i=0;i<(SLONG)strlen((const char *)data);i++)
    {
        if(((data[i]==' ')||(data[i]==0x09))&&(pass==0))
            continue;
        else
        {
            pass=1;
            temp[j]=data[i];
            j=j+1;
        }
    }
    temp[j]=(UCHR)NULL;
    strcpy((char *)data,(char *)temp);
}


void get_part_str(UCHR *in,UCHR *out,SLONG *idx,UCHR key,SLONG max)
{
    SLONG i,j;
    UCHR skip_char;

    skip_char=' ';
    for(j=0,i=*idx;i<(SLONG)strlen((const char *)in);i++)
    {
        if(j>=max)
        {
            out[j]=(UCHR)NULL;
            *idx=i;
            skip_char=(UCHR)NULL;
            return;
        }
        else if(key!=(UCHR)NULL)
        {
            switch(in[i])
            {
            case '=': case ',':
                out[j]=(UCHR)NULL;
                *idx=i;
                skip_char=in[i];
                return;
            case ' ':
                continue;
            default:
                break;
            }
        }
        out[j]=in[i];
        j=j+1;
    }
    out[j]=(UCHR)NULL;
    skip_char=(UCHR)NULL;
    *idx=i;
}

SLONG check_file_exist(UCHR *filename)
{
    FILE *fp;

    if(filename[0]==0x00)return(TTN_NOT_OK);
    fp=fopen((const char *)filename,"rb");
    if(fp==NULL)
        return(TTN_NOT_OK);

    fclose(fp);
    return(TTN_OK);

}


SLONG read_mda_image(UCHR *mda_filename,SLONG frame_no,IMG256_IMAGE *img256_image)
{
    FILE *fp;
    MDA_HEAD temp_mda_head;
    INDEX_OFFSET_SIZE *index=NULL;
    SLONG offset,size;
    UCHR message[255];

    if(check_file_exist(mda_filename)!=TTN_OK)
    {
        sprintf((char *)message,"File %s open error",mda_filename);
        display_message(message,true);
        return(TTN_NOT_OK);
    }
    if(check_is_mda_file(mda_filename)!=TTN_OK)
    {
        sprintf((char *)message,"File %s type error",mda_filename);
        display_message(message,true);
        return(TTN_NOT_OK);
    }

    fp=fopen((char *)mda_filename,"rb");
    if(fp==NULL)
        return(TTN_NOT_OK);
    fread(&temp_mda_head,sizeof(struct MDA_HEAD_STRUCT),1,fp);
    if((temp_mda_head.total_database_frame<=0)||
        (frame_no>=temp_mda_head.total_database_frame))
    {
        sprintf((char *)message,"Read mda frame no error (%d/%d)",frame_no,temp_mda_head.total_database_frame);
        display_message(message,true);
        fclose(fp);
        return(TTN_NOT_OK);
    }
    fseek(fp,temp_mda_head.data_start_offset,SEEK_SET);
    index=(struct INDEX_OFFSET_SIZE_STRUCT *)malloc(sizeof(struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame);
    if(index==NULL)
    {
        display_message((UCHR *)"內存不足",true);
        fclose(fp);
        return(TTN_NOT_OK);
    }
    fread(index,sizeof( struct INDEX_OFFSET_SIZE_STRUCT)*temp_mda_head.total_database_frame,1,fp);
    offset=index[frame_no].offset;
    size=index[frame_no].size;
    fseek(fp,offset,SEEK_SET);

    img256_image->image=(UCHR *)malloc(sizeof(UCHR)*size);
    if(img256_image->image==NULL)
    {
        display_message((UCHR *)"內存不足",true);
        free(index);
        fclose(fp);
        return(TTN_NOT_OK);
    }
    fread(img256_image->image,sizeof(UCHR)*size,1,fp);
    memcpy(&img256_image->img256_head,img256_image->image,sizeof(struct IMG256_HEAD_STRUCT));
    fclose(fp);
    free(index);
    return(TTN_OK);

}


void display_rgb_img256_buffer(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UHINT color;
    UCHR alpha;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[255];

    // ------- Add 換裝參數 ----
    UCHR r,g,b;
    UCHR r_offset,g_offset,b_offset;
    SLONG rgb_effect;
    UCHR effect;
    //SLONG temp_r,temp_g,temp_b;
    bool scroll_color;
    //SLONG xstart;


    r_offset=0;
    g_offset=0;
    b_offset=0;
    effect=rgb_data->effect;
    if((effect&0xF0)&RGB_EFFECT_ANI_R)     // 清除 Low byte
        r_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_G)
        g_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_B)
        b_offset=16;
    if((effect&0x0F)&RGB_EFFECT_COPY)
        rgb_effect=RGB_EFFECT_COPY;
    else if((effect&0x0F)&RGB_EFFECT_AND)
        rgb_effect=RGB_EFFECT_AND;
    else if((effect&0x0F)&RGB_EFFECT_OR)
        rgb_effect=RGB_EFFECT_OR;
    else if((effect&0x0F)&RGB_EFFECT_NOT)
        rgb_effect=RGB_EFFECT_NOT;
    else
        rgb_effect=RGB_EFFECT_NONE;

    if(r_offset+g_offset+b_offset!=0)
        scroll_color=true;
    else
        scroll_color=false;

    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    // stephen
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // Stephen Add [2003/2/11]
    switch(change_color_flag)
    {
    default:
    case 0:			// None
        break;
    case 1:			// Rebuild palette
        switch(rgb_effect)
        {
        default:
        case RGB_EFFECT_NONE:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=temp_img256_head.palette[index];
                change_color_palette[index+1]=temp_img256_head.palette[index+1];
                change_color_palette[index+2]=temp_img256_head.palette[index+2];
            }
            break;
        case RGB_EFFECT_COPY:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=rgb_data->r;
                change_color_palette[index+1]=rgb_data->g;
                change_color_palette[index+2]=rgb_data->b;
            }
            break;
        case RGB_EFFECT_AND:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=oper_and_color(temp_img256_head.palette[index],rgb_data->r);
                change_color_palette[index+1]=oper_and_color(temp_img256_head.palette[index+1],rgb_data->g);
                change_color_palette[index+2]=oper_and_color(temp_img256_head.palette[index+2],rgb_data->b);
            }
            break;
        case RGB_EFFECT_OR:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=temp_img256_head.palette[index]|rgb_data->r;
                change_color_palette[index+1]=temp_img256_head.palette[index+1]|rgb_data->g;
                change_color_palette[index+2]=temp_img256_head.palette[index+1]|rgb_data->b;
            }
            break;
        case RGB_EFFECT_NOT:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=~temp_img256_head.palette[index];
                change_color_palette[index+1]=~temp_img256_head.palette[index+1];
                change_color_palette[index+2]=~temp_img256_head.palette[index+2];
            }
            break;
        }
        break;
    }




    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                    alpha=img256_buffer[decode_index+(i<<1)+1];

                    r=change_color_palette[index];
                    g=change_color_palette[index+1];
                    b=change_color_palette[index+2];

                    /*					
                    switch(rgb_effect)
                    {
                    default:
                    case RGB_EFFECT_NONE:
                    r=temp_img256_head.palette[index];
                    g=temp_img256_head.palette[index+1];
                    b=temp_img256_head.palette[index+2];
                    break;
                    case RGB_EFFECT_COPY:
                    r=rgb_data->r;
                    g=rgb_data->g;
                    b=rgb_data->b;
                    break;
                    case RGB_EFFECT_AND:
                    r=temp_img256_head.palette[index]&rgb_data->r;
                    g=temp_img256_head.palette[index+1]&rgb_data->g;
                    b=temp_img256_head.palette[index+2]&rgb_data->b;
                    break;
                    case RGB_EFFECT_OR:
                    r=temp_img256_head.palette[index]|rgb_data->r;
                    g=temp_img256_head.palette[index+1]|rgb_data->g;
                    b=temp_img256_head.palette[index+2]|rgb_data->b;
                    break;
                    case RGB_EFFECT_NOT:
                    r=~temp_img256_head.palette[index];
                    g=~temp_img256_head.palette[index+1];
                    b=~temp_img256_head.palette[index+2];
                    break;
                    }
                    */

                    color=rgb2hi(r,g,b);
                    oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],(SLONG) alpha);

                }
                /*						else
                {
                i=copy_length;
                }
                */
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


    if(scroll_color)
    {
        if(rgb_data->r>=240)
            rgb_data->scroll=rgb_data->scroll|0x01;
        else if(rgb_data->r<=20)
            rgb_data->scroll=rgb_data->scroll&0xF7;

        if(rgb_data->g>=240)
            rgb_data->scroll=rgb_data->scroll|0x02;
        else if(rgb_data->g<=20)
            rgb_data->scroll=rgb_data->scroll&0xFD;

        if(rgb_data->b>=240)
            rgb_data->scroll=rgb_data->scroll|0x04;
        else if(rgb_data->b<=20)
            rgb_data->scroll=rgb_data->scroll&0xFB;



        if(rgb_data->scroll&0x01)
            rgb_data->r-=r_offset;
        else
            rgb_data->r+=r_offset;

        if(rgb_data->scroll&0x02)
            rgb_data->g-=g_offset;
        else
            rgb_data->g+=g_offset;

        if(rgb_data->scroll&0x04)
            rgb_data->b-=b_offset;
        else
            rgb_data->b+=b_offset;
    }
}


void display_rgb_img256_buffer_with_highlight(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UCHR alpha;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[255];

    // ------- Add 換裝參數 ----
    UCHR r,g,b;
    UCHR r_offset,g_offset,b_offset;
    SLONG rgb_effect;
    UCHR effect;
    //SLONG temp_r,temp_g,temp_b;
    bool scroll_color;
    //SLONG xstart;


    r_offset=0;
    g_offset=0;
    b_offset=0;
    effect=rgb_data->effect;
    if((effect&0xF0)&RGB_EFFECT_ANI_R)     // 清除 Low byte
        r_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_G)
        g_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_B)
        b_offset=16;
    if((effect&0x0F)&RGB_EFFECT_COPY)
        rgb_effect=RGB_EFFECT_COPY;
    else if((effect&0x0F)&RGB_EFFECT_AND)
        rgb_effect=RGB_EFFECT_AND;
    else if((effect&0x0F)&RGB_EFFECT_OR)
        rgb_effect=RGB_EFFECT_OR;
    else if((effect&0x0F)&RGB_EFFECT_NOT)
        rgb_effect=RGB_EFFECT_NOT;
    else
        rgb_effect=RGB_EFFECT_NONE;

    if(r_offset+g_offset+b_offset!=0)
        scroll_color=true;
    else
        scroll_color=false;

    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    // stephen
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];


    // Stephen Add [2003/2/11]
    switch(change_color_flag)
    {
    default:
    case 0:			// None
        break;
    case 1:			// Rebuild palette
        switch(rgb_effect)
        {
        default:
        case RGB_EFFECT_NONE:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=temp_img256_head.palette[index];
                change_color_palette[index+1]=temp_img256_head.palette[index+1];
                change_color_palette[index+2]=temp_img256_head.palette[index+2];
            }
            break;
        case RGB_EFFECT_COPY:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=rgb_data->r;
                change_color_palette[index+1]=rgb_data->g;
                change_color_palette[index+2]=rgb_data->b;
            }
            break;
        case RGB_EFFECT_AND:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=oper_and_color(temp_img256_head.palette[index],rgb_data->r);
                change_color_palette[index+1]=oper_and_color(temp_img256_head.palette[index+1],rgb_data->g);
                change_color_palette[index+2]=oper_and_color(temp_img256_head.palette[index+2],rgb_data->b);
            }
            break;
        case RGB_EFFECT_OR:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=temp_img256_head.palette[index]|rgb_data->r;
                change_color_palette[index+1]=temp_img256_head.palette[index+1]|rgb_data->g;
                change_color_palette[index+2]=temp_img256_head.palette[index+1]|rgb_data->b;
            }
            break;
        case RGB_EFFECT_NOT:
            for(index=0;index<768;index++)
            {
                change_color_palette[index]=~temp_img256_head.palette[index];
                change_color_palette[index+1]=~temp_img256_head.palette[index+1];
                change_color_palette[index+2]=~temp_img256_head.palette[index+2];
            }
            break;
        }
        break;
    }


    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                    alpha=img256_buffer[decode_index+(i<<1)+1];

                    r=change_color_palette[index];
                    g=change_color_palette[index+1];
                    b=change_color_palette[index+2];

                    /*					
                    switch(rgb_effect)
                    {
                    default:
                    case RGB_EFFECT_NONE:
                    r=temp_img256_head.palette[index];
                    g=temp_img256_head.palette[index+1];
                    b=temp_img256_head.palette[index+2];
                    break;
                    case RGB_EFFECT_COPY:
                    r=rgb_data->r;
                    g=rgb_data->g;
                    b=rgb_data->b;
                    break;
                    case RGB_EFFECT_AND:
                    r=temp_img256_head.palette[index]&rgb_data->r;
                    g=temp_img256_head.palette[index+1]&rgb_data->g;
                    b=temp_img256_head.palette[index+2]&rgb_data->b;
                    break;
                    case RGB_EFFECT_OR:
                    r=temp_img256_head.palette[index]|rgb_data->r;
                    g=temp_img256_head.palette[index+1]|rgb_data->g;
                    b=temp_img256_head.palette[index+2]|rgb_data->b;
                    break;
                    case RGB_EFFECT_NOT:
                    r=~temp_img256_head.palette[index];
                    g=~temp_img256_head.palette[index+1];
                    b=~temp_img256_head.palette[index+2];
                    break;
                    }
                    */					

                    rgb_hightlight_color(r,g,b,&bitmap->line[display_y][display_x+i]);

                    //color=rgb2hi(r,g,b);
                    //oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],(SLONG) alpha);

                }
                /*						else
                {
                i=copy_length;
                }
                */
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


    if(scroll_color)
    {
        if(rgb_data->r>=240)
            rgb_data->scroll=rgb_data->scroll|0x01;
        else if(rgb_data->r<=20)
            rgb_data->scroll=rgb_data->scroll&0xF7;

        if(rgb_data->g>=240)
            rgb_data->scroll=rgb_data->scroll|0x02;
        else if(rgb_data->g<=20)
            rgb_data->scroll=rgb_data->scroll&0xFD;

        if(rgb_data->b>=240)
            rgb_data->scroll=rgb_data->scroll|0x04;
        else if(rgb_data->b<=20)
            rgb_data->scroll=rgb_data->scroll&0xFB;



        if(rgb_data->scroll&0x01)
            rgb_data->r-=r_offset;
        else
            rgb_data->r+=r_offset;

        if(rgb_data->scroll&0x02)
            rgb_data->g-=g_offset;
        else
            rgb_data->g+=g_offset;

        if(rgb_data->scroll&0x04)
            rgb_data->b-=b_offset;
        else
            rgb_data->b+=b_offset;
    }
}



void display_rgb_img256_buffer_with_alpha(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap, SLONG alpha_value)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UHINT color;
    UCHR	alpha;
    SLONG	alpha2;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[255];

    // ------- Add 換裝參數 ----
    UCHR r,g,b;
    UCHR r_offset,g_offset,b_offset;
    SLONG rgb_effect;
    UCHR effect;
    bool scroll_color;
    //SLONG temp_r,temp_g,temp_b;

    //SLONG xstart;


    r_offset=0;
    g_offset=0;
    b_offset=0;
    effect=rgb_data->effect;
    if((effect&0xF0)&RGB_EFFECT_ANI_R)     // 清除 Low byte
        r_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_G)
        g_offset=16;
    if((effect&0xF0)&RGB_EFFECT_ANI_B)
        b_offset=16;
    if((effect&0x0F)&RGB_EFFECT_COPY)
        rgb_effect=RGB_EFFECT_COPY;
    else if((effect&0x0F)&RGB_EFFECT_AND)
        rgb_effect=RGB_EFFECT_AND;
    else if((effect&0x0F)&RGB_EFFECT_OR)
        rgb_effect=RGB_EFFECT_OR;
    else if((effect&0x0F)&RGB_EFFECT_NOT)
        rgb_effect=RGB_EFFECT_NOT;
    else
        rgb_effect=RGB_EFFECT_NONE;

    if(r_offset+g_offset+b_offset!=0)
        scroll_color=true;
    else
        scroll_color=false;

    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    // stephen
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // Stephen Add [2003/2/11]
    switch(change_color_flag)
    {
    default:
    case 0:			// None
        break;
    case 1:			// Rebuild palette
        switch(rgb_effect)
        {
        default:
        case RGB_EFFECT_NONE:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=temp_img256_head.palette[index];
                change_color_palette[index+1]=temp_img256_head.palette[index+1];
                change_color_palette[index+2]=temp_img256_head.palette[index+2];
            }
            break;
        case RGB_EFFECT_COPY:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=rgb_data->r;
                change_color_palette[index+1]=rgb_data->g;
                change_color_palette[index+2]=rgb_data->b;
            }
            break;
        case RGB_EFFECT_AND:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=oper_and_color(temp_img256_head.palette[index],rgb_data->r);
                change_color_palette[index+1]=oper_and_color(temp_img256_head.palette[index+1],rgb_data->g);
                change_color_palette[index+2]=oper_and_color(temp_img256_head.palette[index+2],rgb_data->b);
            }
            break;
        case RGB_EFFECT_OR:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=temp_img256_head.palette[index]|rgb_data->r;
                change_color_palette[index+1]=temp_img256_head.palette[index+1]|rgb_data->g;
                change_color_palette[index+2]=temp_img256_head.palette[index+1]|rgb_data->b;
            }
            break;
        case RGB_EFFECT_NOT:
            for(index=0;index<768;index+=3)
            {
                change_color_palette[index]=~temp_img256_head.palette[index];
                change_color_palette[index+1]=~temp_img256_head.palette[index+1];
                change_color_palette[index+2]=~temp_img256_head.palette[index+2];
            }
            break;
        }
        break;
    }


    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                    alpha=img256_buffer[decode_index+(i<<1)+1];

                    // Jack, Add alpha_value control here. [1/21/2003]
                    alpha2=(SLONG)alpha-alpha_value;
                    if(alpha2<0)alpha2=0;
                    if(alpha2>=255)alpha2=255;
                    alpha = (UCHR)alpha2;
                    // ----------------------------

                    r=change_color_palette[index];
                    g=change_color_palette[index+1];
                    b=change_color_palette[index+2];

                    /*
                    switch(rgb_effect)
                    {
                    default:
                    case RGB_EFFECT_NONE:
                    r=temp_img256_head.palette[index];
                    g=temp_img256_head.palette[index+1];
                    b=temp_img256_head.palette[index+2];
                    break;
                    case RGB_EFFECT_COPY:
                    r=rgb_data->r;
                    g=rgb_data->g;
                    b=rgb_data->b;
                    break;
                    case RGB_EFFECT_AND:
                    r=temp_img256_head.palette[index]&rgb_data->r;
                    g=temp_img256_head.palette[index+1]&rgb_data->g;
                    b=temp_img256_head.palette[index+2]&rgb_data->b;
                    break;
                    case RGB_EFFECT_OR:
                    r=temp_img256_head.palette[index]|rgb_data->r;
                    g=temp_img256_head.palette[index+1]|rgb_data->g;
                    b=temp_img256_head.palette[index+2]|rgb_data->b;
                    break;
                    case RGB_EFFECT_NOT:
                    r=~temp_img256_head.palette[index];
                    g=~temp_img256_head.palette[index+1];
                    b=~temp_img256_head.palette[index+2];
                    break;
                    }
                    */

                    color=rgb2hi(r,g,b);
                    oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],(SLONG) alpha);

                }
                /*						else
                {
                i=copy_length;
                }
                */
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


    if(scroll_color)
    {
        if(rgb_data->r>=240)
            rgb_data->scroll=rgb_data->scroll|0x01;
        else if(rgb_data->r<=20)
            rgb_data->scroll=rgb_data->scroll&0xF7;

        if(rgb_data->g>=240)
            rgb_data->scroll=rgb_data->scroll|0x02;
        else if(rgb_data->g<=20)
            rgb_data->scroll=rgb_data->scroll&0xFD;

        if(rgb_data->b>=240)
            rgb_data->scroll=rgb_data->scroll|0x04;
        else if(rgb_data->b<=20)
            rgb_data->scroll=rgb_data->scroll&0xFB;



        if(rgb_data->scroll&0x01)
            rgb_data->r-=r_offset;
        else
            rgb_data->r+=r_offset;

        if(rgb_data->scroll&0x02)
            rgb_data->g-=g_offset;
        else
            rgb_data->g+=g_offset;

        if(rgb_data->scroll&0x04)
            rgb_data->b-=b_offset;
        else
            rgb_data->b+=b_offset;
    }
}


// Jack, remark for cancel voice play for SeaAge. [1/21/2003]
/*
SLONG auto_play_buffer_voice(UCHR *buffer,SLONG size,SLONG loop_flag,SLONG vol)
{
SLONG play_channel;
SLONG find;
SLONG i;
ULONG now_time;
UCHR filename[255];
SLONG bs,bok,bsize;
ULONG tt;

WAVEFORMATEX wfx;

if((buffer==NULL)||(size==0))return(TTN_NOT_OK);
sprintf((char *)filename,"%p",buffer);

// find emtry channel
find=0;
for(i=0;i<VOICE_CHANNEL_MAX;i++)
{
if(voice_filename[i][0]==NULL)
{
find=1;
play_channel=i;
i=VOICE_CHANNEL_MAX;
}
}
if(find==1)
goto find_ok;

// --- step 1 clear play end voice
now_time=GetTickCount();
for(i=1;i<VOICE_CHANNEL_MAX;i++)
{
if((now_time>channel_timer[i])&&(voice_loop[i]==0))
strcpy((char *)voice_filename[i],"");
}

// --- step 2 check playing voice same filename ----
for(i=1;i<VOICE_CHANNEL_MAX;i++)
{
if(voice_filename[i][0]==NULL)continue;
if(strcmpi((char *)filename,(char *)voice_filename[i])==0)
{
set_voice_volume(i,vol);
return(TTN_OK);
}
}


find=0;
for(i=0;i<VOICE_CHANNEL_MAX;i++)
{
if(voice_filename[i][0]==NULL)
{
find=1;
play_channel=i;
i=VOICE_CHANNEL_MAX;
}
}

if(find==0)			// play channel is full
{
find=0;
for(i=0;i<VOICE_CHANNEL_MAX;i++)
{
if((now_time>=channel_timer[i])&&(voice_loop[i]==0))
{
find=1;
play_channel=i;
i=VOICE_CHANNEL_MAX;
}
}
}

if(find==0)
play_channel=0;

find_ok:
strcpy((char *)voice_filename[play_channel],(char *)filename);
voice_loop[play_channel]=loop_flag;
play_buffer_voice( play_channel,loop_flag,buffer,size);
set_voice_volume(play_channel,vol);
get_buffer_wav_format(buffer,&bs,&wfx,&bok,&bsize);	
tt=bsize * 1000 / wfx.nAvgBytesPerSec;
now_time=GetTickCount();
channel_timer[play_channel]=now_time+tt;
return(play_channel);

}

void auto_stop_voice(UCHR *filename)
{
SLONG i;


for(i=0;i<VOICE_CHANNEL_MAX;i++)
{
if(strcmpi((char *)voice_filename[i],(char *)filename)==0)
{
stop_voice(i);				
strcpy((char *)voice_filename[i],"");
return;
}
}
}


void auto_stop_all_voice(void)
{
SLONG i;

for(i=0;i<VOICE_CHANNEL_MAX;i++)
{
stop_voice(i);				
strcpy((char *)voice_filename[i],"");
}
}
*/


void display_hightlight_zoom_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG src_x,src_y;
    SLONG yl,xl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    SLONG xcount,ycount;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    SLONG yy,ww,xx;
    SLONG *xstep=NULL,*ystep=NULL;
    float xscale;
    float yscale;
    UCHR message[255];

    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    xl=temp_img256_head.xlen;
    yl=temp_img256_head.ylen;
    if((xl<=1)||(yl<=1))return;
    data_size=temp_img256_head.image_compress_size;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Open Zoom table
    yscale=(float)zoom_percent/100;
    xscale=yscale;

    //		xscale=(float)yscale*(float)0.75;

    xstep=(SLONG *)malloc(sizeof(SLONG)*xl);
    ystep=(SLONG *)malloc(sizeof(SLONG)*yl);
    for(i=0;i<xl;i++)
    {
        xstep[i]=(SLONG)((float)i*xscale);
        if(i>0)
            xstep[i-1]=xstep[i]-xstep[i-1];
    }
    xstep[xl-1]=(SLONG)((float)xl*xscale)-xstep[xl-1];

    for(i=0;i<yl;i++)
    {
        ystep[i]=(SLONG)((float)i*yscale);
        if(i>0)
            ystep[i-1]=ystep[i]-ystep[i-1];
    }
    ystep[yl-1]=(SLONG)((float)yl*yscale)-ystep[yl-1];

    src_x=x-(SLONG)((float)temp_img256_head.center_x*xscale);
    src_y=y-(SLONG)((float)temp_img256_head.center_y*yscale);
    display_x=src_x;
    display_y=src_y;


    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    ycount=0;
    xcount=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            for(i=xcount;i<xcount+skip_length;i++)
                display_x=display_x+xstep[i];
            xcount=xcount+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;
            xx=0;
            for(yy=0;yy<ystep[ycount];yy++)
            {
                i=0;			// 資料偏移
                xx=0;			// 座標偏移
                while(i<copy_length)
                {
                    for(ww=0;ww<xstep[xcount+i];ww++)
                    {
                        if(((display_x+xx)<bitmap->w)&&
                            (display_y+yy<bitmap->h)&&
                            (display_x+xx>=0)&&
                            (display_y+yy>=0))
                        {
                            index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                            //									color=rgb2hi(temp_img256_head.palette[index],
                            //										temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);

                            rgb_hightlight_color( temp_img256_head.palette[index],
                                temp_img256_head.palette[index+1],temp_img256_head.palette[index+2],
                                &bitmap->line[display_y+yy][display_x+xx]);
                        }
                        xx++;		// 座標偏移
                    }
                    i++;			// 資料偏移
                }
            }
            display_x=display_x+xx;
            xcount=xcount+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            for(yy=0;yy<ystep[ycount];yy++)
                display_y++;
            display_x=src_x;
            ycount++;
            xcount=0;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(ycount>=yl))
            main_pass=1;
    }

    free(xstep);
    free(ystep);

}


void rgb_hightlight_color(UCHR fr,UCHR fg,UCHR fb,UHINT *bk_color)
{
    UCHR br,bg,bb;
    SLONG r,g,b;

    hi2rgb(*bk_color,&br,&bg,&bb);

    r=(SLONG)fr+(SLONG)br;
    g=(SLONG)fg+(SLONG)bg;
    b=(SLONG)fb+(SLONG)bb;
    if(r>=255)r=255;
    if(g>=255)g=255;
    if(b>=255)b=255;

    /*
    __asm
    {

    xor  eax,eax
    xor  ebx,ebx
    mov  al,fr
    mov  bl,br

    xor  ecx,ecx
    xor  edx,edx
    mov  cl,fg
    mov  dl,bg

    add  eax,ebx
    add  ecx,edx

    cmp  eax,0xff
    jle  _r_ok
    mov  eax,0xff
    _r_ok:
    mov  r,eax

    cmp  ecx,0xff
    jle  _g_ok
    mov  ecx,0xff
    _g_ok:
    mov  g,ecx

    xor  eax,eax
    xor  ebx,ebx
    mov  al,fb
    mov  bl,bb

    add  eax,ebx
    cmp  eax,0xff

    jle  _b_ok
    mov  eax,0xff
    _b_ok:
    mov  b,eax
    }
    */
    *bk_color=rgb2hi((UCHR)r,(UCHR)g,(UCHR)b);

}



void oper_hightlight_color(UHINT *color,UHINT *bk_color)
{
    UCHR fr,fg,fb;
    UCHR br,bg,bb;
    UCHR r,g,b;

    hi2rgb(*color,&fr,&fg,&fb);
    hi2rgb(*bk_color,&br,&bg,&bb);

    r=(UCHR)((SLONG)fr+(SLONG)br);
    g=(UCHR)((SLONG)fg+(SLONG)bg);
    b=(UCHR)((SLONG)fb+(SLONG)bb);
    *bk_color=rgb2hi(r,g,b);

}



void display_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UHINT color;
    UCHR alpha;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[256];
    //SLONG xstart;



    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    // stephen
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                    alpha=img256_buffer[decode_index+(i<<1)+1];
                    color=rgb2hi(temp_img256_head.palette[index],
                        temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);
                    oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],(SLONG) alpha);

                }
                /*						else
                {
                i=copy_length;
                }
                */
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


}





void display_hightlight_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[255];
    //SLONG xstart;



    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;

                    rgb_hightlight_color( temp_img256_head.palette[index],
                        temp_img256_head.palette[index+1],temp_img256_head.palette[index+2],
                        &bitmap->line[display_y][display_x+i]);

                    //alpha=img256_buffer[decode_index+(i<<1)+1];
                    //color=rgb2hi(temp_img256_head.palette[index],
                    //	temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);
                    //oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],(SLONG) alpha);

                }
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


}



void display_img256_buffer_alpha(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG alpha_base)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG yl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    UHINT color;
    UCHR alpha;
    SLONG alpha1;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    UCHR message[255];
    //SLONG xstart;



    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    yl=temp_img256_head.ylen;
    data_size=temp_img256_head.image_compress_size;
    display_x=x-temp_img256_head.center_x;
    display_y=y-temp_img256_head.center_y;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            display_x=display_x+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;

            for(i=0;i<copy_length;i++)
            {
                if(((display_x+i)<bitmap->w)&&
                    (display_y<bitmap->h)&&
                    (display_x+i>=0)&&
                    (display_y>=0))
                {
                    index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                    alpha=img256_buffer[decode_index+(i<<1)+1];
                    alpha1=(SLONG)alpha-alpha_base;
                    if(alpha1<0)alpha1=0;
                    if(alpha1>=255)alpha1=255;
                    //							alpha=(UCHR)alpha1;
                    color=rgb2hi(temp_img256_head.palette[index],
                        temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);
                    oper_alpha_color( &color, &bitmap->line[display_y][display_x+i],alpha1);

                }
                /*						else
                {
                i=copy_length;
                }
                */
            }
            display_x=display_x+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            display_y++;
            display_x=x-temp_img256_head.center_x;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(display_y>=end_y))
            main_pass=1;
    }


}


void display_zoom_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG src_x,src_y;
    SLONG yl,xl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    SLONG xcount,ycount;
    UHINT color;
    UCHR alpha;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    SLONG yy,ww,xx;
    SLONG *xstep=NULL,*ystep=NULL;
    float xscale;
    float yscale;
    UCHR message[255];


    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    xl=temp_img256_head.xlen;
    yl=temp_img256_head.ylen;
    if((xl<=1)||(yl<=1))return;
    data_size=temp_img256_head.image_compress_size;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Open Zoom table
    yscale=(float)zoom_percent/100;
    xscale=yscale;

    //		xscale=(float)yscale*(float)0.75;

    xstep=(SLONG *)malloc(sizeof(SLONG)*xl);
    ystep=(SLONG *)malloc(sizeof(SLONG)*yl);
    for(i=0;i<xl;i++)
    {
        xstep[i]=(SLONG)((float)i*xscale);
        if(i>0)
            xstep[i-1]=xstep[i]-xstep[i-1];
    }
    xstep[xl-1]=(SLONG)((float)xl*xscale)-xstep[xl-1];

    for(i=0;i<yl;i++)
    {
        ystep[i]=(SLONG)((float)i*yscale);
        if(i>0)
            ystep[i-1]=ystep[i]-ystep[i-1];
    }
    ystep[yl-1]=(SLONG)((float)yl*yscale)-ystep[yl-1];

    src_x=x-(SLONG)((float)temp_img256_head.center_x*xscale);
    src_y=y-(SLONG)((float)temp_img256_head.center_y*yscale);


    display_x=src_x;
    display_y=src_y;


    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    ycount=0;
    xcount=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            for(i=xcount;i<xcount+skip_length;i++)
                display_x=display_x+xstep[i];
            xcount=xcount+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;
            xx=0;
            for(yy=0;yy<ystep[ycount];yy++)
            {
                i=0;			// 資料偏移
                xx=0;			// 座標偏移
                while(i<copy_length)
                {
                    for(ww=0;ww<xstep[xcount+i];ww++)
                    {
                        if(((display_x+xx)<bitmap->w)&&
                            (display_y+yy<bitmap->h)&&
                            (display_x+xx>=0)&&
                            (display_y+yy>=0))
                        {
                            index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                            alpha=img256_buffer[decode_index+(i<<1)+1];
                            color=rgb2hi(temp_img256_head.palette[index],
                                temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);
                            oper_alpha_color( &color, &bitmap->line[display_y+yy][display_x+xx],(SLONG) alpha);
                        }
                        xx++;		// 座標偏移
                    }
                    i++;			// 資料偏移
                }
            }
            display_x=display_x+xx;
            xcount=xcount+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            for(yy=0;yy<ystep[ycount];yy++)
                display_y++;
            display_x=src_x;
            ycount++;
            xcount=0;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(ycount>=yl))
            main_pass=1;
    }

    free(xstep);
    free(ystep);

}


void display_zoom_img256_buffer_alpha(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent,SLONG alpha_base)
{
    IMG256_HEAD temp_img256_head;
    SLONG display_x,display_y;
    UCHR *img256_buffer;
    SLONG src_x,src_y;
    SLONG yl,xl;
    SLONG data_size;
    SLONG end_y;
    SLONG skip_length,copy_length;
    SLONG decode_index;
    SLONG main_pass;
    SLONG xcount,ycount;
    UHINT color;
    UCHR alpha;
    UCHR compress_type;
    SLONG index;
    SLONG i;
    SLONG yy,ww,xx;
    SLONG *xstep=NULL,*ystep=NULL;
    float xscale;
    float yscale;
    SLONG alpha1;
    UCHR message[255];

    // ------ Get Base Data
    memcpy(&temp_img256_head,data_buffer,sizeof(struct IMG256_HEAD_STRUCT));
    xl=temp_img256_head.xlen;
    yl=temp_img256_head.ylen;
    if((xl<=1)||(yl<=1))return;
    data_size=temp_img256_head.image_compress_size;
    img256_buffer=&data_buffer[temp_img256_head.img_start_offset];

    // ------ Open Zoom table
    yscale=(float)zoom_percent/100;
    xscale=yscale;

    //		xscale=(float)yscale*(float)0.75;

    xstep=(SLONG *)malloc(sizeof(SLONG)*xl);
    ystep=(SLONG *)malloc(sizeof(SLONG)*yl);
    for(i=0;i<xl;i++)
    {
        xstep[i]=(SLONG)((float)i*xscale);
        if(i>0)
            xstep[i-1]=xstep[i]-xstep[i-1];
    }
    xstep[xl-1]=(SLONG)((float)xl*xscale)-xstep[xl-1];

    for(i=0;i<yl;i++)
    {
        ystep[i]=(SLONG)((float)i*yscale);
        if(i>0)
            ystep[i-1]=ystep[i]-ystep[i-1];
    }
    ystep[yl-1]=(SLONG)((float)yl*yscale)-ystep[yl-1];

    src_x=x-(SLONG)((float)temp_img256_head.center_x*xscale);
    src_y=y-(SLONG)((float)temp_img256_head.center_y*yscale);
    display_x=src_x;
    display_y=src_y;


    // ------ Display Loop
    end_y=display_y+yl;
    skip_length=0;
    copy_length=0;
    decode_index=0;
    ycount=0;
    xcount=0;
    main_pass=0;
    while(main_pass==0)
    {
        compress_type=img256_buffer[decode_index];
        decode_index++;
        switch(compress_type)
        {
        case IMG_SKIP:
            skip_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            for(i=xcount;i<xcount+skip_length;i++)
                display_x=display_x+xstep[i];
            xcount=xcount+skip_length;
            decode_index=decode_index+2;
            break;
        case IMG_COPY:
            copy_length=img256_buffer[decode_index]+
                (img256_buffer[decode_index+1]<<8);
            decode_index=decode_index+2;
            xx=0;
            for(yy=0;yy<ystep[ycount];yy++)
            {
                i=0;			// 資料偏移
                xx=0;			// 座標偏移
                while(i<copy_length)
                {
                    for(ww=0;ww<xstep[xcount+i];ww++)
                    {
                        if(((display_x+xx)<bitmap->w)&&
                            (display_y+yy<bitmap->h)&&
                            (display_x+xx>=0)&&
                            (display_y+yy>=0))
                        {
                            index=(SLONG)img256_buffer[decode_index+(i<<1)]*3;
                            alpha=img256_buffer[decode_index+(i<<1)+1];
                            alpha1=(SLONG)alpha-alpha_base;
                            if(alpha1<0)alpha1=0;
                            if(alpha1>=255)alpha1=255;
                            // alpha=(UCHR)alpha1;
                            color=rgb2hi(temp_img256_head.palette[index],
                                temp_img256_head.palette[index+1],temp_img256_head.palette[index+2]);
                            oper_alpha_color( &color, &bitmap->line[display_y+yy][display_x+xx], alpha1);
                        }
                        xx++;		// 座標偏移
                    }
                    i++;			// 資料偏移
                }
            }
            display_x=display_x+xx;
            xcount=xcount+copy_length;
            decode_index=decode_index+(copy_length<<1);
            break;
        case IMG_LINE:
            for(yy=0;yy<ystep[ycount];yy++)
                display_y++;
            display_x=src_x;
            ycount++;
            xcount=0;
            break;
        default:
            sprintf((char *)message,"%x Decompress Code Error",compress_type);
            display_message(message,true);
            return;
        }
        if((decode_index>=data_size)||(ycount>=yl))
            main_pass=1;
    }

    free(xstep);
    free(ystep);

}

void init_media_data(void)
{
    SLONG i;
    for(i=0;i<256;i++)
    {
        r_full_palette[i*3]=0xFF;
        r_full_palette[i*3+1]=0x00;
        r_full_palette[i*3+2]=0x00;

        g_full_palette[i*3]=0x00;
        g_full_palette[i*3+1]=0xFF;
        g_full_palette[i*3+2]=0x00;

        b_full_palette[i*3]=0x00;
        b_full_palette[i*3+1]=0x00;
        b_full_palette[i*3+2]=0xFF;

        yellow_full_palette[i*3]=0xFF;
        yellow_full_palette[i*3+1]=0xFF;
        yellow_full_palette[i*3+2]=0x00;

        black_full_palette[i*3]=0x00;
        black_full_palette[i*3+1]=0x00;
        black_full_palette[i*3+2]=0x00;

        white_full_palette[i*3]=0xFF;
        white_full_palette[i*3+1]=0xFF;
        white_full_palette[i*3+2]=0xFF;
    }

    // ------(4) Clear Voice Channel Data
    // Jack, remark for cancel voice play for SeaAge [1/21/2003]
    /*
    for(i=0;i<MAX_SOUND_CHANNELS;i++)
    {
    strcpy((char *)voice_filename[i],"");
    voice_loop[i]=0;
    channel_timer[i]=0;
    }
    */

}


SLONG get_media_total_frame(SLONG handle)
{
    SLONG mda_group_index;
    SLONG ret_val;

    if(handle<0)return(TTN_NOT_OK);
    mda_group_index=get_mda_index(handle);
    ret_val=mda_group[mda_group_index].total_ani_frame;
    return(ret_val);
}


void set_media_rgb_data(SLONG handle,SLONG select_part,UCHR r,UCHR g,UCHR b)
{
    SLONG mda_group_index;

    mda_group_index=get_mda_index(handle);
    if(mda_group_index==TTN_NOT_OK)return;
    mda_group[mda_group_index].sea_rgb_data[select_part].r=r;
    mda_group[mda_group_index].sea_rgb_data[select_part].g=g;
    mda_group[mda_group_index].sea_rgb_data[select_part].b=b;

}


void set_media_rgb_effect(SLONG handle,SLONG select_part,UCHR effect)
{
    SLONG mda_group_index;

    mda_group_index=get_mda_index(handle);
    if(mda_group_index==TTN_NOT_OK)return;
    mda_group[mda_group_index].sea_rgb_data[select_part].effect=effect;

}



void	get_media_rgb_data_with_scroll(SLONG handle,SLONG select_part,UCHR *r,UCHR *g,UCHR *b, UCHR *scroll)
{
    SLONG mda_group_index;

    mda_group_index=get_mda_index(handle);
    if(mda_group_index==TTN_NOT_OK)
    {
        *r=0x00;
        *g=0x00;
        *b=0x00;
        return;
    }
    *r=mda_group[mda_group_index].sea_rgb_data[select_part].r;
    *g=mda_group[mda_group_index].sea_rgb_data[select_part].g;
    *b=mda_group[mda_group_index].sea_rgb_data[select_part].b;
    *scroll=mda_group[mda_group_index].sea_rgb_data[select_part].scroll;
}

void get_media_rgb_data(SLONG handle,SLONG select_part,UCHR *r,UCHR *g,UCHR *b)
{
    SLONG mda_group_index;

    mda_group_index=get_mda_index(handle);
    if(mda_group_index==TTN_NOT_OK)
    {
        *r=0x00;
        *g=0x00;
        *b=0x00;
        return;
    }
    *r=mda_group[mda_group_index].sea_rgb_data[select_part].r;
    *g=mda_group[mda_group_index].sea_rgb_data[select_part].g;
    *b=mda_group[mda_group_index].sea_rgb_data[select_part].b;

}


void	set_media_offset_position(SLONG handle, SLONG offset_x, SLONG offset_y)
{
    SLONG mda_group_index;

    mda_group_index=get_mda_index(handle);
    if(mda_group_index==TTN_NOT_OK)
        return;

    mda_group[mda_group_index].offset_x = offset_x;
    mda_group[mda_group_index].offset_y = offset_y;
}


void update_media_rgb_data(SLONG handle,SLONG select_part,SLONG r_off,SLONG g_off,SLONG b_off)
{
    UCHR r,g,b;


    get_media_rgb_data(handle,select_part,&r,&g,&b);
    r=(UCHR)((SLONG)r+r_off);
    g=(UCHR)((SLONG)g+g_off);
    b=(UCHR)((SLONG)b+b_off);
    set_media_rgb_data(handle,select_part,r,g,b);
}




// Jack, Added for mda group reference control. [1/24/2003]
SLONG	found_exist_mda_group(USTR *filename)
{
    SLONG	i, find_index;

    find_index = -1;
    for(i=0; i<total_mda_group; i++)
    {
        if(0 == strcmpi((const char *)filename, (const char *)mda_group[i].filename))
        {
            find_index = i;
            break;
        }
    }
    return	find_index;
}


UCHR	oper_and_color(UCHR for_color,UCHR bak_color)
{
    SLONG	temp_color;

    temp_color=(SLONG)for_color+((((SLONG)bak_color)-128)*2);
    if(temp_color>255)temp_color=255;
    if(temp_color<0)temp_color=0;
    return(UCHR)temp_color;
}


UCHR	oper_and_value(UCHR final_color, UCHR init_color)
{
    return	(UCHR)(128 + (SLONG)((SLONG)final_color - (SLONG)init_color) / 2);
}