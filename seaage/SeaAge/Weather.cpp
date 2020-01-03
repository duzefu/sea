/*
**	Weather.cpp
**
**	Stephen, 2002/10/08.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "map.h"
#include "npc.h"
#include "house.h"
#include "houseset.h"
#include "tilefield.h"
#include "weather.h"
#include "clientmain.h"
#include "posdata.h"


CAKE_FRAME_ANI  *cloud_cfa;



// ----------- parameter define area

WEATHER_PARAMETER weather_parameter;
WEATHER_RAIN_DATA weather_rain_data[MAX_RAIN_POINT];
WEATHER_SNOW_DATA weather_snow_data[MAX_RAIN_POINT];
WEATHER_CLOUD_DATA weather_cloud_data[MAX_CLOUD];


/**************************************************************************************************}
{	啟動天氣系統																				   }
{	Input  : None																				   }
{	Output : None																				   }
{**************************************************************************************************/
int  init_weather(void)
{
    SLONG result;
    control_wind(WIND_DOWN,WIND_NONE);
    // -------- Clear all weather type
    control_weather( WEATHER_RAIN | WEATHER_SNOW | WEATHER_CLOUD | WEATHER_THUNDER,
        WEATHER_CLEAR,
        0);
    control_weather( WEATHER_NORMAL,0,0);			// 晴天
    
    set_data_file(packed_menu_file);
    result = load_cake_frame_ani_from_file((USTR*)"menu\\cloud.cak", &cloud_cfa);
    if(result!=TTN_OK)
        return(1);
    
    control_wind(WIND_RIGHT,WIND_LARGE);
    
    return(0);
}


void control_wind(SLONG dir,SLONG range)
{
    SLONG x_off,y_off;
    SLONG rr;
    
    weather_parameter.x_offset=0;
    weather_parameter.y_offset=0;
    switch(dir)
    {
    case WIND_RIGHT:
        x_off=1;
        y_off=0;
        break;
    case WIND_RIGHT_DOWN:
        x_off=1;
        y_off=1;
        break;
    case WIND_DOWN:
        x_off=0;
        y_off=1;
        break;
    case WIND_LEFT_DOWN:
        x_off=-1;
        y_off=1;
        break;
    case WIND_LEFT:
        x_off=-1;
        y_off=0;
        break;
    case WIND_LEFT_UP:
        x_off=-1;
        y_off=-1;
        break;
    case WIND_UP:
        x_off=0;
        y_off=-1;
        break;
    case WIND_UP_RIGHT:
        x_off=1;
        y_off=-1;
        break;
    }
    
    rr=0;
    switch(range)
    {
    case WIND_NONE:
        break;
    case WIND_SMALL:
        rr=1;
        break;
    case WIND_MIDDLE:
        rr=2;
        break;
    case WIND_LARGE:
        rr=4;
        break;
    }
    
    
    weather_parameter.wind_dir = dir;
	weather_parameter.wind_range = range;
    
    weather_parameter.x_offset=x_off*rr;
    weather_parameter.y_offset=y_off*rr;
}


// --------- for dummy runtinue
void free_weather(void)
{
    destroy_cake_frame_ani(&cloud_cfa);
}

void active_weather(int flag)
{
}

/**************************************************************************************************}
{  設定天氣系統參數																				   }
{	Input  : weather_type	天氣狀況															   }
{	         weather_command 目前天氣命令														   }
{			 weather_range 天氣大小																   }
{	Output : None																				   }
{**************************************************************************************************/
void control_weather(SLONG weather_type,SLONG weather_command,SLONG weather_range)
{
    SLONG i;
    
    // --- Step 1 Process rain 
    if(weather_type==WEATHER_NORMAL)
    {
        weather_parameter.status=WEATHER_NORMAL;
        return;
    }
    
    
    if(weather_type&WEATHER_RAIN)
    {
        switch(weather_command)
        {
        case WEATHER_CLEAR:
            // ----- clear rain status 
            for(i=0;i<MAX_RAIN_POINT;i++)
                weather_rain_data[i].active=0;
            weather_parameter.rain_process_count=0;
            break;
        case WEATHER_STARTUP:
            break;
        case WEATHER_STOP:
            break;
        }
        weather_parameter.rain_command=weather_command;
        weather_parameter.rain_range=weather_range;
    }
    
    // --- step 2 process snow
    if(weather_type&WEATHER_SNOW)
    {
        switch(weather_command)
        {
        case WEATHER_CLEAR:
            // ----- clear rain status 
            for(i=0;i<MAX_RAIN_POINT;i++)
                weather_snow_data[i].active=0;
            weather_parameter.snow_process_count=0;
            break;
        case WEATHER_STARTUP:
            break;
        case WEATHER_STOP:
            break;
        }
        weather_parameter.snow_command=weather_command;
        weather_parameter.snow_range=weather_range;
    }
    
    
    // --- step 3 process thunder
    if(weather_type&WEATHER_THUNDER)
    {
        switch(weather_command)
        {
        case WEATHER_CLEAR:
            weather_parameter.thunder_process_count=0;
            break;
        case WEATHER_STARTUP:
            weather_parameter.thunder_process_count=20*30+rand()%50;
            break;
        case WEATHER_STOP:
            weather_parameter.thunder_process_count=0;
            break;
        }
        weather_parameter.thunder_command=weather_command;
        weather_parameter.thunder_range=weather_range;
    }
    
    // --- step 3 process cloud
    if(weather_type&WEATHER_CLOUD)
    {
        switch(weather_command)
        {
        case WEATHER_CLEAR:
            for(i=0;i<MAX_CLOUD;i++)
                weather_cloud_data[i].active=0;
            weather_parameter.cloud_process_count=0;
            break;
        case WEATHER_STARTUP:
            break;
        case WEATHER_STOP:
            break;
        }
        weather_parameter.cloud_command=weather_command;
        weather_parameter.cloud_range=weather_range;
    }
    
    
    // --- step 4 process earthquake
    if(weather_type&WEATHER_EARTHQUAKE)
    {
        switch(weather_command)
        {
        case WEATHER_CLEAR:
            weather_parameter.earthquake_process_count=40;
            break;
        case WEATHER_STARTUP:
            break;
        case WEATHER_STOP:
            break;
        }
        weather_parameter.earthquake_command=weather_command;
        weather_parameter.earthquake_range=weather_range;
    }
    
    // ------- Update to struct 
    weather_parameter.status=weather_parameter.status|weather_type;
}



void refresh_weather(void)
{
    SLONG rain_count;
    SLONG snow_count;
    SLONG i;
    SLONG finish;
    static ULONG loop_count=0;
    
    // ----------------- Process rain ---------------------
    if(weather_parameter.status&WEATHER_RAIN)
    {
        switch(weather_parameter.rain_command)
        {
        case WEATHER_CLEAR:
            break;
        case WEATHER_STARTUP:
            {
                rain_count=5;
                switch(weather_parameter.rain_range)
                {
                case WEATHER_SMALL:
                    rain_count=10;
                    weather_parameter.wind_range=5;		
                    break;
                case WEATHER_MIDDLE:
                    rain_count=20;
                    weather_parameter.wind_range=10;
                    break;
                case WEATHER_LARGE:
                    rain_count=100;
                    weather_parameter.wind_range=30;
                    break;
                }
                for(i=0;i<rain_count;i++)
                {
                    weather_rain_data[weather_parameter.rain_process_count].active=1;
                    weather_rain_data[weather_parameter.rain_process_count].x=(map_data.map_sx-400)+rand()%1600;
                    weather_rain_data[weather_parameter.rain_process_count].y=(map_data.map_sy-300)+rand()%1200;
                    weather_rain_data[weather_parameter.rain_process_count].height=200+rand()%50;
                    
                    weather_parameter.rain_process_count++;
                    if(weather_parameter.rain_process_count>=MAX_RAIN_POINT)
                        weather_parameter.rain_process_count=0;
                }
            }
            break;
        case WEATHER_STOP:
            finish=1;
            for(i=0;i<MAX_RAIN_POINT;i++)
            {
                if(weather_rain_data[i].active>0)
                {
                    finish=0;
                    break;
                }
            }
            if(finish==1)
            {
                weather_parameter.rain_command=WEATHER_CLEAR;
                weather_parameter.status=weather_parameter.status&WEATHER_RAIN_STOP;
            }
            break;
        }
    }
    
    
    // --------------- Process snow ---------------------
    if(weather_parameter.status&WEATHER_SNOW)
    {
        switch(weather_parameter.snow_command)
        {
        case WEATHER_CLEAR:
            break;
        case WEATHER_STARTUP:
            {
                snow_count=5;
                switch(weather_parameter.snow_range)
                {
                case WEATHER_SMALL:
                    snow_count=5;
                    weather_parameter.snow_range=1;		
                    break;
                case WEATHER_MIDDLE:
                    snow_count=10;
                    weather_parameter.snow_range=2;
                    break;
                case WEATHER_LARGE:
                    snow_count=20;
                    weather_parameter.snow_range=4;
                    break;
                }
                for(i=0;i<snow_count;i++)
                {
                    weather_snow_data[weather_parameter.snow_process_count].active=1;
                    weather_snow_data[weather_parameter.snow_process_count].x=(map_data.map_sx-400)+rand()%1600;
                    weather_snow_data[weather_parameter.snow_process_count].y=(map_data.map_sy-300)+rand()%1200;
                    weather_snow_data[weather_parameter.snow_process_count].height=200+rand()%50;
                    weather_snow_data[weather_parameter.snow_process_count].size=rand()%3;
                    
                    weather_parameter.snow_process_count++;
                    if(weather_parameter.snow_process_count>=MAX_RAIN_POINT)
                        weather_parameter.snow_process_count=0;
                }
            }
            break;
        case WEATHER_STOP:
            finish=1;
            for(i=0;i<MAX_RAIN_POINT;i++)
            {
                if(weather_snow_data[i].active>0)
                {
                    finish=0;
                    break;
                }
            }
            if(finish==1)
            {
                weather_parameter.snow_command=WEATHER_CLEAR;
                weather_parameter.status=weather_parameter.status&WEATHER_SNOW_STOP;
            }
            break;
        }
    }
    
    // --------------- Process thunder ---------------------
    if(weather_parameter.status&WEATHER_THUNDER)
    {
        switch(weather_parameter.thunder_command)
        {
        case WEATHER_CLEAR:
            break;
        case WEATHER_STARTUP:
            weather_parameter.thunder_process_count--;
            if(weather_parameter.thunder_process_count<0)
                weather_parameter.thunder_process_count=20*30+rand()%50;
            break;
        case WEATHER_STOP:
            weather_parameter.thunder_command=WEATHER_CLEAR;
            weather_parameter.status=weather_parameter.status&WEATHER_THUNDER_STOP;
            break;
        }
    }
    
    
    
    // --------------- Process cloud ---------------------
    if(weather_parameter.status&WEATHER_CLOUD)
    {
        switch(weather_parameter.cloud_command)
        {
        case WEATHER_CLEAR:
            break;
        case WEATHER_STARTUP:
            loop_count++;
            if(loop_count%20!=0)break;
            if(weather_cloud_data[weather_parameter.cloud_process_count].active==0)
            {
                weather_cloud_data[weather_parameter.cloud_process_count].active=1;
                weather_cloud_data[weather_parameter.cloud_process_count].x=(map_data.map_sx-400)+rand()%1600;
                weather_cloud_data[weather_parameter.cloud_process_count].y=(map_data.map_sy-300)+rand()%1200;
                weather_cloud_data[weather_parameter.cloud_process_count].timer=0;
                weather_cloud_data[weather_parameter.cloud_process_count].type=0;
                switch(weather_parameter.cloud_range)
                {
                case WEATHER_LARGE:
                    weather_cloud_data[weather_parameter.cloud_process_count].type=0+(rand()%2*3);
                    break;
                case WEATHER_MIDDLE:
                    weather_cloud_data[weather_parameter.cloud_process_count].type=1+(rand()%2*3);
                    break;
                case WEATHER_SMALL:
                    weather_cloud_data[weather_parameter.cloud_process_count].type=2+(rand()%2*3);
                    break;
                }
                
                weather_parameter.cloud_process_count++;
                if(weather_parameter.cloud_process_count>=MAX_CLOUD)
                    weather_parameter.cloud_process_count=0;
            }
            
            break;
        case WEATHER_STOP:
            finish=1;
            for(i=0;i<MAX_CLOUD;i++)
            {
                if(weather_cloud_data[i].active>0)
                {
                    finish=0;
                    break;
                }
            }
            if(finish==1)
            {
                weather_parameter.cloud_command=WEATHER_CLEAR;
                weather_parameter.status=weather_parameter.status&WEATHER_CLOUD_STOP;
            }
            break;
        }
    }
    
    
    // --------------- Process earthquake ---------------------
    if(weather_parameter.status&WEATHER_EARTHQUAKE)
    {
        switch(weather_parameter.earthquake_command)
        {
        case WEATHER_CLEAR:
            break;
        case WEATHER_STARTUP:
            weather_parameter.earthquake_process_count--;
            if(weather_parameter.earthquake_process_count<0)
            {
                weather_parameter.earthquake_process_count=4*30+rand()%20;
                if(weather_parameter.earthquake_range==WEATHER_LARGE)
                    weather_parameter.earthquake_process_count=24;
            }
            break;
        case WEATHER_STOP:
            weather_parameter.earthquake_command=WEATHER_CLEAR;
            weather_parameter.status=weather_parameter.status&WEATHER_EARTHQUAKE_STOP;
            break;
        }
    }
}


/**************************************************************************************************}
{  執行天氣系統																					   }
{	Input  : bitmap 繪圖緩衝區																	   }
{	Output : 更改繪圖緩衝區的圖形																   }
{**************************************************************************************************/
void exec_weather(BMP *bitmap)
{
    SLONG i;
    SLONG real_x,real_y;
    SLONG target_x,target_y;
    SLONG ff;
    CAKE_FRAME_ANI  *cloud_frame;
    
    
    // --------------- process rain
    if(weather_parameter.status&WEATHER_RAIN)
    {
        for(i=0;i<MAX_RAIN_POINT;i++)
        {
            switch(weather_rain_data[i].active)
            {
            case 0:
                continue;
                break;
            case 1:
                weather_rain_data[i].x+=weather_parameter.x_offset;
                weather_rain_data[i].y+=weather_parameter.y_offset;
                real_x=weather_rain_data[i].x-map_data.map_sx;
                real_y=weather_rain_data[i].y-map_data.map_sy-weather_rain_data[i].height;
                target_x=real_x+weather_parameter.x_offset;				// wind_dir
                target_y=real_y+weather_parameter.wind_range+weather_parameter.y_offset;			// speed
                
                if((real_x>=1)&&(real_y>=1)&&(real_x<799)&&(real_y<599)&&
                    (target_x>=1)&&(target_y>=1)&&(target_x<799)&&(target_y<599))
                {
                    put_line(real_x,real_y,target_x,target_y,SYSTEM_WHITE,bitmap);
                }
                weather_rain_data[i].height-=weather_parameter.wind_range*2;
                if(weather_rain_data[i].height<=0)
                {
                    weather_rain_data[i].active=2;
                }
                break;
            case 2:
                real_x=weather_rain_data[i].x-map_data.map_sx;
                real_y=weather_rain_data[i].y-map_data.map_sy;
                if((real_x>=1)&&(real_y>=1)&&(real_x<799)&&(real_y<599))
                    put_ellipse(real_x,real_y,2,1,SYSTEM_WHITE,bitmap);
                weather_rain_data[i].active=3;
                break;
            case 3:
                real_x=weather_rain_data[i].x-map_data.map_sx;
                real_y=weather_rain_data[i].y-map_data.map_sy;
                if((real_x>=1)&&(real_y>=1)&&(real_x<799)&&(real_y<599))
                    put_ellipse(real_x,real_y,4,2,SYSTEM_WHITE,bitmap);
                weather_rain_data[i].active=4;
                break;
            case 4:
                real_x=weather_rain_data[i].x-map_data.map_sx;
                real_y=weather_rain_data[i].y-map_data.map_sy;
                if((real_x>=1)&&(real_y>=1)&&(real_x<799)&&(real_y<599))
                    put_ellipse(real_x,real_y,6,3,SYSTEM_WHITE,bitmap);
                weather_rain_data[i].active=0;
                break;
            }
        }
    }
    
    
    // --------------- process snow
    if(weather_parameter.status&WEATHER_SNOW)
    {
        for(i=0;i<MAX_RAIN_POINT;i++)
        {
            switch(weather_snow_data[i].active)
            {
            case 0:
                continue;
                break;
            case 1:
                {
                    weather_snow_data[i].x+=weather_parameter.x_offset;
                    weather_snow_data[i].y+=weather_parameter.y_offset;
                    
                    real_x=weather_snow_data[i].x-map_data.map_sx;
                    real_y=weather_snow_data[i].y-map_data.map_sy-weather_snow_data[i].height;
                    ff=real_y%5;
                    real_x=real_x+(ff-3);
                    
                    switch(weather_snow_data[i].size)
                    {
                    case 0:
                        if((real_x>=5)&&(real_y>=5)&&(real_x<799-5)&&(real_y<599-5))
                            put_pixel(real_x,real_y,SYSTEM_WHITE,bitmap);
                        break;
                    case 1:
                        if((real_x>=5)&&(real_y>=5)&&(real_x<799-5)&&(real_y<599-5))
                            put_bar(real_x,real_y,2,2,SYSTEM_WHITE,bitmap);
                        break;
                    case 2:
                        if((real_x>=5)&&(real_y>=5)&&(real_x<799-5)&&(real_y<599-5))
                        {
                            put_pixel(real_x+1,real_y-1,SYSTEM_WHITE,bitmap);
                            put_pixel(real_x-1,real_y+1,SYSTEM_WHITE,bitmap);
                            put_pixel(real_x+3,real_y+1,SYSTEM_WHITE,bitmap);
                            put_pixel(real_x+1,real_y+3,SYSTEM_WHITE,bitmap);
                            put_bar(real_x,real_y,3,3,SYSTEM_WHITE,bitmap);
                        }
                        break;
                    default:
                        weather_snow_data[i].height=0;
                        break;
                    }
                    
                    weather_snow_data[i].height-=weather_parameter.snow_range;
                    if(weather_snow_data[i].height<=0)
                    {
                        if(weather_snow_data[i].size==0)
                            weather_snow_data[i].active=0;
                        else
                            weather_snow_data[i].active=2;
                    }
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                real_x=weather_snow_data[i].x-map_data.map_sx;
                real_y=weather_snow_data[i].y-map_data.map_sy;
                if((real_x>=5)&&(real_y>=5)&&(real_x<799-5)&&(real_y<599-5))
                    put_bar(real_x,real_y,2,2,SYSTEM_WHITE,bitmap);
                weather_snow_data[i].active++;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
                real_x=weather_snow_data[i].x-map_data.map_sx;
                real_y=weather_snow_data[i].y-map_data.map_sy;
                if((real_x>=5)&&(real_y>=5)&&(real_x<799-5)&&(real_y<599-5))
                    put_pixel(real_x,real_y,SYSTEM_WHITE,bitmap);
                weather_snow_data[i].active++;
                break;
            case 14:
                weather_snow_data[i].active=0;
                break;
            default:
                weather_snow_data[i].active=0;
                break;
            }
        }
    }

    // --------------- process thunder
    if(weather_parameter.status&WEATHER_THUNDER)
    {
        switch(weather_parameter.thunder_process_count)
        {
        case 20:
        case 18:
            put_bar(0,0,800,600,SYSTEM_WHITE,bitmap);
            break;
        case 12:
        case 10:
        case 8:
            put_bar(0,0,800,600,SYSTEM_WHITE,bitmap);
            break;
        case 4:
        case 3:
        case 2:
            put_bar(0,0,800,600,SYSTEM_WHITE,bitmap);
            break;
            // 撥放音效命令
        case 1:
            set_data_file(packed_sound_file);
            play_voice(0,0,(USTR *)"sound\\thunder.wav");
            break;
        }
    }
    
    
    // --------------- process cloud
    if(weather_parameter.status&WEATHER_CLOUD)
    {
        for(i=0;i<MAX_CLOUD;i++)
        {
            if(weather_cloud_data[i].active==0)continue;
            
            real_x=weather_cloud_data[i].x-map_data.map_sx;
            real_y=weather_cloud_data[i].y-map_data.map_sy;
            
            weather_cloud_data[i].x=weather_cloud_data[i].x+weather_parameter.x_offset;
            weather_cloud_data[i].y=weather_cloud_data[i].y+weather_parameter.y_offset;
            
            
            cloud_frame = get_specify_cake_frame_ani(cloud_cfa, weather_cloud_data[i].type);
            // ---- add 偏移量
            if(weather_cloud_data[i].timer>20*5)
            {
                if(weather_cloud_data[i].active>=0)
                {
                    weather_cloud_data[i].active-=5;
                    alpha_put_rle(real_x, real_y, cloud_frame->cake_frame->rle, bitmap,weather_cloud_data[i].active);
                }
                else
                {
                    weather_cloud_data[i].active=0;
                }
            }
            else
            {
                if(weather_cloud_data[i].active<=255)
                {
                    weather_cloud_data[i].active+=5;
                    alpha_put_rle(real_x, real_y, cloud_frame->cake_frame->rle, bitmap,weather_cloud_data[i].active);
                }
                else
                {
                    alpha_put_rle(real_x, real_y, cloud_frame->cake_frame->rle, bitmap,255);
                    weather_cloud_data[i].active=255;
                    weather_cloud_data[i].timer++;
                }
            }
        }
    }
}



void    weather_adjust_map_move(void)
{
    SLONG   dx, dy;
    SLONG   tx, ty;
	SLONG	npc_x, npc_y, npc_z;
    SLONG	e_count, y_off;
    
    switch(map_move.type)
    {
    case MAP_MOVE_STAY_CURRENT:
        break;
    case MAP_MOVE_TO_POSITION:
        dx = map_move.dest_x - map_data.map_sx;
        dy = map_move.dest_y - map_data.map_sy;
        map_data.map_sx += ZSGN(dx) * min(map_move.move_speed, abs(dx) % map_move.move_speed);
        map_data.map_sy += ZSGN(dy) * min(map_move.move_speed, abs(dy) % map_move.move_speed);
        break;
    case MAP_MOVE_FOLLOW_NPC:
        LOCK_CHARACTER(map_move.dest_npc);
		GetCharacterPosition(map_move.dest_npc, &npc_x, &npc_y, &npc_z);
        tx = npc_x - map_data.view_xl/2 - map_data.view_sx;
        ty = npc_y - npc_z - map_data.view_yl/2 - map_data.view_sy;
        UNLOCK_CHARACTER(map_move.dest_npc);
        map_data.map_sx = tx;
        map_data.map_sy = ty;
        /*
        if(map_data.map_sx < tx) map_data.map_sx ++;
        if(map_data.map_sx > tx) map_data.map_sx --;
        if(map_data.map_sy < ty) map_data.map_sy ++;
        if(map_data.map_sy > ty) map_data.map_sy --;
        */
        break;
    case MAP_MOVE_AUTO:
        map_data.map_sx += map_data.map_mx;
        map_data.map_sy += map_data.map_my;
        break;
    }
    
    // --------------- process earthquake
    if(weather_parameter.status&WEATHER_EARTHQUAKE)
    {
        y_off=0;
        if(weather_parameter.earthquake_process_count<20*2)
        {
            e_count=weather_parameter.earthquake_process_count%6;
            switch(e_count)
            {
            case 5:
                y_off=-3;
                break;
            case 4:
                y_off=3;
                break;
            case 3:
                y_off=-2;
                break;
            case 2:
                y_off=2;
                break;
            case 1:
                y_off=-1;
                break;
            case 0:
                y_off=1;
                break;
            default:
                y_off=0;
                break;
            }
        }
        
        switch(weather_parameter.earthquake_range)
        {
        case WEATHER_LARGE:
            y_off=y_off*3;
            break;
        case WEATHER_MIDDLE:
            y_off=y_off*2;
            break;
        case WEATHER_SMALL:
            y_off=y_off*1;
            break;
        }
        map_data.map_sy+=y_off;
    }
    
    if(map_move.keep_range)
    {
        if(map_data.map_sx < -map_data.view_sx)
            map_data.map_sx = -map_data.view_sx;
        if(map_data.map_sx > map_head.map_xl - map_data.view_xl - map_data.view_sx)
            map_data.map_sx = map_head.map_xl - map_data.view_xl - map_data.view_sx;
        if(map_data.map_sy < -map_data.view_sy)
            map_data.map_sy = -map_data.view_sy;
        if(map_data.map_sy > map_head.map_yl - map_data.view_yl - map_data.view_sy)
            map_data.map_sy = map_head.map_yl - map_data.view_yl - map_data.view_sy;
            /*
            if(map_data.map_sx < 0)
            map_data.map_sx = 0;
            if(map_data.map_sx > map_head.map_xl-SCREEN_WIDTH)
            map_data.map_sx = map_head.map_xl-SCREEN_WIDTH;
            if(map_data.map_sy < 0)
            map_data.map_sy = 0;
            if(map_data.map_sy > map_head.map_yl-SCREEN_HEIGHT)
            map_data.map_sy = map_head.map_yl-SCREEN_HEIGHT;
        */
    }
}


void    get_current_weather_wind(SLONG *wind_dir, SLONG *wind_range)
{
    if(wind_dir) *wind_dir = weather_parameter.wind_dir;
    if(wind_range) *wind_range = weather_parameter.wind_range;
}


SLONG   get_current_weather_type(void)
{
    // Jack, TODO: after update UI, this function will be updated. [17:57,10/21/2002]
    if( weather_parameter.status & WEATHER_RAIN)
        return  WEATHER_TYPE_RAIN;
    else if(weather_parameter.status & WEATHER_THUNDER)
        return  WEATHER_TYPE_THUNDER;
    else
        return  WEATHER_TYPE_FINE;
}


SLONG   weather_wind_dir_to_ui_wind_dir(SLONG weather_wind_dir)
{
    SLONG   ui_wind_dir;

    //介面的wind_dir自12點方向順時針旋轉,(0~360).
    switch(weather_wind_dir)
    {
    case WIND_RIGHT:
        ui_wind_dir = 90;
        break;
    case WIND_RIGHT_DOWN:
        ui_wind_dir = 135;
        break;
    case WIND_DOWN:
        ui_wind_dir = 180;
        break;
    case WIND_LEFT_DOWN:
        ui_wind_dir = 225;
        break;
    case WIND_LEFT:
        ui_wind_dir = 270;
        break;
    case WIND_LEFT_UP:
        ui_wind_dir = 315;
        break;
    case WIND_UP:
        ui_wind_dir = 0;
        break;
    case WIND_UP_RIGHT:
        ui_wind_dir = 45;
        break;
    default:
        ui_wind_dir = 0;
        break;
    }
    return  ui_wind_dir;
}


void	get_zone_weather_wind(ULONG *size, ULONG *dir)
{
	if(size) *size = weather_parameter.wind_range;
	if(dir) *dir = weather_parameter.wind_dir;
}



void	get_zone_weather_wind_for_boat(SLONG *dir, SLONG *force)
{
	SLONG	wind_dir, wind_size;

	get_current_weather_wind(&wind_dir, &wind_size);
	*dir = wind_dir;
	switch(wind_size)
	{
	case WIND_SMALL:	//小風
		*force = 5;
		break;
	case WIND_MIDDLE:	//中風
		*force = 10;
		break;
	case WIND_LARGE:	//大風
		*force = 20;
		break;
	case WIND_NONE:		//無風
	default:
		*force = 0;
		break;
	}
}


void	init_zone_weather(void)
{
	weather_parameter.status = WEATHER_NORMAL;
	weather_parameter.wind_dir = WIND_RIGHT_DOWN;
	weather_parameter.wind_range = WIND_MIDDLE;
}
