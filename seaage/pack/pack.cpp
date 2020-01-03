/*
**  pack.cpp
**  pack file tool.
**
**  Jack, 2002.4.23.
**      Created.
**  Jack, 2002.6.25.
**      (1) Modified load_list_file_information(...) for long filename(include space) support in filelist.txt
**          fscanf() can only get a string without blank space, but fgets() can do.
**      (2) Added checking exist file & asking if overwrite when unpack file.
**      (3) Added checking exist file when pack file.
**
*/
#include "rays.h"
#include "xkiss.h"
#include "ybitio.h"
#include "ylzss.h"
#include "lzo.h"
#include "packfile.h"
#include <conio.h>


//-------------------------------------------------------------------------------------
#ifdef  _DEBUG
#pragma comment(lib, "2denginedbg.lib")
#else//!_DEBUG
#pragma comment(lib, "2dengine.lib")
#endif//_DEBUG

//dummy functions for use library "2dengine.lib" or "2denginedbg.lib".
void gameExit(void){}
int gameMain(void){return 0;}
int gameInit(void){return 0;}
int gameSet(void){return 0;}
//-------------------------------------------------------------------------------------

//DEFINES /////////////////////////////////////////////////////////////////////////////
#define TOOL_VERSION            "1.01"

#define IN_LEN		    (0x10000L)
#define OUT_LEN		    (IN_LEN + IN_LEN / 64 + 16 + 3)



//STRUCTURES //////////////////////////////////////////////////////////////////////////
typedef struct  tagFILENAME_ID
{
    char        filename[_MAX_FNAME];
    unsigned    id;
} FILENAME_ID, *LPFILENAME_ID;

/*
typedef struct  tagDATA_FILE_HEAD
{
    ULONG   copyright;      //pack file copyright, 'RAYS'
    ULONG   id;             //pack file id 'PAK '
    ULONG   version;        //pack file version
    ULONG   head_size;      //size of file head
    //
    SLONG   total_files;    //total files in this pack
} DATA_FILE_HEAD, *LPDATA_FILE_HEAD;


typedef struct  tagFILE_INFO
{
    ULONG   id;
    ULONG   offset;
    ULONG   len;
} FILE_INFO, *LPFILE_INFO;
*/



//GLOBALS /////////////////////////////////////////////////////////////////////////////
char    data_filename[_MAX_FNAME];
char    list_filename[_MAX_FNAME];
char    directory_name[_MAX_PATH];
//
FILENAME_ID   *filename_id = NULL;
ULONG   filename_id_total = 0;
//
UCHR    in_buffer[IN_LEN], out_buffer[OUT_LEN];


//FUNCTIONS ///////////////////////////////////////////////////////////////////////////
void    show_usage(void);
int     load_list_file_information(char *filename);
int     pack_data_file(char *filename);
int     unpack_data_file(char *filename);
int     unpack_one_file(char *filename);
void    free_file_information(void);
void    generate_directory_files_list(void);
void    init_data_file_head(DATA_FILE_HEAD *head);
int     directly_unpack_data_file(char *filename);
int     directly_unpack_one_file(char *pack_filename, char *filename);


//USAGE:
//PACK -p data_filename list_filename
//PACK -u data_filename list_filename
//PACK -x data_filename list_filename
//PACK -l directory_name list_filename


int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        show_usage();
        return  0;
    }
    if(argv[1][0] != '-')
    {
        show_usage();
        return  0;
    }
    if((argv[1][1] == 'p') || (argv[1][1] == 'P'))
    {
        //pack file.
        strcpy((char *)data_filename, (const char *)argv[2]);
        strcpy((char *)list_filename, (const char *)argv[3]);

        filename_id_total = load_list_file_information(list_filename);
        if(filename_id_total > 0)
        {
            pack_data_file(data_filename);
        }
        free_file_information();

        return  0;
    }
    else if((argv[1][1] == 'u') || (argv[1][1] == 'U'))
    {
        //unpack file.
        strcpy((char *)data_filename, (const char *)argv[2]);
        strcpy((char *)list_filename, (const char *)argv[3]);

        filename_id_total = load_list_file_information(list_filename);
        if(filename_id_total > 0)
        {
            unpack_data_file(data_filename);
        }
        free_file_information();

        return  0;
    }
    else if((argv[1][1] == 'x') || (argv[1][1] == 'X'))
    {
        //unpack file.
        strcpy((char *)data_filename, (const char *)argv[2]);
        strcpy((char *)list_filename, (const char *)argv[3]);

        filename_id_total = load_list_file_information(list_filename);
        if(filename_id_total > 0)
        {
            directly_unpack_data_file(data_filename);
        }
        free_file_information();

        return  0;
    }
    else if((argv[1][1] == 'l') || (argv[1][1] == 'L'))
    {
        strcpy((char *)directory_name, (const char *)argv[2]);
        strcpy((char *)list_filename, (const char *)argv[3]);

        generate_directory_files_list();
    }
    else
    {
        show_usage();
        return  0;
    }

    return  0;
}


void    show_usage(void)
{
    char    *usage[] = 
    {   "Usage :\n",
    "    PACK -p data_filename list_filename\n",
    "        create a packed data file from the files list.\n",
    "    PACK -u data_filename list_filename\n",
    "        unpack a data file by the list.\n",
    "\n",
    NULL,
    };
    int i;

    printf("Pack file(s) tool, version %s\n", TOOL_VERSION);
    printf("Jack created, 2002.4.24.\n");
    printf("Last build : %s, %s\n", __DATE__, __TIME__);
    printf("\n");
    //
    for(i=0; usage[i]; i++)
    {
        printf(usage[i]);
    }
    return;
}



int load_list_file_information(char *filename)
{
    FILENAME_ID   tmp;
    FILE*   fp = NULL;
    int total_files, i, j, file_index;
    int same_id_exist, len;

    //(1) open list file.
    total_files = 0;
    if(NULL == (fp = fopen((const char *)filename, "r")))
    {
        printf("can't open file %s\n", filename);
        return  total_files;
    }

    //(2) count total file informations in list file.
	while (!feof(fp)) 
    {
        memset((char *)tmp.filename, 0x00, _MAX_FNAME);
        fgets((char *)tmp.filename, _MAX_FNAME, fp);
        len = strlen((const char *)tmp.filename);
        for(i=0; i<len; i++)
        {
            if(tmp.filename[i] == 0x0d || tmp.filename[i] == 0x0a)
            {
                tmp.filename[i] = 0x00;
            }
        }
        if(tmp.filename[0] != 0x00)
        {
#ifdef  _DEBUG
            //printf("filename : %s\n", tmp.filename);
            //getch();
#endif//_DEBUG
            ++total_files;
        }
	}

	fseek(fp, 0, SEEK_SET);
	filename_id = (FILENAME_ID *)malloc(sizeof(FILENAME_ID) * total_files);
    file_index = 0;
	while (!feof(fp)) 
    {
        memset((char *)tmp.filename, 0x00, _MAX_FNAME);
        fgets((char *)tmp.filename, _MAX_FNAME, fp);
        len = strlen((const char *)tmp.filename);
        for(i=0; i<len; i++)
        {
            if(tmp.filename[i] == 0x0d || tmp.filename[i] == 0x0a)
            {
                tmp.filename[i] = 0x00;
            }
        }
        if(tmp.filename[0] != 0x00)
        {
            strcpy((char *)filename_id[file_index].filename, (const char *)tmp.filename);
            strlwr((char *)filename_id[file_index].filename);
            filename_id[file_index].id = filename_to_id((USTR*)filename_id[file_index].filename);
            ++file_index;
        }
	}
	if(fp) fclose(fp);

    same_id_exist = 0;
	for (i=0;i<total_files-1;i++)
    {
		for (j=i+1;j<total_files; j++)
        {
            if (filename_id[i].id > filename_id[j].id)
            {
                memcpy(&tmp, filename_id + i, sizeof(tmp));
                memcpy(filename_id+i, filename_id+j, sizeof(tmp));
                memcpy(filename_id+j, &tmp, sizeof(tmp));
            }
            else if (filename_id[i].id == filename_id[j].id)
            {
                printf("warning : %s & %s has the same ID\n",filename_id[i].filename,filename_id[j].filename);
                same_id_exist ++;
            }
        }
    }

    if(same_id_exist > 0)
    {
        printf("error : found %d same ids, system exit.\n", same_id_exist);
        exit(1);
    }

#ifdef  _DEBUG
    /*
    printf("debug print file information\n");
    for(i=0; i<total_files; i++)
    {
        printf("%-8d, id = 0x%08x, %s\n", i, filename_id[i].id, filename_id[i].filename);
    }
    */
#endif//_DEBUG


    filename_id_total = total_files;

    return  total_files;
}



void    free_file_information(void)
{
    if(filename_id)
        free(filename_id);
    filename_id = NULL;
    filename_id_total = 0;
}


int pack_data_file(char *filename)
{
    DATA_FILE_HEAD  head;
    FILE_INFO *file_info = NULL;
    FILE    *data_fp = NULL;
    ULONG   i, j, file_info_offset, data_offset;
    int input_key, input_pass, overwrite;

    //(0) check if pack file exist ? -----------------------------------
    if(NULL != (data_fp = fopen((const char *)filename, "rb")))
    {
        printf("file %s exist, overwrite it(y/n)?", filename);
        input_pass = 0;
        overwrite = 0;
        while(input_pass == 0)
        {
            input_key = getch();
            if(input_key == 'Y' || input_key == 'y')
            {
                overwrite = 1;
                input_pass = 1;
            }
            else if(input_key == 'N' || input_key == 'n')
            {
                overwrite = 0;
                input_pass = 1;
            }
        }
        printf("%c\n", input_key);
        if(overwrite == 0)
        {
            if(data_fp) fclose(data_fp);

            printf("skip pack file %s ok.\n", filename);
            return  0;
        }
        else
        {
            if(data_fp) fclose(data_fp);
            remove((const char *)filename);
        }
    }


    //(1) open pack file. ----------------------------------------------
    if(NULL == (data_fp = fopen((const char *)filename, "wb")))
    {
        printf("file %s open error\n", filename);
        goto some_error;
    }

    //(2) write pak file head.------------------------------------------
    init_data_file_head(&head);
    head.total_files = filename_id_total;
    fwrite(&head, 1, sizeof(head), data_fp);

    //(3) write block file info. ---------------------------------------
    file_info_offset = ftell(data_fp);
    if(NULL == (file_info = (FILE_INFO *)malloc(sizeof(FILE_INFO) * filename_id_total)))
    {
        printf("memory alloc error\n");
        goto some_error;
    }
    for(i=0; i<filename_id_total; i++)
    {
        file_info[i].id = filename_id[i].id;
        file_info[i].offset = file_info_offset;
        file_info[i].len = 0;
    }
    fwrite(file_info, 1, sizeof(FILE_INFO) * filename_id_total, data_fp);

    //(4) write each file.
    data_offset = ftell(data_fp);
    for(i=0; i<filename_id_total; i++)
    {
        FILE    *fp = NULL;
        UHINT   *block_size = NULL;
        SLONG   n, size, len;

        fp = fopen((const char *)filename_id[i].filename, "rb");
        if(NULL == fp)
        {
            printf("file %s open error\n", filename_id[i].filename);
            goto some_error;
        }
        fseek(fp, 0, SEEK_END);
        size = file_info[i].len = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fseek(data_fp, data_offset, SEEK_SET);
        file_info[i].offset = data_offset;

        n = (size + 0xffff) >> 16;
        block_size = (UHINT*)malloc(sizeof(UHINT) * n);

        //write block sizes.
        fwrite(block_size, 1, sizeof(UHINT) * n, data_fp);

        //write block data.
        for(j = 0; size >= IN_LEN; size -= IN_LEN, j++)
        {
            fread(in_buffer, 1, IN_LEN, fp);
            len = lzo_compress(in_buffer, IN_LEN, out_buffer);
            if(len >= IN_LEN)
            {
                block_size[j] = 0;
                fwrite(in_buffer, 1, IN_LEN, data_fp);
            }
            else
            {
                block_size[j] = (UHINT)len;
                fwrite(out_buffer, 1, len, data_fp);
            }
        }
        if(size > 0)
        {
            fread(in_buffer, 1, size, fp);
            len = lzo_compress(in_buffer, size, out_buffer);
            if(len >= IN_LEN)
            {
                block_size[j] = 0;
                fwrite(in_buffer, 1, IN_LEN, data_fp);
            }
            else
            {
                block_size[j] = (UHINT)len;
                fwrite(out_buffer, 1, len, data_fp);
            }
        }

        //rewrite block sizes.
        data_offset = ftell(data_fp);
        fseek(data_fp, file_info[i].offset, SEEK_SET);
        fwrite(block_size, 1, sizeof(UHINT) * n, data_fp);
        fseek(data_fp, data_offset, SEEK_SET);

		printf("(%10d -> %10d)<% 3.1f%%>[%08X] %s\n",
            file_info[i].len, data_offset - file_info[i].offset,
            ((float)data_offset-file_info[i].offset)/file_info[i].len*100, 
            filename_id[i].id, filename_id[i].filename);
        if(block_size) 
        {
            free(block_size);
            block_size = NULL;
        }
        if(fp) fclose(fp);
    }

    //(5) rewrite block file info. --------------------------------------
    fseek(data_fp, file_info_offset, SEEK_SET);
    fwrite(file_info, 1, sizeof(FILE_INFO) * filename_id_total, data_fp);

    //(6) finished.
    if(data_fp) fclose(data_fp);
    if(file_info) free(file_info);

    return  0;

some_error:
    if(data_fp) fclose(data_fp);
    if(file_info) free(file_info);
    return  -1;
}


int     directly_unpack_data_file(char *filename)
{
    USTR    block_filename[_MAX_FNAME];
    USTR*   path = NULL;
    ULONG   i;

    //(1) ready the directories.
    for(i = 0; i < filename_id_total; i ++)
    {
        path = get_file_path((USTR *)filename_id[i].filename);
        if(path)
        {
            if(! is_directory_exist((USTR*)path))
            {
                make_directory((USTR*)path);
            }
        }
    }

    //(2) unpack each file directly.
    for(i = 0; i < filename_id_total; i ++)
    {
        strcpy((char *)block_filename, filename_id[i].filename);
        if( 0 == directly_unpack_one_file((char *)filename, (char*)block_filename))
        {
            //printf("unpack file %s ok.\n", block_filename);
        }
    }
    return  0;
}


int unpack_data_file(char *filename)
{
    USTR    block_filename[_MAX_FNAME];
    USTR*   path = NULL;
    ULONG   i;


    //(1) ready the directories.
    for(i = 0; i < filename_id_total; i ++)
    {
        path = get_file_path((USTR *)filename_id[i].filename);
        if(path)
        {
            if(! is_directory_exist((USTR*)path))
            {
                make_directory((USTR*)path);
            }
        }
    }

    //(2) unpack each file.
    DATA_FILE   *data_file = NULL;

    data_file = open_data_file((char *)filename);
    for(i = 0; i < filename_id_total; i ++)
    {
        strcpy((char *)block_filename, filename_id[i].filename);
        if( 0 == unpack_one_file((char*)block_filename))
        {
            //printf("unpack file %s ok.\n", block_filename);
        }
    }
    close_data_file(data_file);

    return  0;
}


void    generate_directory_files_list(void)
{
    printf("generate directory files list:\n");
}


void    init_data_file_head(DATA_FILE_HEAD *head)
{
    head->copyright = PACK_FILE_COPYRIGHT;
    head->id = PACK_FILE_ID;
    head->version = PACK_FILE_VERSION;
    head->head_size = sizeof(DATA_FILE_HEAD);
    head->total_files = 0;
}


int unpack_one_file(char *filename)
{
    enum { CACHE_SIZE = 4096 };
    static  char    cache[CACHE_SIZE];
    PACK_FILE *f = NULL;
    SLONG   size, i, n;
    FILE *fp = NULL;
    int input_key, input_pass, overwrite;

    // check if file exist, if exist, ask overwrite it or not ? ----------------------
    if(NULL != (fp = fopen((const char *)filename, "rb")))
    {
        printf("file %s exist, overwrite it(y/n)?", filename);
        input_pass = 0;
        overwrite = 0;
        while(input_pass == 0)
        {
            input_key = getch();
            if(input_key == 'Y' || input_key == 'y')
            {
                overwrite = 1;
                input_pass = 1;
            }
            else if(input_key == 'N' || input_key == 'n')
            {
                overwrite = 0;
                input_pass = 1;
            }
        }
        printf("%c\n", input_key);
        if(overwrite == 0)
        {
            if(fp) fclose(fp);

            printf("skip file %s ok.\n", filename);
            return  0;
        }
        else
        {
            if(fp) fclose(fp);
            remove((const char *)filename);
        }
    }


    //if not exist the file or want to overwrite the exist file, unpack it. -----------------------
    f = pack_fopen((const char *)filename, "rb");
    if(NULL == f)
    {
        printf("unpack file %s error\n", filename);
        goto _error;
    }
    size = pack_fsize(f);
    n = size / CACHE_SIZE;

    if(NULL ==(fp = fopen((const char *)filename, "wb")))
    {
        printf("file %s open error\n", filename);
        goto _error;
    }

    for(i=0; i<n; i++)
    {
        pack_fread(cache, 1, CACHE_SIZE, f);
        size -= CACHE_SIZE;

        fwrite(cache, 1, CACHE_SIZE, fp);
    }

    if(size > 0)
    {
        pack_fread(cache, 1, size, f);

        fwrite(cache, 1, size, fp);
    }

    if(fp) fclose(fp);
    if(f) pack_fclose(f);

    printf("unpack file %s ok.\n", filename);
    return  0;

_error:
    if(fp) fclose(fp);
    if(f) pack_fclose(f);
    return  -1;
}



int directly_unpack_one_file(char *pack_filename, char *filename)
{
    FILE *pack_fp = NULL;
    FILE *orig_fp = NULL;
    DATA_FILE_HEAD  head;
    FILE_INFO   *file_info = NULL;
    SLONG   total_files, begin_index, end_index, middle_index;
    ULONG   id, sid;
    SLONG   offset, size, blocks, i, len;
    UHINT   *block_size = NULL;
    int input_key, input_pass, overwrite;

    // check if file exist, if exist, ask overwrite it or not ? ----------------------
    if(NULL != (orig_fp = fopen((const char *)filename, "rb")))
    {
        printf("file %s exist, overwrite it(y/n)?", filename);
        input_pass = 0;
        overwrite = 0;
        while(input_pass == 0)
        {
            input_key = getch();
            if(input_key == 'Y' || input_key == 'y')
            {
                overwrite = 1;
                input_pass = 1;
            }
            else if(input_key == 'N' || input_key == 'n')
            {
                overwrite = 0;
                input_pass = 1;
            }
        }
        printf("%c\n", input_key);
        if(overwrite == 0)
        {
            if(orig_fp) fclose(orig_fp);
            printf("skip file %s ok.\n", filename);
            return  0;
        }
        else
        {
            if(orig_fp) fclose(orig_fp);
            remove((const char *)filename);
        }
    }


    //if not exist the file or want to overwrite the exist file, unpack it. -----------------------
    if(NULL == (pack_fp = fopen((const char *)pack_filename, "rb")))
    {
        printf("pack file %s open error\n", pack_filename);
        goto _error;
    }
    if(NULL == (orig_fp = fopen((const char *)filename, "wb")))
    {
        printf("orig file %s open error\n", filename);
        goto _error;
    }
    fread(&head, 1, sizeof(head), pack_fp);
    total_files = head.total_files;

    file_info = (FILE_INFO *)malloc(sizeof(FILE_INFO) * total_files);
    fread(file_info, 1, sizeof(FILE_INFO) * total_files, pack_fp);

    id = filename_to_id((USTR*)filename);
    begin_index = 0;
    end_index = total_files - 1;
    while(begin_index <= end_index)
    {
        middle_index = (begin_index + end_index) / 2;
        sid = file_info[middle_index].id;
        if(id == sid)
            goto _found;
        else if(id < sid)
            end_index = middle_index - 1;
        else
            begin_index = middle_index + 1;
    }
    printf("can't find file %s in data file %s\n", filename, pack_filename);
    goto _error;

_found:
    offset = file_info[middle_index].offset;
    size = file_info[middle_index].len;
    blocks = (size + 0xffff) / 0x10000;
    block_size = (UHINT*)malloc(sizeof(UHINT) * blocks);
    fseek(pack_fp, offset, SEEK_SET);
    fread(block_size, 1, sizeof(UHINT)*blocks, pack_fp);
    for(i=0; i<blocks; i++)
    {
        if(block_size[i] == 0)
        {
            fread(in_buffer, 1, IN_LEN, pack_fp);
            fwrite(in_buffer, 1, IN_LEN, orig_fp);
        }
        else
        {
            fread(in_buffer, 1, block_size[i], pack_fp);
            len = lzo_decompress(in_buffer, block_size[i], out_buffer);
            fwrite(out_buffer, 1, len, orig_fp);
        }
    }

    if(pack_fp) fclose(pack_fp);
    if(orig_fp) fclose(orig_fp);
    if(file_info) free(file_info);
    if(block_size) free(block_size);

    printf("unpack file %s ok.\n", filename);
    return  0;

_error:
    if(pack_fp) fclose(pack_fp);
    if(orig_fp) fclose(orig_fp);
    if(file_info) free(file_info);
    if(block_size) free(block_size);

    return  -1;
}

