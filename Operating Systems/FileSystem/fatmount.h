#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 512
#define FATIMG "fat32.img"
#define DIRNAMELEN 8
#define DIRPATHLEN 11
#define NONDIR 0xE5
#define ISLONGDIR 15
#define NOTFOUND -1
#define WRITEONLY 1
#define READONLY 0
#define INVALID 999
#define RWMODE 2
#define ENTRY_LENGTH 12
/*globals*/
typedef struct {
    unsigned char BS_jmpBoot[3];
    char BS_OEMName[8];
    unsigned short BPB_BytesPerSec;
    unsigned char BPB_SecPerClus;
    unsigned short BPB_RsvdSecCnt;
    unsigned char BPB_NumFATs;
    unsigned short BPB_RootEntCnt;
    unsigned short BPB_TotSec16; 
    unsigned char BPB_Media;
    unsigned short BPB_FATSz16;
    unsigned short BPB_SecPerTrk;
    unsigned short BPB_NumHeads;
    unsigned int BPB_HiddSec;
    unsigned int BPB_TotSec32;
    
    unsigned int BPB_FATSz32;
    unsigned short BPB_ExtFlags;
    unsigned short BPB_FSVer;
    unsigned int BPB_RootClus;
    unsigned short BPB_FSInfo;
	unsigned short BPB_BkBootSec;
    char BPB_Reserved[12];
	char BS_DrvNum;
	char BS_Reserved1;
	char BS_BootSig;
	unsigned int BS_VolID;
	char BS_VolLab[11];
    char BS_FilSysType[8];
	char bootdata[420];
    unsigned short valid_signature;
} __attribute((packed)) BootSector; /*512 bytes*/

typedef struct {
	char DIR_Name[11];
	char DIR_Attr;
	char DIR_NTRes;
	char DIR_CrtTimeTenth;
	unsigned short DIR_CrtTime;
	unsigned short DIR_CrtDate;
	unsigned short DIR_LstAccDate;
	unsigned short DIR_FstClusHI;
	unsigned short DIR_WrtTime;
	unsigned short DIR_WrtDate;
	unsigned short DIR_FstClusLO;
	unsigned int DIR_FileSize;
} __attribute((packed)) DirEntry; /*32 bytes*/

typedef struct {
	unsigned int FSI_LeadSig;
	char FSI_Reserved1[480];
	unsigned int FSI_StrucSig;
	unsigned int FSI_Free_Count;
	unsigned int FSI_Nxt_Free;
	char FSI_Reserved2[12];
	unsigned int FSI_TrailSig;
} __attribute((packed)) FSInfo;

typedef struct {
	unsigned short mode;
	char file[MAXLENGTH];
	bool isActive;
} OpenFile;

/*utility declarations*/
void get_input();
void process_input();
void reset_inputs();

/*command declarations*/
void print_ls(DirEntry);
void print_size();
void change_directory(DirEntry);
void try_open_file(DirEntry, unsigned short);
void try_close_file();
void read_file();
void write_to_file();
void create_file(unsigned int,unsigned int);
void make_directory();
void try_remove_directory();
void remove_file();

const unsigned int EOC = 0x0FFFFFF8;
/*helper declarations*/
bool entry_found(DirEntry);
bool get_entry_name(DirEntry, char*);
void set_entries(unsigned int);
void print_name(DirEntry);
unsigned int read_FAT(unsigned int);
unsigned int get_FATOffset(unsigned int, unsigned int);
unsigned short get_mode(const char*);
void open_file(OpenFile);
int get_open_file(const char*);
void close_all();
int get_entry_size();
unsigned int get_next_cluster(DirEntry);
DirEntry get_directory_entry();
unsigned int get_cluster_offset(unsigned int);
int get_next_FAT();
void convert_entry(char*);
unsigned int get_new_direntry();
unsigned int get_next_free_FAT();
bool update_last_cluster();
