#ifndef SHELLOPS_H
#define SHELLOPS_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
	int size;
	char** data;
} Array;

typedef struct{
	char* command;
	pid_t pid;
} bkgrd_prcs;

typedef struct {
	bkgrd_prcs* queue;
} bkgrd_q;

void setup();
void generateCommandsList();
void cleanUp(char* line, Array lineArgs);


/*interaction functions*/
void prompt();
char* readInput();


/*parse function*/
Array begin_parse(char* line);
void parse_whitespace(char* line);

void resolve_paths(Array lineArgs);
void expand_path(char* arg);
void expand_global(char* arg);
void expand_home(char* arg);


/*command execution*/
void process_args(Array lineArgs);
void execute_command(char* command);
void built_in_commands(char* command, int id);
bool find_redirection(Array args);
bool find_background(Array args);
/*helper functions*/


bool isAsciiMatch(char c, const char* str);


int getCommandId(char* cmdStr);
int contains_builtin(Array args);


void freeStringArray(Array ary);
Array split_args(char* line, char splitOnSymbol);
char* connect_array(Array ary);
int get_used_size(Array ary);
void printStrArray(Array lineArgs);
Array getNewStringArray(int size);
char* getNewString();
void getSubstring(char* str, int start, int finish);
Array get_fitted_array(char* line);
#endif
