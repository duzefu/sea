/*
 *	ljun 2003-04-14
 *  本文件裡面定義的是一些NPC最小行為的函數
 */
#include "NetGE_Mainfunc.h"
#include "NetGE_MAGIC_mindoingkind.h" 

//----
//  STATE   處理函數
//----
//其他狀態的處理函數 
void    do_magic_part_state_dump(SLONG lIndex)
{
    return;
}
//當魔法物件處於休眠的狀態......就是魔法組件的開始準備階段
void    do_magic_part_state_sleep(SLONG lIndex)
{
	SLONG	sleep_tick, magic_stop;
	SLONG	next_x, next_y, next_z;
	SLONG	result;
    //
    //  休眠計數..減少
    //  休眠計數..減到0後...開始準備移動
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
			//如果物件..默認被放在阻單裡面..需要把它清處掉..不需要顯示出來
			// Dead for stop
			SetZoneMagicPartFlag(lIndex, 0);
		}
		else
		{
		    //準備時間結束...開始讓物件移動
			PrepareZoneMagicPartForShift(lIndex);
		}
	}
	else
	{
	    //
		SetZoneMagicPartSleepTick(lIndex, sleep_tick);
	}
}
//魔法物件處於移動中........就是魔法組件的激活狀態
void    do_magic_part_state_shift(SLONG lIndex)
{
    SLONG   path;
    //
    path = GetZoneMagicPartPath(lIndex);
    //
    switch (path)
    {
    case MAGIC_PATH_LINE:   //直線移動...該移動方式是從..本地方到目標點..直線移動
        do_magic_part_path_line(lIndex);
        break;
    case MAGIC_PATH_UP:     //z 軸移動
        do_magic_part_path_up(lIndex);
        break;        
    default:
        do_magic_part_path_dum(lIndex);
        break;            
    }
    //
    return;
}
//魔法物件處於炸開中......所有的法術組件的消亡都在這裡控制
//...............播放法術組件的消失動畫..一次...然後刪除法術組件
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
        if (frame_num >= total_frame-1)//最後一幀..需要 -1 ...
            SetZoneMagicPartFlag(lIndex , 0);
    }    

    return;
}
//----
//  PATH 控制函數
//----
void    do_magic_part_path_dum(SLONG lIndex)
{
    return;
}
//魔法物件直線移動
void    do_magic_part_path_line(SLONG lIndex)
{
    SLONG   step;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;    
	SLONG   dx, dy, dz;
    double  speed,dr;	
    //直線移動..是...從原點.到目標點..
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
	//設置新的座標
    SetZoneMagicPartCurrPosition(lIndex, next_x, next_y, next_z);
    //增加經過的步數
    SetZoneMagicPartStep(lIndex, step+1);
}
void    do_magic_part_path_up(SLONG lIndex)
{
    SLONG   step;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	cur_x, cur_y, cur_z;
	SLONG   dx, dy, dz;
    double  speed;
    //直線移動..是...從原點.到目標點..
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
	//設置新的座標
    SetZoneMagicPartCurrPosition(lIndex, dx, dy, dz);
    //增加經過的步數
    SetZoneMagicPartStep(lIndex, step+1);

}
//----
//  FRAME 幀數控制函數
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
            //如果物件處在..動畫開始播放的狀態...
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
//  SURVIAL 控制函數
//              控制該魔法物件的生存方式
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
    if (survial & MAGIC_SURVIAL_TIME)               //該魔法物件在一段時間後會消失
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
    if (survial & MAGIC_SURVIAL_FRAME_ONE_TIME)     //該魔法物件在動畫播放到最後一幀會消失
    {
        cur_frame = GetZoneMagicPartImageFrame(lIndex);
        id = GetZoneMagicPartImageID(lIndex);
        total_frame = GetObjectImageTotalFrames(id);
        //
        if (cur_frame >= total_frame-1) //最後一幀
        {
            PrepareZoneMagicPartForExplode(lIndex);
        }            
    }
    //    
    if (survial &  MAGIC_SURVIAL_PATH)               //該魔法物件在完成自己的運動距離後消失
    {
        GetZoneMagicPartCurrPosition(lIndex, &cx, &cy, &cz);
        GetZoneMagicPartDestPosition(lIndex, &dx, &dy, &dz);
        //
        if ((dx == cx) && (dy == cy))//到達目標點
        {
            PrepareZoneMagicPartForExplode(lIndex);
        }            
    }
    //    
    if (survial & MAGIC_SURVIAL_ALPHA_DISAPPEAR)    //該魔法物件alpha出現..後消失
    {
        //
    }
    //
    if (survial & MAGIC_SURVIAL_ALPHA_APPEAR)       //該魔法物件 alpha消失..後消失    
    {
    }
    //
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------
