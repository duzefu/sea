/*
**      NetGE_Script.CPP
**      Script file functions.
**
**      Jack, 2003.1.19.
*/
#include "NetGE_MainFunc.h"


#define   MC_DEBUG

//DEFINES -------------------------------------------------------------------------------------------------
#define MAC_PROC_STACKS     32      /* depth of macro proc stack    */

#define MAC_INIT            0x01    /* mac system is init ok        */
#define MAC_LOAD            0x02    /* have load mac file           */
#define MAC_FILENAME        0x04    /* have stored mac filename     */


//GLOBALS -------------------------------------------------------------------------------------------------

//STATICS VARIABLES ---------------------------------------------------------------------------------------
static  MAC_INFO    * pmac_info = NULL ;                    /* macro information    */
static  MAC_HEAD    * pmac_head = NULL ;                    /* macro file head      */
static  USTR        * pmac_buffer = NULL ;                  /* macro code buffer    */
static  SLONG       mac_info_size = 0;                      /* size of macro info   */
static  SLONG       mac_head_size = 0;                      /* size of macro head   */
static  SCRIPT_DECODE_FUNC   fn_mac_decode = NULL;           /* user decode macro function pointer   */
static  SCRIPT_DEBUG_FUNC    fn_mac_debug = NULL;            /* user debug macro function pointer    */
static  SCRIPT_INSET_FUNC    fn_mac_inset = NULL;            /* user inset macro function pointer    */
static  SLONG       process_index = 0;                      /* now process index    */
static  SLONG       mac_proc_stack[MAC_PROC_STACKS];        /* process stack for CALL...    */
static  SLONG       mac_proc_stack_pointer = 0 ;            /* process stack pointer        */
static  SLONG       mac_flag = 0;                           /* macro system flag    */
static  USTR        mac_print_rec[1024];                    /* macro system print record */

//STATICS FUNCTION PROTOTYPE ------------------------------------------------------------------------------
static  SLONG       judge_conditional_expression(SLONG num1,UCHR oper,SLONG num2);
static  SLONG       get_script_long(void);
static  void        fn_dummy_mac_debug(USTR *info);
static  SLONG       fn_dummy_mac_decode(UCHR code);
static  void        fn_dummy_mac_inset(void);




//FUNCTIONS ===============================================================================================
int     init_script(void)
{
    // Mark this line so we can reinit mac system
    //  if(mac_flag & MAC_INIT) return(TTN_OK);
    
    if(pmac_info) { GlobalFree(pmac_info); pmac_info = NULL; }

    mac_info_size = sizeof(MAC_INFO)+(MAX_VAR-1)*sizeof(SLONG);
    pmac_info = (MAC_INFO *)GlobalAlloc(GPTR, mac_info_size);
    if(NULL == pmac_info)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
        log_error(1, mac_print_rec);
        goto error;
    }
    memset(pmac_info,0x00,mac_info_size);
    strcpy((char *)pmac_info->filename,"NONAME");
    pmac_info->code_size = 0;
    pmac_info->code_index = 0;
    pmac_info->max_var = MAX_VAR;
    memset((char *)pmac_info->variable,0x00,MAX_VAR*sizeof(SLONG));

    if(pmac_buffer) { GlobalFree(pmac_buffer); pmac_buffer=NULL; }
    fn_mac_decode = fn_dummy_mac_decode;
    fn_mac_debug = fn_dummy_mac_debug;
    fn_mac_inset = fn_dummy_mac_inset;

    mac_flag |= MAC_INIT;

    sprintf((char *)mac_print_rec,"******** INIT MACRO OK !");
    log_error(1,mac_print_rec);
    return 0;

error:
    if(pmac_info) { GlobalFree(pmac_info); pmac_info=NULL; }
    mac_info_size=0;

    mac_flag = 0;
    return(-1);
}



void    active_script(int active)
{
    if(active)
    {
    }
}


void    reset_script(void)
{
    if( mac_flag & MAC_INIT )
    {
        if(pmac_buffer)
        {
            pmac_info->code_size = 0;
            pmac_info->code_index = 0;
            pmac_info->max_var = MAX_VAR;
            memset((char *)pmac_info->variable, 0x00, MAX_VAR*sizeof(SLONG));
        }
    }
}



void    free_script(void)
{
    if(pmac_buffer) { GlobalFree(pmac_buffer); pmac_buffer=NULL; }
    if(pmac_head) { GlobalFree(pmac_head); pmac_head=NULL; }
    if(pmac_info) { GlobalFree(pmac_info); pmac_info=NULL; }
    mac_head_size=0; 
    mac_info_size=0; 
    mac_flag = 0;

    sprintf((char *)mac_print_rec,"******** FREE MACRO OK !");
    log_error(1,mac_print_rec);
}




SLONG   load_script(USTR *filename)
{
    PACK_FILE   *fp=NULL;
    USTR    path_filename[_MAX_PATH+_MAX_FNAME];
    
    //
    // if mac system have not been initialized ...
    //
    if(!(mac_flag & MAC_INIT))
    {
        sprintf((char *)mac_print_rec,"ERROR : mac system have not been initialized !");
        log_error(1, mac_print_rec);
        goto error;
    }
    
    sprintf((char *)path_filename,"%s\\%s",SCRIPT_PATH,filename);
    fp = pack_fopen((const char *)path_filename,"rb");
    if(fp==NULL)
    {
        sprintf((char *)mac_print_rec,"ERROR : error open file %s(load_script)",filename);
        log_error(1, mac_print_rec);
        goto error;
    }
    
    //
    // get mac file head and compute it's size
    //
    if(pmac_head) {GlobalFree(pmac_head); pmac_head=NULL; }
    pmac_head = (MAC_HEAD *)GlobalAlloc(GPTR, sizeof(*pmac_head));
    if(NULL == pmac_head)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
        log_error(1, mac_print_rec);
        goto error;
    }
    pack_fseek(fp,0,SEEK_SET);
    pack_fread(pmac_head,sizeof(*pmac_head),1,fp);
    mac_head_size = sizeof(*pmac_head)+(pmac_head->max_proc-1)*sizeof(SLONG);
    
    //
    // read mac head to pmac_head
    //
    if(pmac_head) { GlobalFree(pmac_head); pmac_head=NULL;}
    pmac_head = (MAC_HEAD *)GlobalAlloc(GPTR, mac_head_size);
    if(NULL == pmac_head)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error(load_script)");
        log_error(1, mac_print_rec);
        goto error;
    }
    memset(pmac_head,0,mac_head_size);
    pack_fseek(fp,0,SEEK_SET);
    pack_fread(pmac_head,1,mac_head_size,fp);
    
    //
    // read mac data to pmac_buffer
    //
    if(pmac_buffer){GlobalFree(pmac_buffer);pmac_buffer=NULL;}
    pmac_buffer = (USTR *)GlobalAlloc(GPTR, pmac_head->data_size);
    if(NULL == pmac_buffer)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error(load_script)");
        log_error(1, mac_print_rec);
        goto error;
    }
    memset(pmac_buffer,0,pmac_head->data_size);
    pack_fread(pmac_buffer,1,pmac_head->data_size,fp);
    if(fp) pack_fclose(fp);
    
    //
    // update pmac_info datas
    //
    if(NULL == pmac_info)
    {
        sprintf((char *)mac_print_rec,"ERROR : pmac_info is null");
        log_error(1, mac_print_rec);
        goto error;
    }
    pmac_info->code_size = pmac_head->data_size;
    pmac_info->code_index = 0;
    strcpy((char *)pmac_info->filename,(const char *)filename);
    
    mac_flag |= (MAC_LOAD|MAC_FILENAME);

    sprintf((char *)mac_print_rec,"LOAD MAC %s(%d) OK!",pmac_info->filename,pmac_info->code_size);
    log_error(1,(USTR *)mac_print_rec);
    
    return(0);
    
error:
    if(pmac_head){ GlobalFree(pmac_head); pmac_head=NULL; }
    if(pmac_buffer) { GlobalFree(pmac_buffer); pmac_buffer=NULL; }
    mac_info_size = 0;
    mac_head_size = 0;
    
    mac_flag &= ~MAC_LOAD;
    return(-1);
}


SLONG   reload_script(void)
{
    PACK_FILE   *fp=NULL;
    SLONG   mac_head_size;
    USTR    path_filename[_MAX_PATH+_MAX_FNAME];
    
    //
    // check if mac system initialized...
    //
    if(!(mac_flag & MAC_INIT))
    {
        sprintf((char *)mac_print_rec,"ERROR : mac system have not been initialized !");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    
    //
    // check if we have mac filename information...
    //
    if(!(mac_flag & MAC_FILENAME))
    {
        sprintf((char *)mac_print_rec,"ERROR : mac filename lost !");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    
    //
    // start to open mac file ...
    //
    sprintf((char *)path_filename,"%s\\%s",SCRIPT_PATH,(const char *)pmac_info->filename);
    fp = pack_fopen((const char *)path_filename,"rb");
    if(NULL==fp)
    {
        sprintf((char *)mac_print_rec,"ERROR : error open file %s",pmac_info->filename);
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    
    //
    // if file is opened successfully...
    //
    mac_flag &= ~MAC_LOAD;
    
    // first we must get mac_head_size
    if(pmac_head) { GlobalFree(pmac_head); pmac_head=NULL;}
    pmac_head = (MAC_HEAD *)GlobalAlloc(GPTR, sizeof(*pmac_head));
    if(NULL == pmac_head)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    memset(pmac_head,0,sizeof(*pmac_head));
    pack_fseek(fp,0,SEEK_SET);
    pack_fread(pmac_head,1,sizeof(*pmac_head),fp);
    mac_head_size = sizeof(*pmac_head)+(pmac_head->max_proc-1)*sizeof(SLONG);
    
    // realloc memory for pmac_head and reread mac_head
    if(pmac_head) { GlobalFree(pmac_head); pmac_head=NULL; }
    pmac_head = (MAC_HEAD *)GlobalAlloc(GPTR, mac_head_size);
    if(NULL == pmac_head)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    memset(pmac_head,0,mac_head_size);
    pack_fseek(fp,0,SEEK_SET);
    pack_fread(pmac_head,1,mac_head_size,fp);
    
    // read mac data to mac_buffer
    if(pmac_buffer) {GlobalFree(pmac_buffer); pmac_buffer=NULL; }
    pmac_buffer = (USTR *)GlobalAlloc(GPTR, pmac_head->data_size);
    if(NULL==pmac_buffer)
    {
        sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    memset(pmac_buffer,0,pmac_head->data_size);
    pack_fread(pmac_buffer,1,pmac_head->data_size,fp);
    if(fp) pack_fclose(fp);
    
    //
    // update mac information ...
    //
    if(NULL == pmac_info)
    {
        sprintf((char *)mac_print_rec,"ERROR : pmac_info is null");
        log_error(1,(USTR *)mac_print_rec);
        goto error;
    }
    pmac_info->code_size = pmac_head->data_size;
    pmac_info->code_index = 0;
    
    mac_flag |= MAC_LOAD;
    sprintf((char *)mac_print_rec,"LOAD MAC %s(%d) OK!",pmac_info->filename,pmac_info->code_size);
    log_error(1,(USTR *)mac_print_rec);
    return(0);

error:
    if(pmac_head) { GlobalFree(pmac_head); pmac_head=NULL; }
    if(pmac_buffer) { GlobalFree(pmac_buffer); pmac_buffer=NULL; }
    mac_head_size = 0;

    mac_flag &= ~MAC_LOAD;
    return(-1);
}



SLONG   process_script(SLONG proc_no)
{
    SLONG   pass;
    SLONG   skip;
    SLONG   num,num1,num2,num3,num4,num5;
    SLONG   else_index;
    SLONG   goto_index;
    UCHR    oper;
    SLONG   ret;
    USTR    str[256];
    SLONG   show_debug;
    UCHR    command_code;
    
    if(!(mac_flag & MAC_INIT)) return(GAME_CONTINUE);
    if(!(mac_flag & MAC_LOAD)) return(GAME_CONTINUE);
    if((NULL == pmac_head) || (NULL == pmac_info) || (NULL==pmac_buffer)) return(GAME_CONTINUE);
    if(proc_no<0||proc_no>(SLONG)(pmac_head->max_proc-1)) return(GAME_CONTINUE);
    
    num=0;
    num1=num2=num3=num4=num5=0;
    memset(str,0x00,255);
    memset(mac_print_rec,0x00,255);
    if(pmac_head->proc_address[proc_no]<0)
    {
        sprintf((char *)mac_print_rec,"WARN: proc address invalid.");
        log_error(1,(USTR *)mac_print_rec);
        return(GAME_CONTINUE);
    }
    pmac_info->code_index=pmac_head->proc_address[proc_no];
    process_index=pmac_info->code_index;
    mac_proc_stack_pointer=0;
    pass=0;
    ret=GAME_CONTINUE;
    while(pass==0)
    {
        //idle_loop();

        //Here we execute inset function.
        if( fn_mac_inset) 
            fn_mac_inset();

        show_debug=1;
        command_code=pmac_buffer[pmac_info->code_index++];
        skip=(SLONG)pmac_buffer[pmac_info->code_index++];
        process_index=pmac_info->code_index;
        pmac_info->code_index=pmac_info->code_index+skip;
        
        switch(command_code)
        {
            // SYSTEM COMMAND ===============================================================================
        case CMD_PROC:
            num = get_script_number();
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"    PROC    %d",num);
#endif//MC_DEBUG
            break;

        case CMD_ENDPROC:
            if(mac_proc_stack_pointer>0)
            {
                mac_proc_stack_pointer--;
                pmac_info->code_index=mac_proc_stack[mac_proc_stack_pointer];
            }
            else
            {
                pass=1;
            }
#ifdef  MC_DEBUG
            strcpy((char *)mac_print_rec,"    ENDPROC");
#endif//MC_DEBUG
            break;

        case CMD_IF:
            else_index = get_script_long();
            num = get_script_number();
            oper = get_script_char();
            num2 = get_script_number();
            num1=0;
            if((num>=0) && (num<MAX_VAR) )
                num1=pmac_info->variable[num];
            if(judge_conditional_expression(num1,oper,num2) != TRUE)
                pmac_info->code_index = else_index;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        IF [%d] %d(%d) %c %d",else_index,num,num1,oper,num2);
#endif//MC_DEBUG
            break;

        case CMD_GOTO:
            goto_index = get_script_long();
            pmac_info->code_index=goto_index;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        GOTO [%d]",goto_index);
#endif//MC_DEBUG
            break;

        case CMD_CALL:
            num = get_script_number();
            if((num<0)|| (num>(SLONG)(pmac_head->max_proc-1)))
            {
                sprintf((char *)mac_print_rec,"MAC call proc no out of range");
                log_error(1,mac_print_rec);
            }
            else
            {
                if(mac_proc_stack_pointer < MAC_PROC_STACKS)
                {
                    mac_proc_stack[mac_proc_stack_pointer]=pmac_info->code_index;
                    mac_proc_stack_pointer++;
                    pmac_info->code_index=pmac_head->proc_address[num];
                }
                else
                {
                    sprintf((char *)mac_print_rec,"MAC stack overflow");
                    log_error(1,mac_print_rec);
                }
            }
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        CALL {%d}",num);
#endif//MC_DEBUG
            break;

        case CMD_RETURN:
            if(mac_proc_stack_pointer>0)
            {
                mac_proc_stack_pointer--;
                pmac_info->code_index=mac_proc_stack[mac_proc_stack_pointer];
            }
            else
                pass=1;
#ifdef  MC_DEBUG
            strcpy((char *)mac_print_rec,"        RETURN");
#endif//MC_DEBUG
            break;

        case CMD_VAR:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num< MAX_VAR) )
                pmac_info->variable[num]=num2;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        VAR %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_ADD:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num<MAX_VAR) )
                pmac_info->variable[num]=pmac_info->variable[num]+num2;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        ADD %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_SUB:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num<MAX_VAR) )
                pmac_info->variable[num]=pmac_info->variable[num]-num2;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        SUB %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_MUL:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num<MAX_VAR) )
                pmac_info->variable[num]=pmac_info->variable[num]*num2;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        MUL %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_DEV:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num<MAX_VAR) )
            {
                if(num2)
                    pmac_info->variable[num]=pmac_info->variable[num]/num2;
            }
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        DEV %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_RAND:
            num = get_script_number();
            num2 = get_script_number();
            if( (num>=0) && (num<MAX_VAR) )
            {
                if(num2 > 0 )
                {
                    //geaan, 2001.10.12. replace the rand() to system_rand().
                    pmac_info->variable[num] = system_rand() % num2;
                    //pmac_info->variable[num] = rand(0, num2);
                }
            }
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        RAND %d %d",num,num2);
#endif//MC_DEBUG
            break;

        case CMD_EXEC:
            strcpy( (char *)str,(const char *)get_script_string() );
            strcpy( (char *)pmac_info->filename, (const char *)str );
            ret=GAME_EXEC;
            pass=1;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"        EXEC %s",str);
#endif//MC_DEBUG
            break;

        case CMD_EXIT:
            ret=GAME_OVER;
            pass=1;
#ifdef  MC_DEBUG
            sprintf((char *)mac_print_rec,"    EXIT %s","");
#endif//MC_DEBUG
            break;

        case CMD_ELSE:
        case CMD_ELSEIF:
        case CMD_ENDIF:
        case CMD_WHILE:
        case CMD_ENDWHILE:
        case CMD_SWITCH:
        case CMD_CASE:
        case CMD_ENDCASE:
        case CMD_ENDSWITCH:
        case CMD_BREAK:
            break;

            // USER COMMAND NOW ============================================================================
        default:
            show_debug=0;
            ret = fn_mac_decode(command_code);
            if(ret!=GAME_CONTINUE)
                pass=1;
            break;
        }
#ifdef  MC_DEBUG
        if(show_debug)
            fn_mac_debug(mac_print_rec);
#endif//MC_DEBUG
    }
    pmac_info->code_index=process_index;
    return(ret);
}



void    set_script_decode_func( SCRIPT_DECODE_FUNC func)
{
    if(func) fn_mac_decode = func;
}


void    set_script_debug_func( SCRIPT_DEBUG_FUNC func)
{
    if(func) fn_mac_debug = func;
}


void    set_script_inset_func( SCRIPT_INSET_FUNC func)
{
    if(func) fn_mac_inset = func;
}


SLONG   get_script_info_size(void)
{
    return mac_info_size;
}


SLONG   get_script_head_size(void)
{
    return mac_head_size;
}



USTR *  export_script_filename(USTR *buffer)
{
    static  USTR    filename[80];
    
    if(pmac_info)
    {
        strcpy((char *)filename,(const char *)pmac_info->filename);
        strcpy((char *)buffer,(const char *)filename);
        return((USTR *)filename);
    }
    else
    {
        strcpy((char *)filename,"NONAME");
        return NULL;
    }
}



SLONG   export_script_info(MAC_INFO *mi)
{
    if(pmac_info)
    {
        memcpy(mi,pmac_info,sizeof(*pmac_info)+(MAX_VAR-1)*sizeof(SLONG));
        return(sizeof(*pmac_info)+(MAX_VAR-1)*sizeof(SLONG));
    }
    else
        return(0);
}



SLONG   inport_script_info(MAC_INFO *mi)
{
    if(mi)
    {
        if(pmac_info) { GlobalFree(pmac_info); pmac_info=NULL; }
        pmac_info = (MAC_INFO *)GlobalAlloc(GPTR, sizeof(*mi)+(MAX_VAR-1)*sizeof(SLONG));
        if(NULL == pmac_info)
        {
            sprintf((char *)mac_print_rec,"ERROR : memory alloc error");
            log_error(1,mac_print_rec);
            goto error;
        }
        memset(pmac_info,0,sizeof(*mi)+(MAX_VAR-1)*sizeof(SLONG));
        memcpy(pmac_info,mi,sizeof(*mi)+(MAX_VAR-1)*sizeof(SLONG));
        mac_flag |= MAC_FILENAME;

        return(sizeof(*mi)+(MAX_VAR-1)*sizeof(SLONG));
    }
    else
    {
        sprintf((char *)mac_print_rec,"ERROR : mac inport info is null");
        log_error(1,mac_print_rec);
        goto error;
    }

error:
    return(0);
}



SLONG   get_script_number(void)
{
    enum LEADCODES
    {   LEAD_VARIABLE   =   '@',
    LEAD_DIRECTNUMBER   =   '#'
    };
    SLONG ret;
    SLONG number;
    UCHR lead_code;

    ret = 0;

    lead_code = pmac_buffer[process_index];
    process_index += sizeof(UCHR);

    switch(lead_code)
    {
    case LEAD_VARIABLE:
        number = *(SLONG *)&pmac_buffer[process_index];
        process_index += sizeof(SLONG);

        if((number>=0)&&(number<MAX_VAR))
            ret = pmac_info->variable[number];
        break;
    case LEAD_DIRECTNUMBER:
        number = *(SLONG *)&pmac_buffer[process_index];
        process_index += sizeof(SLONG);

        ret=number;
        break;
    }
    return ( ret );
}



USTR *  get_script_string(void)
{
    static USTR temp[256];
    SLONG   len;
    
    len = pmac_buffer[process_index];
    process_index ++;

    memset(temp, 0x00, 256);
    if(len>253)     return(NULL);

    memcpy(temp, &pmac_buffer[process_index], len);
    process_index += len;

    return((USTR*)temp);
}




UCHR    get_script_char(void)
{
    UCHR char_value;
    
    char_value = pmac_buffer[process_index];
    process_index += 1;

    return(char_value);
}


SLONG   get_script_variable(SLONG index)
{
    if(pmac_info)
        return((SLONG)pmac_info->variable[index]);
    else
        return(0);
}


void    set_script_variable(SLONG index,SLONG value)
{
    if(pmac_info)
    {
        if((index>=0)&&(index<MAX_VAR))
            pmac_info->variable[index]=(SLONG)value;
    }
}


// S T A T I C    F U N C T I O N S ////////////////////////////////////////////////////////////////////////////////
static      SLONG   judge_conditional_expression(SLONG num1, UCHR oper, SLONG num2)
{
    static  UCHR    op[6]=
    {   0x3d,   // '=' --> op "=="
    0x3c,       // '<' --> op "<"
    0x3e,       // '>' --> op ">"
    0xf3,       // 'ó'  --> op "<="
    0xf2,       // 'ò'  --> op ">="
    0xf7        // '÷'  --> op "!="
    };
    SLONG ret;
    
    ret = FALSE;
    switch(oper)
    {
    case 0x3d:      if(num1 == num2)    ret=TRUE;       break;
    case 0x3c:      if(num1 <  num2)    ret=TRUE;       break;
    case 0x3e:      if(num1 >  num2)    ret=TRUE;       break;
    case 0xf3:      if(num1 <= num2)    ret=TRUE;       break;
    case 0xf2:      if(num1 >= num2)    ret=TRUE;       break;
    case 0xf7:      if(num1 != num2)    ret=TRUE;       break;
    }
    return(ret);
}


static  SLONG   get_script_long(void)
{
    SLONG   long_value;
    
    long_value = pmac_buffer[process_index] 
        + pmac_buffer[process_index + 1] * 0x100
        + pmac_buffer[process_index + 2] * 0x10000
        + pmac_buffer[process_index + 3] * 0x1000000;
    process_index += 4;

    return(long_value);
}


static      void    fn_dummy_mac_debug(USTR *info)
{
    log_error(1,(USTR *)info);
}


static      SLONG   fn_dummy_mac_decode(UCHR code)
{
    UCHR    my_code;
    my_code=code;
    return(GAME_OVER);
}

static  void        fn_dummy_mac_inset(void)
{
    return;
}

