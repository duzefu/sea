/*
**  CHear.h
**  hear of map sound source.
**
**  ZJian,2001.4.28.
*/
#ifndef _CHEAR_H_INCLUDE_
#define _CHEAR_H_INCLUDE_


#define SNDSRC_NUM					256		//
#define AUDIBLE_NUM					3		//使用CHANNEL 0~2 播放地圖場景音效
#define	MENU_VOICE_CHANNEL			4		//使用CHANNEL 4 播放選單音效

#define	HEAR_RANGE_HALF_WIDTH		(SCREEN_WIDTH/2 + SCREEN_WIDTH/8)
#define	HEAR_RANGE_HALF_HEIGHT		(SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8)


//Sound Source State -------------------------------------------------------------------
#define SSS_UNUSED      0
#define SSS_INUSED      0x01
#define SSS_ONPLAY      0x02
#define SSS_ONPAUSE     0x04
//
//Sound Source Check Ticks
#define SSCT_WAIT       1
#define SSCT_PLAY       2

//Class specify ------------------------------------------------------------------------
class   CSoundSource
{
private:
    SLONG   state;
    SLONG   channel;
    SLONG   x,y,z;
    SLONG   min_ticks;
    SLONG   max_ticks;
    USTR    filename[_MAX_FNAME];
    double  distance;
    SLONG   volume;
    SLONG   ticks;
    SLONG   loop;

public:
    CSoundSource();
    ~CSoundSource();

    void    clear(void);
    void    set_position(SLONG x, SLONG y, SLONG z);
	void	get_position(SLONG *x, SLONG *y, SLONG *z);
    void    set_channel(SLONG chn);
    void    set_filename(USTR *filename);
    void    set_ticks(SLONG mintcs, SLONG maxtcs);
	void	get_ticks(SLONG *mintcs, SLONG *maxtcs);
    void    set_state(SLONG state);
    void    set_volume(SLONG vol);
    void    set_loop(SLONG loop);
    SLONG   get_state(void);
    SLONG   get_channel(void);
    USTR *  get_filename(void);
    SLONG   get_volume(void);
    SLONG   get_loop(void);
    double  check_dist(SLONG cx, SLONG cy, SLONG cz);
    double  get_dist(void);
    void    display(SLONG sx, SLONG sy, void *vbitmap);
    SLONG   check_ticks(void);
};



class   CHear
{
private:
    CSoundSource    sndsrc[SNDSRC_NUM];
    double  hear_range;
	//
	SLONG	stop_music_flag;
	SLONG	play_music_no;
	SLONG	loop_music_flag;

public:
    CHear();
    ~CHear();

    SLONG   add_sndsrc(SLONG x, SLONG y, SLONG z, SLONG mintcs, SLONG maxtcs, USTR *filename, SLONG loop);
    void    del_sndsrc(SLONG index);
    void    check_play(SLONG hear_x, SLONG hear_y, SLONG hear_z);
    void    clear(void);
    void    pause(void);
    void    display(SLONG sx, SLONG sy, void *vbitmap);
	void	set_stop_music_flag(SLONG stop_flag);
	void	set_play_music_data(SLONG music_no, SLONG loop_music);
	SLONG	get_stop_music_flag(void);
	void	get_play_music_data(SLONG *music_no, SLONG *loop_music);
	void	debug_log_file(USTR *filename);
	SLONG   load_from_file(USTR *filename);
	void	process_music(void);
};


extern  CHear   game_hear;


//global functions.
extern	void	play_fall_item_voice(SLONG item_no);
extern	void	play_hand_item_voice(SLONG item_no);
extern	void	play_npc_attack_voice(SLONG npc_no, SLONG file_index);
extern	void	play_npc_beated_voice(SLONG npc_no, SLONG file_index);
extern	void	play_npc_dead_voice(SLONG npc_no, SLONG file_index);
extern  void    play_npc_spower_voice(SLONG npc_no, SLONG file_index);
extern  void    play_npc_muse_voice(SLONG npc_no, SLONG file_index);
extern	void	play_npc_move_voice(SLONG npc_no, SLONG file_index);
extern	void	play_magic_start_voice(SLONG magic_index);
extern	void	play_magic_broken_voice(SLONG magic_index);
extern  void    play_npc_sequential_attack_voice(SLONG npc_no, SLONG file_index, SLONG sequential_index);
extern  void    play_npc_clash_voice(SLONG npc_no, SLONG file_index);




#endif//_CHEAR_H_INCLUDE_
