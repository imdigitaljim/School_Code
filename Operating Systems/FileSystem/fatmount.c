#include "fatmount.h"

BootSector bs;
FSInfo fs;
DirEntry* entries;
OpenFile ft[MAXLENGTH];

unsigned int CurrentCluster, DirEntryPerCluster, FirstDataSector, FATBYTES;
unsigned int currentDir = 0;
char input[MAXLENGTH];
char CWD[MAXLENGTH][MAXLENGTH];
char data[MAXLENGTH][MAXLENGTH];
int CWDCLUSTER[MAXLENGTH];

FILE* img;

/*point of entry*/
int main()
{
	int i;	
	img = fopen(FATIMG, "r+"); 
	if (img == NULL)
	{
		fprintf(stderr, "'%s' file was not found in this directory\n",FATIMG);
		exit(1);
	}
	fread(&bs, sizeof(BootSector), 1, img);
	fseek(img, bs.BPB_FSInfo * bs.BPB_BytesPerSec, SEEK_SET);
	fread(&fs, sizeof(FSInfo), 1, img);
	FATBYTES = (bs.BPB_FATSz32 * bs.BPB_BytesPerSec) / 4;
	CWDCLUSTER[0] = bs.BPB_RootClus;
	FirstDataSector = bs.BPB_RsvdSecCnt + (bs.BPB_NumFATs * bs.BPB_FATSz32); /*# of sectors used before first data sector*/		
	DirEntryPerCluster = (bs.BPB_BytesPerSec * bs.BPB_SecPerClus) / sizeof(DirEntry);
	entries = (DirEntry*)malloc(DirEntryPerCluster * sizeof(DirEntry));
	
	fs.FSI_Nxt_Free = get_next_free_FAT();
	fseek(img, bs.BPB_FSInfo * bs.BPB_BytesPerSec, SEEK_SET);
	fwrite(&fs, sizeof(FSInfo), 1, img);
	
	for (i = 0; i < MAXLENGTH; i++)
	{
		ft[i].mode = INVALID;
		ft[i].isActive = false;
		memset(ft[i].file, 0, MAXLENGTH);
	}
	while(1)
	{
		reset_inputs();	
		get_input();
		process_input();

	}
	free(entries);
	fclose(img);
	return 0;
}

void get_input()
{
	char *token;
	int i;
	printf("/");
	for (i = 0; i < currentDir; i++)
	{
		printf("%s/", CWD[i + 1]);
	}
	i = 0;
	printf("] ");
	scanf(" %[^\n]", input);
	token = strtok(input, " ");
	while (token != NULL)
	{
		strcpy(data[i], token);
		strcat(data[i++], "\0");
		if (strcmp(data[0], "write") == 0 && i > 3)
		{
			token = strtok(NULL, "\"");
			strcpy(data[4], token);
			strcat(data[4], "");
			return;
		}
		token = strtok(NULL, " ");
	}	

}

void reset_inputs()
{
	int i;
	memset(input, 0, MAXLENGTH);
	for (i = 0; i < MAXLENGTH; i++)
	{
		memset(data[i], 0, MAXLENGTH);	
	}
	set_entries(CWDCLUSTER[currentDir]);
	CurrentCluster = CWDCLUSTER[currentDir];
}


void process_input()
{
	if (strcmp(data[0], "open") == 0) 
	{
		unsigned short mode = get_mode(data[2]);
		if (mode > 2)
		{
			printf("Error: incorrect parameter\n");
		}
		else
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				printf("Error: file does not exist\n");
			}
			else if (e.DIR_Attr == 0x10)
			{
				printf("Error: cannot open a directory.\n");
			}
			else
			{
				try_open_file(e, mode);
			}
		}
	}
	else if (strcmp(data[0], "close") == 0) 
	{
		try_close_file();
	}
	else if (strcmp(data[0], "rm") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing parameter\n");
		}
		else if (strcmp(data[1],"..") == 0 || strcmp(data[1],".") == 0)
		{
			printf("Error: invalid file\n");
		}
		else
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				printf("Error: does not exist\n");
			}
			else if (e.DIR_Attr == 0x10)
			{
				printf("Error: cannot delete directory\n");
			}
			else
			{
				int file_index = get_open_file(data[1]);
				if (file_index > -1)
				{
					ft[file_index].isActive = false;
				}
				remove_file();
			}
		}
	}
	else if (strcmp(data[0], "create") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing parameter\n");
		}
		else if (data[1][0] == '.')
		{
			printf("Error: invalid name\n");
		}
		else if (strcmp(data[1],"..") == 0 || strcmp(data[1],".") == 0)
		{
			printf("Error: invalid file\n");
		}
		else
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				create_file(get_new_direntry(), get_next_FAT());
			}
			else
			{
				printf("Error: name already exists \n");
			}
		}
	}
	else if (strcmp(data[0], "size") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing filename\n");
		}
		else
		{
			print_size();
		}
	}
	else if (strcmp(data[0], "cd") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing parameter\n");
		}
		else if (strcmp(data[1],"..") == 0 && currentDir > 0)
		{
			currentDir--;
		}
		else if (strcmp(data[1],".") != 0 && strcmp(data[1],"..") != 0)
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				printf("Error: does not exist\n");
			}
			else if (e.DIR_Attr == 0x10)
			{
				change_directory(e);
			}
			else
			{
				printf("Error: not a directory. \n");	
			}
		}
	}
	else if (strcmp(data[0], "ls") == 0)
	{
		if (strlen(data[1]) == 0)
		{
			int i;
			while(CurrentCluster < EOC)
			{
				for (i = 0; i < DirEntryPerCluster; i++) 
				{
					print_name(entries[i]);
				}
				CurrentCluster = read_FAT(CurrentCluster);
				set_entries(CurrentCluster);
			}
			printf("\n");
		}
		else
		{
			DirEntry e = get_directory_entry();	
			if (e.DIR_Attr == 0x10)
			{
				print_ls(e);
			}
			else if (e.DIR_FileSize == NOTFOUND)
			{
				printf("Error: does not exist\n");
			}
			else 
			{
				printf("Error: invalid directory\n");
			}
		}
	}
	else if (strcmp(data[0], "mkdir") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing parameter\n");
		}
		else if (strcmp(data[1],"..") == 0 || strcmp(data[1],".") == 0)
		{
			printf("Error: invalid directory\n");
		}
		else
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				make_directory();
			}
			else 
			{
				printf("Error: name already exists \n");
			}
		}
	}
	else if (strcmp(data[0], "rmdir") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing parameter\n");
		}
		else if (strcmp(data[1],"..") == 0 || strcmp(data[1],".") == 0)
		{
			printf("Error: invalid directory\n");
		}
		else
		{
			DirEntry e = get_directory_entry();
			if (e.DIR_FileSize == NOTFOUND)
			{
				printf("Error: does not exist\n");
			}
			else if (e.DIR_FileSize > 0)
			{
				printf("Error: not a directory. \n");
			}
			else
			{
				try_remove_directory(e);	
			}
		}
	}
	else if (strcmp(data[0], "read") == 0) 
	{
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing filename\n");
			printf("Usage: read <FILE_NAME> <POSITION> <NUM_BYTES>\n");
		}
		else if (strlen(data[3]) == 0)
		{
			printf("Error: missing position/bytes count\n");
			printf("Usage: read <FILE_NAME> <POSITION> <NUM_BYTES>\n");
		} 
		else
		{
			int exist_index = get_open_file(data[1]), file_size = get_entry_size();
			int position = atoi(data[2]), stream_bytes = atoi(data[3]);
			if (position > file_size)
			{
				printf("Error: position too large\n");
			}
			else if (position + stream_bytes > file_size)
			{
				printf("Error: attempt to read beyond EoF\n");
			}
			else if (exist_index == NOTFOUND)
			{
				printf("Error: file not open\n");
			}
			else if (ft[exist_index].mode == WRITEONLY)
			{
				printf("Error: file is write-only\n");
			}
			else
			{
				read_file();
			}
		}
	}
	else if (strcmp(data[0], "write") == 0) 
	{
		int exist_index;
		if (strlen(data[1]) == 0)
		{
			printf("Error: missing filename\n");
			printf("Usage: write <FILE_NAME> <POSITION> <NUM_BYTES> <STRING>\n");
			return;
		}
		exist_index = get_open_file(data[1]);
		if (strlen(data[4]) == 0)
		{
			printf("Error: missing parameters\n");
			printf("Usage: write <FILE_NAME> <POSITION> <NUM_BYTES> <STRING>\n");
		}
		else if (exist_index == NOTFOUND)
		{
			printf("Error: file not open\n");
		}
		else if (ft[exist_index].mode == READONLY)
		{
			printf("Error: file is read-only\n");
		}
		else
		{	
			write_to_file();
		}
	}
	else if (strcmp(data[0], "exit") == 0)
	{
		free(entries);
		fclose(img);
		exit(0);
	}
	else
	{
		printf("%s: command not recognized\n", data[0]);
	}
}

void try_remove_directory()
{
	int i, j;
	char match[ENTRY_LENGTH];
	while (CurrentCluster < EOC)
	{
		for (i = 0; i < DirEntryPerCluster; i++)
		{
			if (get_entry_name(entries[i], match) && strcmp(match, data[1]) == 0)
			{
				unsigned dirClust = get_next_cluster(entries[i]);
				set_entries(dirClust);
				for (j = 0; j < DirEntryPerCluster; j++)
				{	
					if (!(entries[j].DIR_Name[0] == '\0' || entries[j].DIR_Name[0] == NONDIR))
					{
						if (strcmp(entries[j].DIR_Name, ".          ") != 0 
						&& strcmp(entries[j].DIR_Name, "..         ") != 0)
						{
							printf("Error: directory not empty\n");
							return;
						}
					}						
				}
				set_entries(CurrentCluster);
				remove_file();
				return;
			}
		}
	}
}

void remove_file()
{
	int i;
	char match[ENTRY_LENGTH];
	for (i = 0; i < DirEntryPerCluster; i++)
	{
		if (get_entry_name(entries[i], match) && strcmp(match, data[1]) == 0)
		{
			entries[i].DIR_Name[0] = 0;
			fseek(img, get_cluster_offset(CurrentCluster), SEEK_SET);
			fwrite(entries, sizeof(DirEntry) * DirEntryPerCluster, 1, img);
			CurrentCluster = get_next_cluster(entries[i]);
			break;
		}
	}
	while (update_last_cluster())
	{
		fs.FSI_Free_Count++;
	}
	fseek(img, get_FATOffset(CurrentCluster, 1), SEEK_SET);
	fwrite(&EOC, sizeof(unsigned int), 1, img);
	
	fs.FSI_Free_Count++;
	
	fseek(img, bs.BPB_FSInfo * bs.BPB_BytesPerSec, SEEK_SET);
	fwrite(&fs, sizeof(FSInfo), 1, img);
}

bool update_last_cluster()
{
	unsigned int prevCluster = CurrentCluster, lastCluster = read_FAT(CurrentCluster);
	while (lastCluster < EOC)
	{
		prevCluster = lastCluster;
		lastCluster = read_FAT(lastCluster);
	}
	fseek(img, get_FATOffset(prevCluster, 1), SEEK_SET);
	fwrite(&EOC, sizeof(unsigned int), 1, img);
	return CurrentCluster == lastCluster;
}

void write_to_file()
{
	DirEntry e = get_directory_entry(); 
	int i, stream_count = atoi(data[3]), read_count = 0;
	int file_position = atoi(data[2]), len = strlen(data[4]);
	unsigned int clusterBytes = (bs.BPB_BytesPerSec * bs.BPB_SecPerClus);
	char* str = data[4], *temp = malloc(sizeof(char) * (strlen(data[4]) + 1));
	char match[ENTRY_LENGTH];
	for (i = 0; i < DirEntryPerCluster; i++)
	{
		if (get_entry_name(entries[i], match) && strcmp(match, data[1]) == 0)
		{
			int net = file_position + len;
			if (net > entries[i].DIR_FileSize)
			{
				entries[i].DIR_FileSize += net - entries[i].DIR_FileSize;	
			}
			fseek(img, get_cluster_offset(CurrentCluster), SEEK_SET);
			fwrite(entries, sizeof(DirEntry) * DirEntryPerCluster, 1, img);
			break;
		}
	}
	CurrentCluster = get_next_cluster(e);	
	while (file_position > clusterBytes)
	{
		file_position -= clusterBytes;
		CurrentCluster = read_FAT(CurrentCluster);
	}
	while (read_count < stream_count && read_count < len)
	{	
		unsigned int remain = clusterBytes - file_position;
		fseek(img, get_cluster_offset(CurrentCluster) + file_position, SEEK_SET);
		file_position = 0;
		if (remain < stream_count - read_count)
		{
			strncpy(temp, str, remain);
			str += remain;
			read_count += remain;
		}
		else 
		{
			strcpy(temp, str);
			remain = stream_count - read_count;
			read_count += stream_count - read_count;
		}
		fwrite(temp, remain, 1, img);
		CurrentCluster = read_FAT(CurrentCluster);
		if (CurrentCluster == EOC)
		{
			int prevCluster = CurrentCluster;
			CurrentCluster = get_next_FAT();
			if (CurrentCluster == NOTFOUND)
			{
				printf("Error: ran out of space\n");
				break;
			}	
			fseek(img, get_FATOffset(prevCluster, 1), SEEK_SET);
			fwrite(&CurrentCluster, sizeof(unsigned int), 1, img);
		}
	}
	free(temp);
}

void make_directory()
{
	unsigned int i, nextEntry = get_new_direntry(), newCluster = get_next_FAT();
	create_file(nextEntry, newCluster);
	if (nextEntry != NOTFOUND)
	{
		DirEntry e = entries[nextEntry];
		entries[nextEntry].DIR_Attr = 0x10;
		fseek(img, get_cluster_offset(CurrentCluster), SEEK_SET);
		fwrite(entries, sizeof(DirEntry) * DirEntryPerCluster, 1, img);
		strcpy(entries[0].DIR_Name, ".          ");
		strcpy(entries[1].DIR_Name, "..         ");
		for (i = 2; i < DirEntryPerCluster; i++)
		{
			entries[i].DIR_Name[0] = 0;
		}
		fseek(img, get_cluster_offset(get_next_cluster(e)), SEEK_SET);
		fwrite(entries, sizeof(DirEntry) * DirEntryPerCluster, 1, img);
	}
}

void create_file(unsigned int nextEntry, unsigned int newCluster)
{
	if (nextEntry != NOTFOUND)
	{
		char result[ENTRY_LENGTH];
		convert_entry(result);
		strcpy(entries[nextEntry].DIR_Name, result);
		entries[nextEntry].DIR_Attr = 0;
		entries[nextEntry].DIR_NTRes = 0;
		entries[nextEntry].DIR_FstClusHI = (unsigned short) newCluster;
		newCluster >>= 16;
		entries[nextEntry].DIR_FstClusLO = newCluster;
		entries[nextEntry].DIR_FileSize = 0;

		fseek(img, get_cluster_offset(CurrentCluster), SEEK_SET);
		fwrite(entries, sizeof(DirEntry) * DirEntryPerCluster, 1, img);
	}
}
void convert_entry(char* result)
{
	int pos = 0;
	int nextC = 0;
	while (data[1][nextC] != '\0' && data[1][nextC] != '.' && pos < DIRNAMELEN)
	{
		result[pos++] = toupper(data[1][nextC]);
		nextC++;
	}
	while (data[1][nextC] != '.' && data[1][nextC] != '\0')
	{
		nextC++;
	}
	if (data[1][nextC] == '.')
	{
		nextC++;
		while (pos < DIRNAMELEN)
		{
			result[pos++] = ' ';
		}
		while (data[1][nextC] != '\0' && pos < DIRPATHLEN)
		{
			result[pos++] = toupper(data[1][nextC++]);
		}
	}
	while (pos < DIRPATHLEN)
	{
		result[pos++] = ' ';
	}
	result[DIRPATHLEN] = '\0';
}

unsigned int get_new_direntry()
{
	int i, prevCluster;
	CurrentCluster = CWDCLUSTER[currentDir];
	fseek(img, get_cluster_offset(CWDCLUSTER[currentDir]), SEEK_SET);
	fread(entries, DirEntryPerCluster * sizeof(DirEntry), 1, img);
	while(true)
	{
		for (i = 0; i < DirEntryPerCluster; i++)
		{
			if (entries[i].DIR_Name[0] == '\0' || entries[i].DIR_Name[0] == NONDIR)
			{
				return i;
			}			
		}
		prevCluster = CurrentCluster;
		CurrentCluster = read_FAT(CurrentCluster);
		if (CurrentCluster >= EOC)
		{
			CurrentCluster = get_next_FAT();
			if (CurrentCluster == NOTFOUND)
			{
				return NOTFOUND;
			}	
			fseek(img, get_FATOffset(prevCluster, 1), SEEK_SET);
			fwrite(&CurrentCluster, sizeof(unsigned int), 1, img);
		}
		set_entries(CurrentCluster);
	}
	return NOTFOUND;
}

int get_next_FAT()
{
	int result = fs.FSI_Nxt_Free; 
	if (fs.FSI_Free_Count <= 0)
	{
		return NOTFOUND;
	}

	if (result == 0x0FFFFFFF || result == NOTFOUND)
	{
		result = get_next_free_FAT();
		if (result == NOTFOUND)
		{
			return NOTFOUND;
		}
	}

	fs.FSI_Free_Count--;
	fseek(img, get_FATOffset(result, 1), SEEK_SET);
	fwrite(&EOC, sizeof(unsigned int), 1, img);
	
	fs.FSI_Nxt_Free = get_next_free_FAT();

	fseek(img, bs.BPB_FSInfo * bs.BPB_BytesPerSec, SEEK_SET);
	fwrite(&fs, sizeof(FSInfo), 1, img);
	
	return result;
}

unsigned int get_next_free_FAT()
{
	int i;
	for (i = 0; i < FATBYTES; i++)
	{
		if (read_FAT(i) == 0)
		{
			return i; 
		}
	}
	return NOTFOUND;
}
void read_file()
{
	DirEntry e = get_directory_entry();
	int stream_count = atoi(data[3]), read_count = 0, file_position = atoi(data[2]);
	unsigned int thisRead, clusterBytes = (bs.BPB_BytesPerSec * bs.BPB_SecPerClus);
	char* read = (char*)malloc((sizeof(char) * stream_count) + 1);
	CurrentCluster = get_next_cluster(e);	
	memset(read, 0, stream_count);
	
	while (file_position > clusterBytes)
	{
		file_position -= clusterBytes;
		CurrentCluster = read_FAT(CurrentCluster);
	}

	while (read_count < stream_count)
	{	
		if (read_count + clusterBytes < stream_count)
		{
			thisRead = clusterBytes - file_position;
		}
		else
		{
			thisRead = stream_count % clusterBytes;
		}
		fseek(img, get_cluster_offset(CurrentCluster) + file_position, SEEK_SET);	
		fread(&read[read_count], thisRead, 1, img);
		file_position = 0;
		read_count+= thisRead;
		CurrentCluster = read_FAT(CurrentCluster);
	}
	read[stream_count] = 0;
	printf("%s\n", read);
	free(read);
}

DirEntry get_directory_entry()
{
	int i;
	char match[ENTRY_LENGTH];
	DirEntry e;
	while (CurrentCluster < EOC)
	{
		for (i = 0; i < DirEntryPerCluster; i++)
		{
			if (get_entry_name(entries[i], match) && strcmp(match, data[1]) == 0)
			{
				return entries[i];
			}
		}
		CurrentCluster = read_FAT(CurrentCluster);
		set_entries(CurrentCluster);
	}
	e.DIR_FileSize = NOTFOUND;
	return e;
}

void try_open_file(DirEntry e, unsigned short mode)
{
	char match[ENTRY_LENGTH];
	OpenFile newFile;
	get_entry_name(e, match);
	strcpy(newFile.file, match);
	newFile.mode = mode;
	newFile.isActive = true;
	open_file(newFile);
}

void open_file(OpenFile entry)
{
	int i, exist_index = get_open_file(data[1]);
	if (exist_index > NOTFOUND)
	{
		unsigned short mode = get_mode(data[2]);
		if (ft[exist_index].mode != mode)
		{
			ft[exist_index].mode = mode;
			return;
		}
		printf("Error: file already open!\n");
		return;
	}
	for (i = 0; i < MAXLENGTH; i++)
	{
		if (!ft[i].isActive)
		{
			ft[i] = entry;
			return;
		}
	}
}

int get_open_file(const char* name)
{
	int i;
	for (i = 0; i < MAXLENGTH; i++)
	{
		if (strcmp(ft[i].file, name) == 0 && ft[i].isActive)
		{
			return i;
		}
	}
	return NOTFOUND;
}

void try_close_file()
{
	int file_index = get_open_file(data[1]);
	if (file_index > -1)
	{
		ft[file_index].isActive = false;
		return;
	}
	printf("Error: file not open\n");
}

void close_all()
{
	int i;
	for (i = 0; i < MAXLENGTH; i++)
	{
		ft[i].isActive = false;
	}
}

unsigned int get_next_cluster(DirEntry e)
{
	return (e.DIR_FstClusHI << 8) |	e.DIR_FstClusLO;
}

void print_ls(DirEntry e)
{
	int i;
	char newDir[ENTRY_LENGTH];
	get_entry_name(e, newDir);
	strcpy(CWD[++currentDir], newDir);
	CWDCLUSTER[currentDir] = get_next_cluster(e);
	set_entries(CWDCLUSTER[currentDir]);
	CurrentCluster = CWDCLUSTER[currentDir];					
	while(CurrentCluster < EOC)
	{
		for (i = 0; i < DirEntryPerCluster; i++) 
		{
			print_name(entries[i]);
		}
		CurrentCluster = read_FAT(CurrentCluster);
		set_entries(CurrentCluster);
	}
	currentDir--;
	
	printf("\n");
}

unsigned int read_FAT(unsigned int n)
{
	unsigned int offset = get_FATOffset(n, 1);
	unsigned int next_entry;
	
	fseek(img, offset, SEEK_SET);
	fread(&next_entry, sizeof(unsigned int), 1, img);
	if (n == next_entry)
	{
		return EOC;
	}
	return next_entry;
}

unsigned int get_FATOffset(unsigned int n, unsigned int fatNum)
{
	return (unsigned int)((n * 4) + bs.BPB_RsvdSecCnt 
	* bs.BPB_BytesPerSec + (fatNum - 1) * bs.BPB_FATSz32 * bs.BPB_BytesPerSec);
}

unsigned int get_cluster_offset(unsigned int n)
{
	return (((n - 2) * bs.BPB_SecPerClus) + FirstDataSector) * bs.BPB_BytesPerSec;
}
void set_entries(unsigned int n)
{
	fseek(img, get_cluster_offset(n), SEEK_SET);
	fread(entries, DirEntryPerCluster * sizeof(DirEntry), 1, img);
}

void print_size()
{
	int size = get_entry_size();
	if (size <= NOTFOUND)
	{
		printf("Error: file does not exist\n");
	}
	else if (get_directory_entry().DIR_Attr == 0x10)
	{
		printf("Error: this is a directory\n");
	}
	else
	{
		printf("%d\n", size);
	}
}

int get_entry_size()
{
	return get_directory_entry().DIR_FileSize;
}

void change_directory(DirEntry e)
{
	char newDir[ENTRY_LENGTH];
	get_entry_name(e, newDir);
	strcpy(CWD[++currentDir], newDir);
	close_all();
	CWDCLUSTER[currentDir] = get_next_cluster(e);	
}

bool get_entry_name(DirEntry e, char* result)
{
	unsigned int i = 0, fill = 0;
	if (e.DIR_Name[0] == '\0' || e.DIR_Name[0] == NONDIR 
	|| (e.DIR_Attr & ISLONGDIR) == ISLONGDIR)
	{
		/* ignore */
		return false;
	}
	/*print short name*/
	while(e.DIR_Name[i] != ' ' && i < DIRNAMELEN)
	{
		result[fill++] = e.DIR_Name[i++];
	}
	i = DIRNAMELEN;
	/*print filetype*/
	if (e.DIR_Name[i] != ' ')
	{
		result[fill++] = '.';
	}
	while (e.DIR_Name[i] != ' ' && i < DIRPATHLEN)
	{
		result[fill++] = e.DIR_Name[i++];
	}
	result[fill] = '\0';
	return true;
}

void print_name(DirEntry e)
{
	char entry[ENTRY_LENGTH];
	if (get_entry_name(e, entry))
	{
		printf("%s ", entry);
	}
}

unsigned short get_mode(const char* mode)
{
	if (strcmp(mode, "r") == 0)
	{
		return READONLY;
	}
	if (strcmp(mode, "w") == 0)
	{
		return WRITEONLY;
	}
	if (strcmp(mode, "rw") == 0)
	{
		return RWMODE;
	}
	if (strcmp(mode, "wr") == 0)
	{
		return RWMODE;
	}
	return INVALID;
}