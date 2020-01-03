/*
**  CHear.cpp
**  hear of map sound source.
**
**  ZJian,2001.4.28.
*/
#include "MainFun.h"
#include "chear.h"
#include "ClientMain.h"



//#define   HEAR_DSBVOLUME      (DSBVOLUME_MIN)
//#define   HEAR_KK(k)          tan(3.1415927 / 2 * kk)
#define HEAR_DSBVOLUME      (-3000)
#define HEAR_KK(k)          k


CHear   game_hear;


//=============================================================================================================
// class CSoundSource
//=============================================================================================================
CSoundSource::CSoundSource()
{
    this->clear();
}


CSoundSource::~CSoundSource()
{
}


void    CSoundSource::set_channel(SLONG chn)
{
    this->channel = chn;
}


void    CSoundSource::set_position(SLONG x, SLONG y, SLONG z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}


void	CSoundSource::get_position(SLONG *x, SLONG *y, SLONG *z)
{
	*x = this->x;
	*y = this->y;
	*z = this->z;
}


void    CSoundSource::set_filename(USTR *filename)
{
    strcpy((char *)this->filename, (const char *)filename);
}


void    CSoundSource::set_ticks(SLONG mintcs, SLONG maxtcs)
{
    this->min_ticks = mintcs;
    this->max_ticks = maxtcs;
}


void	CSoundSource::get_ticks(SLONG *mintcs, SLONG *maxtcs)
{
	*mintcs = this->min_ticks;
	*maxtcs = this->max_ticks;
}


void    CSoundSource::set_state(SLONG state)
{
    this->state = state;
}


SLONG   CSoundSource::get_state(void)
{
    return this->state;
}


SLONG   CSoundSource::get_channel(void)
{
    return this->channel;
}


void    CSoundSource::set_loop(SLONG loop)
{
    this->loop = loop;
}


SLONG   CSoundSource::get_loop(void)
{
    return  this->loop;
}




void    CSoundSource::clear(void)
{
    this->state = SSS_UNUSED;
    this->channel = -1;
    memset(this->filename, '\0', _MAX_FNAME);
    strcpy((char *)this->filename,"NONAME.WAV");
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->min_ticks = 0;
    this->max_ticks = 9999;
    this->ticks = 0;
    this->loop = 0;
}


double  CSoundSource::check_dist(SLONG cx, SLONG cy, SLONG cz)
{
    this->distance = sqrt( (cx - this->x) * (cx - this->x) +
        (cy - this->y) * (cy - this->y) +
        (cz - this->z) * (cz - this->z) );
    return this->distance;
}


double  CSoundSource::get_dist(void)
{
    return this->distance;
}


USTR *  CSoundSource::get_filename(void)
{
    return (USTR *)this->filename;
}



void    CSoundSource::set_volume(SLONG vol)
{
    this->volume = vol;
}



SLONG   CSoundSource::get_volume(void)
{
    return this->volume;
}


SLONG   CSoundSource::check_ticks(void)
{
    return 0;
}


void    CSoundSource::display(SLONG sx, SLONG sy, void *vbitmap)
{
    enum {BAR_WIDTH = 8};
    BMP *bitmap = (BMP*)vbitmap;
    SLONG   under_x,under_y;
    SLONG   top_x, top_y;

    under_x = this->x - sx;
    under_y = this->y - sy;
    top_x = under_x;
    top_y = under_y - this->z;


    if( (under_x >= 0 && under_x < bitmap->w && under_y >= 0 && under_y < bitmap->h) ||
        (top_x >= 0 && top_x < bitmap->w && top_y >= 0 && top_y < bitmap->h) )
    {
        put_cross(under_x, under_y, SYSTEM_WHITE, bitmap);
        put_line(under_x, under_y, top_x, top_y, SYSTEM_PINK, bitmap);

        put_bar(top_x-BAR_WIDTH, top_y-BAR_WIDTH, BAR_WIDTH * 2, BAR_WIDTH * 2, SYSTEM_BLUE, bitmap);
        put_box(top_x-BAR_WIDTH+1, top_y-BAR_WIDTH+1, BAR_WIDTH * 2 - 2, BAR_WIDTH * 2 - 2,
            SYSTEM_YELLOW, bitmap);
        sprintf((char *)print_rec, "~C0~O3%d:%s~C0~O0", this->channel, strupr((char *)this->filename));
        print16(top_x-BAR_WIDTH, top_y+BAR_WIDTH+1, (USTR*)print_rec, PEST_PUT, bitmap);
        sprintf((char *)print_rec, "~C0~O3DIS:%f~C0~O0", this->distance);
        print16(top_x-BAR_WIDTH, top_y+BAR_WIDTH+1+16, (USTR*)print_rec, PEST_PUT, bitmap);
        sprintf((char *)print_rec, "~C0~O3VOL:%d~C0~O0", this->volume);
        print16(top_x-BAR_WIDTH, top_y+BAR_WIDTH+1+32, (USTR*)print_rec, PEST_PUT, bitmap);
    }
}


//=============================================================================================================
// class CHear
//=============================================================================================================
CHear::CHear()
{
    this->hear_range = sqrt( SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT );
    this->clear();
}


CHear::~CHear()
{
}


SLONG   CHear::add_sndsrc(SLONG x, SLONG y, SLONG z, SLONG mintcs, SLONG maxtcs, USTR *filename, SLONG loop)
{
    SLONG   i;
    SLONG   index;

    index = -1;
    for(i=0; i<SNDSRC_NUM; i++)
    {
        if( SSS_UNUSED == this->sndsrc[i].get_state() )
        {
            this->sndsrc[i].set_position( x, y, z );
            this->sndsrc[i].set_ticks( mintcs, maxtcs );
            this->sndsrc[i].set_filename( filename );
            this->sndsrc[i].set_state( SSS_INUSED );
            this->sndsrc[i].set_loop( loop );
            index = i;
            break;
        }
    }
    return index;
}


void    CHear::del_sndsrc(SLONG index)
{
    if(index>=0 && index<SNDSRC_NUM)
    {
        this->sndsrc[index].clear();
    }
}


void    CHear::check_play(SLONG hear_x, SLONG hear_y, SLONG hear_z)
{
    static  double  distance[AUDIBLE_NUM];
    static  SLONG   sndsrc_no[AUDIBLE_NUM];
    static  SLONG   unused_channel[AUDIBLE_NUM];
    USTR    filename[_MAX_FNAME];
    SLONG   i,j,k;
    SLONG   near_flag;
    SLONG   sndsrc_index;
    double  chk_dist;
    double  kk;
    SLONG   unused_channel_max;
    SLONG   voice_channel;
    SLONG   voice_loop;

    //預先初始化
    for(i=0; i<AUDIBLE_NUM; i++)
    {
        distance[i] = this->hear_range;
        sndsrc_no[i] = -1;
        unused_channel[i] = -1;
    }

    //計算所有的聲源的距離和音量
    for(i=0; i<SNDSRC_NUM; i++)
    {
        if( SSS_INUSED == this->sndsrc[i].get_state() )
        {
            this->sndsrc[i].check_dist( hear_x, hear_y, hear_z );
            kk = this->sndsrc[i].get_dist() / ( 1.0 + fabs(this->hear_range) );
            if(kk > 1.0) kk = 0.99999;
            this->sndsrc[i].set_volume( (SLONG)(HEAR_DSBVOLUME * HEAR_KK(kk) ) );

            //對正在播放的聲源作音量控制
            voice_channel = this->sndsrc[i].get_channel();
            if(voice_channel >= 0)
            {
                if( is_voice_playing(voice_channel) )
                {
                    set_voice_volume(voice_channel, this->sndsrc[i].get_volume() );
                }
                else
                {
                    //geaan, 2001.10.19. add loop control here.
                    voice_loop = this->sndsrc[i].get_loop();
                    if( voice_loop )
                    {
                        //remain this sndsrc
                        this->sndsrc[i].set_channel( -1 );
                    }
                    else
                    {
                        //delete this sndsrc
                        this->sndsrc[i].clear();
                    }
                    //this->sndsrc[i].set_channel( -1 );

                }
            }
            //對未播放的聲源按照離聽眾的距離由近到遠排序
            else
            {
                chk_dist = this->sndsrc[i].get_dist();
                near_flag = 0;
                for(j=0; j<AUDIBLE_NUM; j++)
                {
                    if(chk_dist < distance[j])
                    {
                        for(k=AUDIBLE_NUM-2; k >= j; k--)
                        {
                            distance[k+1] = distance[k];
                            sndsrc_no[k+1] = sndsrc_no[k];
                        }
                        distance[j] = chk_dist;
                        sndsrc_no[j] = i;
                        
                        j = AUDIBLE_NUM + 100;  //break;
                        near_flag = 1;
                    }
                }
            }
        }
    }

    //搜尋沒有被使用的聲音通道
    unused_channel_max = 0;
    for(i=0; i<AUDIBLE_NUM; i++)
    {
        if( ! is_voice_playing(i) )
        {
            unused_channel[unused_channel_max++] = i;
        }
    }

    //將需要播放的聲源按照可用的通道數目開始播放
    for(i=0; i<unused_channel_max; i++)
    {
        sndsrc_index = sndsrc_no[i];
        voice_channel = unused_channel[i];
        if(sndsrc_index >= 0)
        {
            this->sndsrc[sndsrc_index].set_channel( voice_channel );

            set_data_file(packed_sound_file);
            sprintf((char *)filename,"sound\\%s", this->sndsrc[sndsrc_index].get_filename() );
            play_voice(voice_channel, 0,  (USTR*)filename);
            set_voice_volume(voice_channel, this->sndsrc[sndsrc_index].get_volume() );
        }
    }
}


void    CHear::clear(void)
{
    SLONG   i;

    for(i=0; i<SNDSRC_NUM; i++)
    {
        this->sndsrc[i].clear();
    }
    for(i=0; i<AUDIBLE_NUM; i++)
    {
        stop_voice( i );
    }
	this->stop_music_flag = 0;
	this->play_music_no = -1;
	this->loop_music_flag = 0;
}


void    CHear::pause(void)
{
    SLONG   i;

    for(i=0; i<AUDIBLE_NUM; i++)
    {
        stop_voice( i );
    }
}


void    CHear::display(SLONG sx, SLONG sy, void *vbitmap)
{
    SLONG   i;
    SLONG   disp_x,disp_y;
    BMP *   bitmap = (BMP*)vbitmap;

    for(i=0; i<SNDSRC_NUM; i++)
    {
        if( SSS_INUSED == this->sndsrc[i].get_state() )
        {
            this->sndsrc[i].display(sx, sy, vbitmap);
        }
    }

    disp_x = 4;
    disp_y = 40;
    for(i=0; i<SNDSRC_NUM; i++)
    {
        if( SSS_INUSED == this->sndsrc[i].get_state() )
        {
            sprintf((char *)print_rec,"~C0~O3SS:[%3d]%s[%3d][%f]~C0~O0", 
                i, this->sndsrc[i].get_filename(), this->sndsrc[i].get_channel(), this->sndsrc[i].get_dist());
            print16(disp_x, disp_y, (USTR*)print_rec, PEST_PUT, bitmap);
            disp_y += 16;
        }
    }
}


void	CHear::set_stop_music_flag(SLONG flag)
{
	this->stop_music_flag = flag;
}


void	CHear::set_play_music_data(SLONG music_no, SLONG loop_music)
{
	this->play_music_no = music_no;
	this->loop_music_flag = loop_music;
}


SLONG	CHear::get_stop_music_flag(void)
{
	return	this->stop_music_flag;
}


void	CHear::get_play_music_data(SLONG *music_no, SLONG *loop_music)
{
	*music_no = this->play_music_no;
	*loop_music = this->loop_music_flag;
}


void	CHear::debug_log_file(USTR *filename)
{
#ifdef  DEBUG
	FILE*	fp = NULL;
	USTR	line[1024];
	SLONG	i;
	SLONG	x, y, z;
	SLONG	min_ticks, max_ticks;
	USTR	wav_filename[_MAX_FNAME];

	if( is_file_exist((USTR*)filename) )
		remove((const char *)filename);
	if(NULL == (fp = fopen((const char *)filename, "a+")) )
	{
		log_error(1, "file %s open error", filename);
		return;
	}
	sprintf((char *)line, "STOP_MUSIC = %d\n", this->stop_music_flag);
	fputs((const char *)line, fp);
	sprintf((char *)line, "PLAY_MUSIC = %d, %d\n", this->play_music_no, this->loop_music_flag );
	fputs((const char *)line, fp);
	for(i=0; i<SNDSRC_NUM; i++)
	{
		if( SSS_UNUSED != sndsrc[i].get_state())
		{
			sndsrc[i].get_position(&x, &y, &z);
			sndsrc[i].get_ticks(&min_ticks, &max_ticks);
			strcpy((char *)wav_filename, (const char *)sndsrc[i].get_filename());
			//
			sprintf((char *)line, "ADD_SNDSRC = %d, %d, %d, %d, %d, %s\n", 
				x, y, z, min_ticks, max_ticks, wav_filename);
			fputs((const char *)line, fp);
		}
	}
	fputs((const char *)"\n", fp);

	if(fp) fclose(fp);
	return;
#endif//DEBUG
}


SLONG   CHear::load_from_file(USTR* filename)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    line[LINE_BUFFER_SIZE];
    USTR    temp[256];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
	SLONG	stop_flag, play_no, loop_flag;
	SLONG	x, y, z, min_ticks, max_ticks;
	SLONG	wav_filename[_MAX_FNAME];

    file_size = load_file_to_buffer(filename, &file_buf);
    if(file_size < 0)
        return TTN_NOT_OK;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            
            skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
            get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
            
            if(strcmpi((const char *)"STOP_MUSIC", (const char *)temp) == 0)
            {
                //stop_flag
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                stop_flag = string_2_number((char *)temp);
                
                this->set_stop_music_flag(stop_flag);
            }
            else if(strcmpi((const char *)"PLAY_MUSIC", (const char *)temp) == 0)
            {
                //music_no
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                play_no = string_2_number((char *)temp);
                
                //loop_flag
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                loop_flag = string_2_number((char *)temp);
                
                this->set_play_music_data(play_no, loop_flag);
            }
            else if(strcmpi((const char *)"ADD_SNDSRC", (const char *)temp) == 0)
            {
                //x
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                x = string_2_number((char *)temp);
                //y
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                y = string_2_number((char *)temp);
                //z
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                z = string_2_number((char *)temp);
                //min_ticks
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                min_ticks = string_2_number((char *)temp);
                //max_ticks
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                max_ticks = string_2_number((char *)temp);
                //wav_filename
                skip_compartment((USTR*)line, &index, (USTR*)"= ,\x09", 4);
                get_string(temp, 255, line, &index, (USTR *)"= ,\x09", 4);
                strcpy((char *)wav_filename, (const char *)temp);
                
                this->add_sndsrc(x, y, z, min_ticks, max_ticks, (USTR*)wav_filename, 1);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    
    return  TTN_OK;
}


void	CHear::process_music(void)
{
	if(this->stop_music_flag)
	{
		stop_music();
	}
	if(this->play_music_no >= 0)
	{
        set_data_file(packed_music_file);
		play_music(this->play_music_no, this->loop_music_flag);
	}
}


//====================================================================================================
// OTHER VOICE FUNCTIONS
//====================================================================================================
void	play_fall_item_voice(SLONG item_no)
{
    // Jack, for SEAAGE. [16:16,9/30/2002]
    /*
	USTR	filename[_MAX_FNAME];

	switch(item_no)
	{
	case ITEM_BASE_NONE:
		break;
	case ITEM_BASE_MONEY:
		break;
	default:
		if(item_no >= 0 && item_no < MAX_ITEM_BASE)
		{
            set_data_file(packed_sound_file);
			sprintf((char *)filename, "SOUND\\%s", item_base[item_no].fall_wav);
			//play_3dvoice(0, 0, (USTR*)filename);
			//play_voice(0, 0, (USTR*)filename);
			direct_play_voice(4, 6, 0, (USTR*)filename);
		}
		break;
	}
	return;
    */
}


void	play_hand_item_voice(SLONG item_no)
{
    // Jack, for SeaAge. [16:16,9/30/2002]
    /*
	USTR	filename[_MAX_FNAME];

	switch(item_no)
	{
	case ITEM_BASE_NONE:
		break;
	case ITEM_BASE_MONEY:
		break;
	default:
        set_data_file(packed_sound_file);
		sprintf((char *)filename, "SOUND\\HANDITEM.WAV");
		//play_voice(0, 0, (USTR*)filename);
		direct_play_voice(4, 6, 0, (USTR*)filename);
		break;
	}
	return;
    */
}


void	play_npc_move_voice(SLONG npc_no, SLONG file_index)
{
    // Jack, for SeaAge. [16:16,9/30/2002]
    /*
	USTR	filename[_MAX_FNAME];

	//~C is move voice.
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "SOUND\\NPC%03dC.WAV", file_index);
	direct_play_voice(4, 6, 0, (USTR *)filename);

	return;
    */
}


void	play_npc_attack_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %4d + 00
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d00.wav", file_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void	play_npc_beated_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %4d + 01
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d01.wav", file_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void	play_npc_dead_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %04d + 11
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d11.wav", file_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void    play_npc_spower_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %04d + 03
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d03.wav", file_index);
	//direct_play_voice(1, 6, 1, (USTR*)filename);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void    play_npc_muse_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %04d + 12
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d12.wav", file_index);
	//direct_play_voice(1, 6, 1, (USTR*)filename);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void	play_magic_start_voice(SLONG magic_index)
{
    // Jack, for seaage. [16:19,9/30/2002]
    /*
	USTR	filename[_MAX_FNAME];

    set_data_file(packed_sound_file);
	sprintf((char *)filename, "SOUND\\MAG%03dA.WAV", magic_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
    */
}


void	play_magic_broken_voice(SLONG magic_index)
{
    // Jack, for seaage. [16:19,9/30/2002]
    /*
	USTR	filename[_MAX_FNAME];

    set_data_file(packed_sound_file);
	sprintf((char *)filename, "SOUND\\MAG%03dB.WAV", magic_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
    */
}


void    play_npc_sequential_attack_voice(SLONG npc_no, SLONG file_index, SLONG sequential_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %04d + (05,06,07,08,09), 五連擊
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d%02d.wav", file_index, 05 + sequential_index - 1);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}


void    play_npc_clash_voice(SLONG npc_no, SLONG file_index)
{
	USTR	filename[_MAX_FNAME];

    //fg + %04d + 10
    set_data_file(packed_sound_file);
	sprintf((char *)filename, "sound\\fg%04d10.wav", file_index);
	direct_play_voice(1, 6, 0, (USTR*)filename);

	return;
}
