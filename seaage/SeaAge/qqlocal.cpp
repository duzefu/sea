/*
 * qqlocal.cpp
 * functions for save and load qq infomation
 * Zhang Zhaohui
 * 2002.10.11
 *
 * filename
 *                chat file: playername.cht
 *      system message file: playername.msg
 */

#include "qqlocal.h"
#include "clientmain.h"

//////////////////////////////////////////////////////////////////////////


// create key for encode, multi-call rand()
#define MAKE_ORG_KEY(a)     ((DWORD)(\
                            (((DWORD)a&0xff)<<16)\
                            |(((DWORD)a&0xff00)<<16)\
                            |((DWORD)a&0xff)\
                            |(((DWORD)a&0xff00))\
                            ))

// get key from save file header
#define GET_KEY(a,b)        ((((DWORD)a<<16)&0xff000000) \
                            |(((DWORD)a<<8)&0xff00) \
                            |(((DWORD)b<<8)&0xff0000) \
                            |(((DWORD)b)&0xff))

//////////////////////////////////////////////////////////////////////////

// EXT. file name
const char MSG_FILE_EXT[]           = "msg";
const char CHAT_FILE_EXT[]          = "cht";
const char CHAT_INDEX_FILE_EXT[]    = "cti";


// Save file sign
const char MSG_FILE_SIGN[]          = "raysmsg";
const char CHAT_FILE_SIGN[]         = "rayscht";
const char CHAT_INDEX_FILE_SIGN[]   = "rayscti";


// File type
enum QQLOCAL_FILE_TYPE
{
    MSG_FILE                = 1,
    CHAT_FILE               = 2,
    CHAT_INDEX_FILE         = 5,
    QL_VERSION              = 100,
    QL_BUFSIZE              = 0x4000, // 16K
};


// Filename buffer
char msg_file[MAX_PATH];
char chat_file[MAX_PATH];
char chat_index_file[MAX_PATH];

typedef struct tagUI_QQLOCAL
{
    FILE*    fp;                // data file pointer
    DWORD    offset;            // next block offset, 0 is the last one
    DWORD    player;            // player server ID
    DWORD    key;               // key
    DWORD    sid;               // server ID        ( chat file only )
} UI_QQLOCAL, *LPUI_QQLOCAL;


UI_QQLOCAL lchat;           // chat log information
UI_QQLOCAL lmsg;            // system message information
QLCI_BLOCK *i_buf = NULL;
//////////////////////////////////////////////////////////////////////////

static BOOL     ql_file_exists(char *filename);
static LONG     ql_clear_filename( VOID );
static VOID     ql_make_filename( VOID );
static LONG     ql_make_dir( VOID );
static LONG     ql_encode(char *buf, LONG size, DWORD key);
static LONG     ql_decode(char *buf, LONG size, DWORD key);
static DWORD    ql_check_code(char *buf, LONG size);
static VOID     ql_check_filename(VOID);
static BOOL     ql_move_file_ex( char *src_file, char *des_file);
static char     *ql_get_server_name( VOID );
static VOID     ql_close_all_file( VOID );
static BOOL     ql_read_block( FILE* fp, DWORD key, DWORD offset, QL_BLOCK* p_block);
static BOOL     ql_write_block( FILE* fp, DWORD key, DWORD next_offset, CHAR *name, CHAR *text );
static BOOL     ql_check_file( VOID *header, LONG filetype );
static DWORD    ql_make_org_key( DWORD a );
static DWORD    ql_get_key( WORD a, WORD b );
static WORD     ql_set_key1( DWORD a );
static WORD     ql_set_key2( DWORD a );

/************************************************************************/
/* Init/Free/OnLogin/OnLogout Functions                                 */
/************************************************************************/

LONG ql_init( VOID )
{
    ql_clear_filename( );
 
    memset( &lchat, 0, sizeof( lchat ) );
    memset( &lmsg, 0, sizeof( lmsg ) );

    i_buf = (QLCI_BLOCK*)malloc( QL_BUFSIZE );
    if ( !i_buf )
    {
        log_error( 1, "Error: Can not get enough memory for index file buffer" );
        return TTN_NOT_OK;
    }

    return TTN_OK;
}


VOID ql_free( VOID )
{
    ql_clear_filename( );
    ql_close_all_file( );

    memset( &lchat, 0, sizeof( lchat) );
    memset( &lmsg, 0, sizeof( lmsg ) );
    
    if ( i_buf )
    {
        free( i_buf );
        i_buf = NULL;
    }
}

LONG ql_on_login(VOID)
{
    if ( lchat.fp || lmsg.fp )
        ql_on_logout( );

   ql_make_dir( );
    ql_make_filename( );
    memset( i_buf, 0, QL_BUFSIZE );

    return TTN_OK;
}


LONG ql_on_logout(VOID)
{
    ql_clear_filename( );
    ql_close_all_file( );

    lchat.offset    = 0;
    lchat.player    = 0;
    lchat.sid = 0;

    lmsg.offset   = 0;
    lmsg.player   = 0;

    return TTN_OK;
}


/************************************************************************/
/* Load/Save message                                                    */
/************************************************************************/

BOOL ql_get_first_msg( time_t* p_ltime, CHAR * p_message )
{
    QLM_HEADER header;
    QL_BLOCK block;

    if ( NULL == ( lmsg.fp = fopen( msg_file, "r+b" ) ) )
        goto error;

    fread( &header, 1, sizeof( QLM_HEADER), lmsg.fp );
    if ( !ql_check_file( &header, MSG_FILE ) )
        goto error;

    lmsg.key = ql_get_key( header.key1, header.key2 );
    lmsg.offset = header.first_offset;
    
    if ( !ql_read_block( lmsg.fp, lmsg.key, lmsg.offset, &block ) )
        goto error;
    
    lmsg.offset = block.next_offset;
    lstrcpyn( p_message, block.text_buf, QL_MAX_TEXT_SIZE );
    *p_ltime = block.time;

    return TRUE;

error:
    if ( lmsg.fp )
    {
        fclose( lmsg.fp );
        lmsg.fp = NULL;
    }
    lmsg.key = 0;
    lmsg.offset = 0;
    *p_ltime = 0;
    p_message[0] = '\0';
    return FALSE;
}


BOOL ql_get_next_msg( time_t* p_ltime, CHAR* p_message )
{
    QL_BLOCK block;

    if ( lmsg.offset == 0 || lmsg.fp == NULL )
    {
        p_message[0] = '\0';
        *p_ltime = 0;
        return FALSE;
    }

    if ( !ql_read_block( lmsg.fp, lmsg.key, lmsg.offset, &block ) )
    {
        log_error( 1, "Error: Can not read message save file block" );
        p_message[0] = '\0';
        *p_ltime = 0;
        return FALSE;
    }

    lstrcpyn( p_message, block.text_buf, QL_MAX_TEXT_SIZE );
    *p_ltime = block.time;

    lmsg.offset = block.next_offset;

    return TRUE;
}

VOID ql_get_msg_end( VOID )
{
    if ( lmsg.fp )
    {
        fclose( lmsg.fp );
        lmsg.fp = NULL;
    }
    lmsg.key = 0;
    lmsg.offset = 0;
}

//////////////////////////////////////////////////////////////////////////

BOOL ql_add_msg( char *message )
{
    QLM_HEADER header;
    DWORD next_offset;
    DWORD org_key;
    BOOL need_close = FALSE;


    if ( !ql_file_exists( msg_file ) )
    {

        if ( NULL == ( lmsg.fp = fopen( msg_file, "w+b" ) ) )
        {
            log_error( 1, "Error: Can not create message save file." );
            return FALSE;
        }
        
        srand( timeGetTime( ) );
        org_key = ql_make_org_key( ( rand() << 16 ) | rand() );
        
        // init file header and write it to file
        strcpy( header.sign, MSG_FILE_SIGN );
        header.version = QL_VERSION;
        header.total_msg = NULL;
        header.first_offset = 0;
        header.key1 = ql_set_key1( org_key );
        header.key2 = ql_set_key2( org_key );
        memset( header.reserved, 0, QL_RESERVED_SIZE );
        
        fwrite( &header, 1, sizeof( QLM_HEADER ), lmsg.fp );
        
        lmsg.key = ql_get_key( header.key1, header.key2 );
        need_close = TRUE;
    }
    else
    {
        if ( !lmsg.fp )
        {
            if ( NULL == ( lmsg.fp = fopen( msg_file, "r+b" ) ) )
            {
                log_error( 1, "Error: Can not open chat save file." );
                return FALSE;
            }
            need_close = TRUE;
        }

        // read file header
        fseek( lmsg.fp, 0, SEEK_SET );
        fread( &header, 1, sizeof( QLM_HEADER ), lmsg.fp );
        fseek( lmsg.fp, 0, SEEK_END );
        lmsg.key = ql_get_key( header.key1, header.key2 );

    }

    next_offset = header.first_offset;
    header.first_offset = ftell( lmsg.fp );
    header.total_msg++;

    // save block
    ql_write_block( lmsg.fp, lmsg.key, next_offset, NULL, message );

    fseek( lmsg.fp, 0, SEEK_SET );
    fwrite( &header, 1, sizeof( QLM_HEADER ), lmsg.fp );

    if ( need_close )
    {
        fclose( lmsg.fp );
        lmsg.fp = NULL;
        lmsg.key = 0;
    }
    
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////

DWORD ql_get_msg_count( VOID )
{
    QLM_HEADER header;
    DWORD result = 0;

    if ( lmsg.fp )
    {
        fseek( lmsg.fp, 0, SEEK_SET );
        fread( &header, 1, sizeof( header ), lmsg.fp );
    }
    else
    {
        if( NULL == ( lmsg.fp = fopen( msg_file, "rb" ) ) )
            return 0;
        fread( &header, 1, sizeof( header ), lmsg.fp );
        fclose( lmsg.fp );
        lmsg.fp = NULL;
    }

    if( ql_check_file( &header, MSG_FILE ) )
        result = header.total_msg;

    return result;
}


/************************************************************************/
/* Load/Save chat                                                       */
/************************************************************************/

/*
    INDEX FILE

  _______________________
 |                       |
 |        Header         |      ______________________
 |_______________________|     |                      |
 |                       |     |         ID           |
 |        Block          |---->|______________________|
 |_______________________|     |                      |
 |                       |     |       Offset         |
 |        Block          |     |______________________|
 |_______________________|               |
 |                       |               |
 |        .....          |               |
 |_______________________|               |
 |                       |               |
 |        Block          |               |
 |_______________________|               |
                                         |
                                         |
                                         |
    CHAT FILE                            |
  _______________________                |
 |                       |               |
 |        Header         |               |
 |_______________________|               |
 |                       |<--------------O
 |        Block          |      ______________________ 
 |_______________________|     |                      |
 |                       |     |     Block Size       |
 |        Block          |---->|______________________|
 |_______________________|     |                      |
 |                       |     |     Check Code       |
 |        Block          |     |______________________|
 |_______________________|     |                      |
 |                       |     |     Next Block       |
 |        .....          |     |______________________|
 |_______________________|     |                      |
 |                       |     |         Time         |
 |        Block          |     |______________________|
 |_______________________|     |                      |
                               |         Name         |
                               |______________________|
                               |                      |
                               |         Text         |
                               |______________________|

*/
// 讀取第一條聊天消息
BOOL ql_get_first_chat( DWORD sid, CHAR *name, time_t* ltime, CHAR *text )
{
    QLCI_HEADER     iheader;
    QLC_HEADER      header;
    QL_BLOCK        block;
    LP_QLCI_BLOCK   p_block = NULL;
    DWORD           i = 0;
    DWORD           block_size = 0;;

    FILE *ifp = NULL;

    if ( NULL == ( ifp = fopen( chat_index_file, "rb") ) )
        goto error;

    if ( NULL == ( lchat.fp = fopen( chat_file, "rb" ) ) )
        goto error;

    // read file header
    fread( &iheader, 1, sizeof( iheader ), ifp );
    fread( &header, 1, sizeof( header ), lchat.fp );

    // check file sign
    if ( !ql_check_file( &iheader, CHAT_INDEX_FILE ) || 
         !ql_check_file( &header, CHAT_FILE ) )
        goto error;

    // read index file block
    fread( i_buf, 1, QL_BUFSIZE, ifp  );
    fclose( ifp );
    
    // look for specify server ID
    while ( i < iheader.count )
    {
        if ( i_buf[i].sid == 0 )
            continue;
        
        if ( i_buf[i].sid == sid )
            break;

        i++;
    }

    if ( i == iheader.count )        // not found
        goto error;

    lchat.offset = i_buf[i].offset;
    lchat.sid = i_buf[i].sid;
    
    lchat.key = ql_get_key( header.key1, header.key2 );

    // read save block
    if ( !ql_read_block( lchat.fp, lchat.key, lchat.offset, &block ) )
    {
        log_error( 1, "Error: Read chat block failed." );
        goto error;
    }

    lstrcpyn( text, block.text_buf, QL_MAX_TEXT_SIZE );
    *ltime = block.time;
    lstrcpyn( name, block.name, QL_NAME_TEXT_SIZE );
    
    lchat.offset = block.next_offset;

    return TRUE;

error:
    if ( lchat.fp )
    {
        fclose( lchat.fp );
        lchat.fp = NULL;
    }
    if ( ifp )
    {
        fclose( ifp );
        ifp = NULL;
    }

    lchat.sid        = 0;
    lchat.key        = 0;
    lchat.offset    = 0;

    ltime = 0;
    text[0] = '\0';

    return FALSE;
}


BOOL ql_get_next_chat( CHAR *name, time_t* p_ltime, CHAR* p_text )
{
    QL_BLOCK block;

    if ( lchat.offset == 0 )
        return FALSE;

    if ( lchat.sid == 0 || lchat.key == 0 || 
         lchat.fp == NULL )
        goto error;

    if ( !ql_read_block( lchat.fp, lchat.key, lchat.offset, &block ) )
    {
        log_error( 1, "Error: Read save file block failed" );
        goto error;
    }

    lstrcpyn( p_text, block.text_buf, QL_MAX_TEXT_SIZE );
    *p_ltime = block.time;
    lstrcpyn( name, block.name, QL_NAME_TEXT_SIZE );
    lchat.offset = block.next_offset;
    
    return TRUE;

error:
    *p_ltime = 0;
    p_text[0] = '\0';
    return FALSE;
}


VOID ql_get_chat_end( VOID )
{
    lchat.sid = 0;
    lchat.key = 0;
    lchat.offset = 0;
    if ( lchat.fp )
    {
        fclose( lchat.fp );
        lchat.fp = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////

BOOL ql_add_chat( DWORD sid, CHAR *name, CHAR *text )
{
    QLC_HEADER header;
    QLCI_HEADER iheader;
    DWORD org_key, i;
    BOOL need_close;
    FILE* ifp = NULL;
    FILE* fp = NULL;
    CHAR filename[MAX_PATH];
    DWORD next_offset;

    if ( !ql_file_exists( chat_index_file ) )
    {
        if ( ql_file_exists( chat_file ) )
        {
            // backup chat save
            wsprintf( filename, "%s.bak", chat_file );
            ql_move_file_ex( chat_file, filename );
        }
        if ( NULL == ( ifp = fopen( chat_index_file, "w+b" ) ) )
        {
            log_error( 1, "Error: Can not create chat index file." );
            return FALSE;
        }
        if ( NULL == ( fp = fopen( chat_file, "w+b" ) ) )
        {
            fclose( fp );
            log_error( 1, "Error: Can not create chat file." );
            return FALSE;
        }

        // write index file header
        lstrcpyn( iheader.sign, CHAT_INDEX_FILE_SIGN, QL_FILE_SIGN_SIZE );
        iheader.version = QL_VERSION;
        iheader.count = 0;
        memset( iheader.reserved, 0, QL_RESERVED_SIZE );
        fwrite( &iheader, 1, sizeof( QLCI_HEADER ), ifp );

        // make encode key
        srand( timeGetTime( ) );
        org_key = ql_make_org_key( rand() | ( rand() << 16 ) );

        // write chat file header
        lstrcpyn( header.sign, CHAT_FILE_SIGN, QL_FILE_SIGN_SIZE );
        header.version = QL_VERSION;
        header.key1 = ql_set_key1( org_key );
        header.key2 = ql_set_key2( org_key );
        memset( header.reserved, 0, QL_RESERVED_SIZE );
        fwrite( &header, 1, sizeof( QLC_HEADER ), fp );

        // clear block
        memset( i_buf, 0, QL_BUFSIZE );
        
        need_close = TRUE;
    }
    else
    {
        if ( NULL == ( ifp = fopen( chat_index_file, "r+b" ) ) )
        {
            log_error( 1, "Error: Can not open chat index file." );
            return FALSE;
        }
        if ( !lchat.fp )
        {
            if ( NULL == ( fp = fopen( chat_file, "r+b" ) ) )
            {
                fclose( fp );
                log_error( 1, "Error: Cant not open chat file." );
                return FALSE;
            }
            need_close = TRUE;
        }
        else
        {
            fp = lchat.fp;
            need_close = FALSE;
        }
        
        fread( &iheader, 1, sizeof( QLCI_HEADER), ifp );
        fseek( fp, 0, SEEK_SET );
        fread( &header, 1, sizeof(QLC_HEADER), fp );

        if ( !ql_check_file( &iheader, CHAT_INDEX_FILE ) ||
             !ql_check_file( &header, CHAT_FILE ) ||
             ( iheader.count == QL_BUFSIZE/sizeof( QLCI_BLOCK ) ) )
        {
            if ( need_close )
                fclose( fp );
            fclose( ifp );
            fp = NULL;
            ifp = NULL;
            return FALSE;
        }
        fread( i_buf, 1, QL_BUFSIZE, ifp );
        org_key = ql_get_key( header.key1, header.key2 );
    }

    i = 0;

    while ( i < iheader.count )
    {
        if ( i_buf[i].sid == 0 )
            continue;
        
        if ( i_buf[i].sid == sid )
            break;

        i++;
    }
    
    if ( i == iheader.count )
    {
        for ( i = 0; i < QL_BUFSIZE/sizeof( QLCI_BLOCK ); i++ )
        {
            if ( i_buf[i].sid == 0 )
                break;
        }
    }

    next_offset = i_buf[i].offset;
    fseek( fp, 0, SEEK_END );
    i_buf[i].offset = ftell( fp );

    ql_write_block( fp, org_key, next_offset, name, text );
    fseek( ifp, 0, SEEK_SET );

    if ( i_buf[i].sid == 0 )
    {
        iheader.count++;
        i_buf[i].sid = sid;
    }
    
    fseek( ifp, 0, SEEK_SET );
    fwrite( &iheader, 1, sizeof( iheader ), ifp );
    fwrite( i_buf, 1, QL_BUFSIZE, ifp );

    if ( fp && need_close )
    {
        fclose( fp );
        fp = NULL;
    }
    if ( ifp )
    {
        fclose( ifp );
        ifp = NULL;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////

VOID ql_del_chat( DWORD sid )
{
    FILE *ifp;
    QLCI_HEADER iheader;
    DWORD i = 0;

    if ( !ql_file_exists( chat_index_file ) )
        return;

    if ( NULL == ( ifp = fopen( chat_index_file, "r+b" ) ) )
    {
        log_error( 1, "Error: open file %s error.", chat_index_file );
        return;
    }
    
    fread( &iheader, 1, sizeof(QLCI_HEADER), ifp );
    fread( i_buf, 1, QL_BUFSIZE, ifp );
    if ( !ql_check_file( &iheader, CHAT_INDEX_FILE ) )
    {
        fclose( ifp );
        return;
    }

    while( i < iheader.count )
    {
        if ( i_buf[i].sid == sid )
            break;

        if ( i_buf[i].sid == 0 )
            continue;

        i++;
    }
    if ( i != iheader.count )
    {
        i_buf[i].offset = 0;
        i_buf[i].sid = 0;
        iheader.count--;
        fseek( ifp, 0, SEEK_SET );
        fwrite( &iheader, 1, sizeof(QLC_HEADER), ifp );
        fwrite( i_buf, 1, QL_BUFSIZE, ifp );
    }
    fclose( ifp );
}

/************************************************************************/
/* Local Function ( static )                                            */
/************************************************************************/

BOOL ql_file_exists(char *filename)
{
    HANDLE h_file;
    WIN32_FIND_DATA find_data;
    BOOL result;
    
    h_file = FindFirstFile((LPCSTR)filename, &find_data);

    result = (h_file != INVALID_HANDLE_VALUE);

    if (result)
        FindClose(h_file);
    
    return result;
}

VOID ql_make_filename( VOID )
{
    char player_name[QL_NAME_TEXT_SIZE];
    char world_name[QL_NAME_TEXT_SIZE];
    char file_ext[QL_NAME_TEXT_SIZE];
    char *str;

    // get server name
    str = ql_get_server_name( );
    lstrcpyn( world_name, str, QL_NAME_TEXT_SIZE );

    // get player main name
    lstrcpyn( player_name, g_szPlayerMainName, QL_NAME_TEXT_SIZE );

    // chat save file
    lstrcpy( file_ext, CHAT_FILE_EXT );
    wsprintf( chat_file, "%s\\save\\%s\\%s.%s", game_path, world_name, 
                                            player_name, file_ext);

    // chat index save file
    lstrcpy( file_ext, CHAT_INDEX_FILE_EXT );
    wsprintf( chat_index_file, "%s\\save\\%s\\%s.%s", game_path, world_name, 
                                            player_name, file_ext);

    // message save file
    lstrcpy( file_ext, MSG_FILE_EXT );
    wsprintf( msg_file, "%s\\save\\%s\\%s.%s", game_path, world_name, 
                                            player_name, file_ext );
}

LONG ql_make_dir(VOID)
{
    char tmp[MAX_PATH];
    char *str;
    BOOL dir_exist = FALSE;

    wsprintf(tmp, "%s\\save", game_path);

    dir_exist = ql_file_exists(tmp);

    if (!dir_exist)
    {
        if (!CreateDirectory((LPCTSTR)tmp, NULL))
            return TTN_NOT_OK;
    }

    // get server name
    str = ql_get_server_name();
    
    wsprintf(tmp, "%s\\save\\%s", game_path, str);

    dir_exist = ql_file_exists(tmp);

    if (!dir_exist)
    {
        if (!CreateDirectory((LPCTSTR)tmp, NULL))
            return TTN_NOT_OK;
    }

    return TTN_OK;
}


LONG ql_encode(char *buf, LONG size, DWORD key)
{
    LONG new_key = 0;
    
    while (size--)
    {
        buf[size] = buf[size]^((char)key&0xFF);
        ((char*)&new_key)[0] = buf[size];
        if (!(size--))
            break;
        buf[size] = buf[size]^((char)(key>>8)&0xFF);
        ((char*)&new_key)[1] = buf[size];
        if (!(size--))
            break;
        buf[size] = buf[size]^((char)(key>>16)&0xFF);
        ((char*)&new_key)[2] = buf[size];
        if (!(size--))
            break;
        buf[size] = buf[size]^((char)(key>>24)&0xFF);
        ((char*)&new_key)[3] = buf[size];

        // store new key for next 4 bytes encode
        key = new_key;
    }
    return TTN_OK;
}


LONG ql_decode(char *buf, LONG size, DWORD key)
{
    LONG new_key = key;
    
    while (size--)
    {
        ((char*)&new_key)[0] = buf[size];
        buf[size] = buf[size]^((char)key&0xFF);
        if (!(size--))
            break;
        ((char*)&new_key)[1] = buf[size];
        buf[size] = buf[size]^((char)(key>>8)&0xFF);
        if (!(size--))
            break;
        ((char*)&new_key)[2] = buf[size];
        buf[size] = buf[size]^((char)(key>>16)&0xFF);
        if (!(size--))
            break;
        ((char*)&new_key)[3] = buf[size];
        buf[size] = buf[size]^((char)(key>>24)&0xFF);

        // store new key for next 4 bytes decode
        key = new_key;
    }
    return TTN_OK;
}

DWORD ql_check_code(char *buf, LONG size)
{
    DWORD check_code = 0;
    
    if (size < 0 || size > QL_MAX_BLOCK_SIZE)
        return -1;

    while (size--)
    {
        check_code += buf[size];
    }

    return check_code;
}

char *ql_get_server_name(VOID)
{

    // In UI.cpp
    extern CHAR world_name[64];

    return world_name;
}

BOOL  ql_read_block( FILE* fp, DWORD key, DWORD offset, QL_BLOCK* p_block)
{
    DWORD size;
    fseek( fp, offset, SEEK_SET );
    fread( &size, 1, sizeof( size ), fp );
    if ( size == 0 || size > sizeof( QL_BLOCK ) )
        return FALSE;

    fread( p_block, 1, size, fp );

    ql_decode( (CHAR*)p_block, size, key );

    if ( p_block->check_code != 
         ql_check_code( (CHAR*)p_block + sizeof( p_block->check_code ), 
                        size - sizeof( p_block->check_code ) ) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  ql_write_block( FILE* fp, DWORD key, DWORD next_offset, CHAR *name, CHAR *text )
{
    QL_BLOCK block;
    DWORD size;
    time_t ltime;

    if ( !fp || !text )
        return FALSE;

    time( &ltime );
    block.time = ltime;
    block.next_offset = next_offset;
    if ( name )
        lstrcpyn( block.name, name, QL_NAME_TEXT_SIZE );
    else
        memset( block.name, (INT)key, QL_NAME_TEXT_SIZE );
    lstrcpyn( block.text_buf, text, QL_MAX_TEXT_SIZE );

    size = sizeof( QL_BLOCK ) - QL_MAX_TEXT_SIZE;
    size += strlen( block.text_buf ) + 1;

    block.check_code = ql_check_code( (CHAR*)&block + sizeof( block.check_code ),
                                        size - sizeof( block.check_code ) );

    // encode block
    ql_encode( (CHAR*)&block, size, key );

    fwrite( &size, 1, sizeof(size), fp );
    fwrite( &block, 1, size, fp );

    return TRUE;
}


VOID ql_check_filename(VOID)
{
    if ( msg_file[0] == '\0' || 
         chat_file[0] == '\0' || chat_index_file[0] == '\0'    )
        ql_make_filename( ); 
}

LONG ql_clear_filename(VOID)
{
    msg_file [0] = '\0';
    chat_file[0] = '\0';
    
    chat_index_file[0] = '\0';
    
    return TTN_OK;
}

BOOL ql_move_file_ex( char *src_file, char *des_file)
{
    if ( src_file && des_file )
        if ( ql_file_exists( des_file ) )
            if ( DeleteFile( des_file ) )
                if ( ql_file_exists( src_file ) )
                    return MoveFile( src_file, des_file );

    return FALSE;
}

VOID  ql_close_all_file( VOID )
{
    if ( lchat.fp )
    {
        fclose( lchat.fp );
        lchat.fp = NULL;
    }
    if ( lmsg.fp )
    {
        fclose( lmsg.fp );
        lmsg.fp = NULL;
    }
}

BOOL  ql_check_file( VOID *header, LONG filetype )
{
    LPSTR str_sign1;
    LPSTR str_sign2;
    LPSTR filename;

    DWORD ver1, ver2;

    ver2 = QL_VERSION;

    switch( filetype )
    {
    case MSG_FILE:
        str_sign1 = (( LP_QLM_HEADER )header )->sign;
        ver1      = (( LP_QLM_HEADER )header )->version;
        str_sign2 = (CHAR*)MSG_FILE_SIGN;
        filename  = msg_file;
        break;
    case CHAT_FILE:
        str_sign1 = (( LP_QLC_HEADER )header )->sign;
        ver1      = (( LP_QLC_HEADER )header )->version;
        str_sign2 = (CHAR*)CHAT_FILE_SIGN;
        filename  = chat_file;
        break;
    case CHAT_INDEX_FILE:
        str_sign1 = (( LP_QLCI_HEADER )header )->sign;
        ver1      = (( LP_QLCI_HEADER)header )->version;
        str_sign2 = (CHAR*)CHAT_INDEX_FILE_SIGN;
        filename  = chat_index_file;
        break;
    default:
        return FALSE;
    }

    if ( strcmp( str_sign1, str_sign2 ) != 0 )
    {
        log_error( 1, "Error: The sign of %s is not correct!", filename );
        return FALSE;
    }

    if ( ver1 > ver2 )
    {
        log_error( 1, "Error: Error version of file %s", filename );
        return FALSE;
    }

    return TRUE;
}

inline DWORD ql_make_org_key( DWORD a )
{
    return ((((DWORD)a&0xff)<<16) |
            (((DWORD)a&0xff00)<<16) |
             ((DWORD)a&0xff) |
            (((DWORD)a&0xff00)));
}

inline DWORD ql_get_key( WORD a, WORD b )
{
    return ((((DWORD)a<<16)&0xff000000) |
            (((DWORD)a<<8)&0xff00) |
            (((DWORD)b<<8)&0xff0000) |
            (((DWORD)b)&0xff));
}

inline WORD ql_set_key1( DWORD org_key )
{
    return (WORD)(((org_key&0xff000000)>>16)|
                 ((org_key&0xff00)>>8));;
}

inline WORD ql_set_key2( DWORD org_key )
{
    return (WORD)(((org_key&0xff0000)>>8)|
                  ((org_key&0xff)));
}

