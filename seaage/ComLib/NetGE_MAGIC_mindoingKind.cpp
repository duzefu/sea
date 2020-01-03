/*
 *	ljun 2003-04-14
 *  �����̭��w�q���O�@��NPC�̤p�欰�����
 */
#include "NetGE_Mainfunc.h"
#include "NetGE_MAGIC_mindoingkind.h" 

//----
//  STATE   �B�z���
//----
//��L���A���B�z��� 
void    do_magic_part_state_dump(SLONG lIndex)
{
    return;
}
//���]�k����B���v�����A......�N�O�]�k�ե󪺶}�l�ǳƶ��q
void    do_magic_part_state_sleep(SLONG lIndex)
{
	SLONG	sleep_tick, magic_stop;
	SLONG	next_x, next_y, next_z;
	SLONG	result;
    //
    //  ��v�p��..���
    //  ��v�p��..���0��...�}�l�ǳƲ���
    //
	sleep_tick = GetZoneMagicPartSleepTick(lIndex);
	--sleep_tick;
	if (sleep_tick <= 0)
	{
		GetZoneMagicPartCurrPosition(lIndex, &next_x, &next_y, &next_z);
		magic_stop = GetZoneMagicPartStop(lIndex);
		
		LOCK_MAPMASK(0);
		result = IsPixelMaskMatch(next_x, next_y, magic_stop);
		UNLOCK_MAPMASK(0);
		
		if(TRUE == result)
		{
			//�p�G����..�q�{�Q��b����̭�..�ݭn�⥦�M�B��..���ݭn��ܥX��
			// Dead for stop
			SetZoneMagicPartFlag(lIndex, 0);
		}
		else
		{
		    //�ǳƮɶ�����...�}�l�����󲾰�
			PrepareZoneMagicPartForShift(lIndex);
		}
	}
	else
	{
	    //
		SetZoneMagicPartSleepTick(lIndex, sleep_tick);
	}
}
//�]�k����B�󲾰ʤ�........�N�O�]�k�ե󪺿E�����A
void    do_magic_part_state_shift(SLONG lIndex)
{
    SLONG   path;
    //
    path = GetZoneMagicPartPath(lIndex);
    //
    switch (path)
    {
    case MAGIC_PATH_LINE:   //���u����...�Ӳ��ʤ覡�O�q..���a���ؼ��I..���u����
        do_magic_part_path_line(lIndex);
        break;
    case MAGIC_PATH_UP:     //z �b����
        do_magic_part_path_up(lIndex);
        break;        
    default:
        do_magic_part_path_dum(lIndex);
        break;            
    }
    //
    return;
}
//�]�k����B�󬵶}��......�Ҧ����k�N�ե󪺮��`���b�o�̱���
//...............����k�N�ե󪺮����ʵe..�@��...�M��R���k�N�ե�
void    do_magic_part_state_explode(SLONG lIndex)
{
    SLONG   frame_num;
    SLONG   id;
    SLONG   total_frame;
    //
    id = GetZoneMagicPartImageID(lIndex);
    frame_num = GetZoneMagicPartImageFrame(lIndex);    
    //
    if (id == INVALID_OBJECT_ID)
    {
        SetZoneMagicPartFlag(lIndex , 0);
    }
    else
    {
        total_frame = GetObjectImageTotalFrames(id);
        if (frame_num >= total_frame-1)//�̫�@�V..�ݭn -1 ...
            SetZoneMagicPartFlag(lIndex , 0);
    }    

    return;
}
//----
//  PATH ������
//----
void    do_magic_part_path_dum(SLONG lIndex)
{
    return;
}
//�]�k���󪽽u����
void    do_magic_part_path_line(SLONG lIndex)
{
    SLONG   step;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;    
	SLONG   dx, dy, dz;
    double  speed,dr;	
    //���u����..�O...�q���I.��ؼ��I..
	step = GetZoneMagicPartStep(lIndex);
	speed = (SLONG)GetZoneMagicPartSpeed(lIndex);
	GetZoneMagicPartDestPosition(lIndex, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(lIndex, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr );
	next_z = orig_z + (SLONG) ( step * speed * dz / dr );
	//�]�m�s���y��
    SetZoneMagicPartCurrPosition(lIndex, next_x, next_y, next_z);
    //�W�[�g�L���B��
    SetZoneMagicPartStep(lIndex, step+1);
}
void    do_magic_part_path_up(SLONG lIndex)
{
    SLONG   step;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	cur_x, cur_y, cur_z;
	SLONG   dx, dy, dz;
    double  speed;
    //���u����..�O...�q���I.��ؼ��I..
	step = GetZoneMagicPartStep(lIndex);
	speed = (SLONG)GetZoneMagicPartSpeed(lIndex);
	GetZoneMagicPartDestPosition(lIndex, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartCurrPosition(lIndex, &cur_x, &cur_y, &cur_z);
	dx = cur_x;
	dy = cur_y;
	//
	if (abs(cur_z -dest_z) <= speed )
	    dz = dest_z;
	else
	    dz = (SLONG)(cur_z + speed);
	//
	//�]�m�s���y��
    SetZoneMagicPartCurrPosition(lIndex, dx, dy, dz);
    //�W�[�g�L���B��
    SetZoneMagicPartStep(lIndex, step+1);

}
//----
//  FRAME �V�Ʊ�����
//----
void    do_magic_part_frame(SLONG lIndex)
{
    SLONG   frame_num;
    SLONG   id, appear_id, proc_id;
    SLONG   total_frame;
    //
    id = GetZoneMagicPartImageID(lIndex);
    if (id != INVALID_OBJECT_ID )
    {
        //
        frame_num = GetZoneMagicPartImageFrame(lIndex);    
        //
        total_frame = GetObjectImageTotalFrames(id);
        //
        frame_num++;
        if (frame_num >= total_frame)
        {
            //�p�G����B�b..�ʵe�}�l���񪺪��A...
            appear_id = GetZoneMagicPartAppearImgId(lIndex);
            proc_id = GetZoneMagicPartProcImagId(lIndex);
            //
            if (appear_id == id)
            {
                SetZoneMagicPartImageID(lIndex, proc_id);
            }
            //
            frame_num = 0;
        }
        //
        SetZoneMagicPartImageFrame(lIndex,frame_num);    
    }
}
//----
//  SURVIAL ������
//              ������]�k���󪺥ͦs�覡
//----
void    do_magic_part_survial(SLONG lIndex)
{
    SLONG   id;
    SLONG   survial;
    SLONG   live_tick;
    SLONG   cur_frame, total_frame;
    SLONG   dx, dy, dz, cx, cy, cz;
    //
    survial = GetZoneMagicPartSurvial(lIndex);
    //
    if (survial & MAGIC_SURVIAL_TIME)               //���]�k����b�@�q�ɶ���|����
    {
        live_tick = GetZoneMagicPartLifeTick(lIndex);
        live_tick--;
        if (live_tick <= 0)
        {
            PrepareZoneMagicPartForExplode(lIndex);
        }            
        SetZoneMagicPartLifeTick(lIndex, live_tick);
    }
    //
    if (survial & MAGIC_SURVIAL_FRAME_ONE_TIME)     //���]�k����b�ʵe�����̫�@�V�|����
    {
        cur_frame = GetZoneMagicPartImageFrame(lIndex);
        id = GetZoneMagicPartImageID(lIndex);
        total_frame = GetObjectImageTotalFrames(id);
        //
        if (cur_frame >= total_frame-1) //�̫�@�V
        {
            PrepareZoneMagicPartForExplode(lIndex);
        }            
    }
    //    
    if (survial &  MAGIC_SURVIAL_PATH)               //���]�k����b�����ۤv���B�ʶZ�������
    {
        GetZoneMagicPartCurrPosition(lIndex, &cx, &cy, &cz);
        GetZoneMagicPartDestPosition(lIndex, &dx, &dy, &dz);
        //
        if ((dx == cx) && (dy == cy))//��F�ؼ��I
        {
            PrepareZoneMagicPartForExplode(lIndex);
        }            
    }
    //    
    if (survial & MAGIC_SURVIAL_ALPHA_DISAPPEAR)    //���]�k����alpha�X�{..�����
    {
        //
    }
    //
    if (survial & MAGIC_SURVIAL_ALPHA_APPEAR)       //���]�k���� alpha����..�����    
    {
    }
    //
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------
