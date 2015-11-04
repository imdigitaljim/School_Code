#define _DEFAULT_SOURCE /* to prevent implicit function definition */
#define MAXLENGTH 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shellops.h"

const char* commands[] = { "exit", "cd", "echo", "etime", "limits"};
Array pathDir;
bool isError, exitApplication;

void setup()
{
	/*this is a global variable of global paths that holds the locations executable commands*/
	char* token, *envPath = getenv("PATH");
	char path[MAXLENGTH];
	const char s[2] = ":";
	int i = 0;
	strcpy(path, envPath);
	isError = false;
	exitApplication = false;
	pathDir = getNewStringArray(MAXLENGTH); 
	token = strtok(path, s);
	while (token != NULL)
	{
		/* build a string list of these paths and clear them out each time because they can change*/
		strcpy(pathDir.data[i], token);
		strcat(pathDir.data[i++], "\0");
		token = strtok(NULL, s);
	}
}
void prompt() {
	char user[MAXLENGTH];
	char machine[MAXLENGTH];
	char cwd[MAXLENGTH];
	gethostname(machine, MAXLENGTH);
	getlogin_r(user, MAXLENGTH);
	getcwd(cwd, sizeof(cwd));
	printf("%s@%s: %s => ", user, machine, cwd);
}

char* readInput()
{
	char input[MAXLENGTH];
	char* line;
	memset(input, 0, MAXLENGTH);
	scanf(" %[^\n]", input);
	line = getNewString();
	strcpy(line, input);
	strcat(line, "\0");
	return line;
}

Array begin_parse(char* line)
{
	Array lineArgs, pipeList;
	int i, usedSize;
	char* tempStr;
	parse_whitespace(line);
	pipeList = split_args(line, '|');
	usedSize = get_used_size(pipeList);
	for (i = 0; i < usedSize; i++)
	{
		lineArgs = split_args(pipeList.data[i] , ' ');
		memset(pipeList.data[i], 0, MAXLENGTH);
		resolve_paths(lineArgs);
		tempStr = connect_array(lineArgs);
		strcpy(pipeList.data[i], tempStr);
		free(tempStr);
	}
	freeStringArray(lineArgs);
	if (isError)
	{
		Array fail;
		freeStringArray(pipeList);
		fail.size = 0;
		return fail;
	}
	else if (exitApplication)
	{
		Array exit;
		freeStringArray(pipeList);
		exit.size = -1;
		return exit;
	}
	return pipeList;
}

char* connect_array(Array ary)
{
	char* str = getNewString();
	int j, usedSize = get_used_size(ary);
	for (j = 0; j < usedSize; j++)
	{
		strcat(str, ary.data[j]);
		if (j + 1 < usedSize)
		{
			strcat(str, " ");
		}
	}
	return str;
}


void parse_whitespace(char* line)
{
	int lineIndex = 0, newLineIndex = 0, i = 1;
	char current;
	char tempLine[MAXLENGTH];
	bool isSpaceInserted = false;
	memset(tempLine, 0, MAXLENGTH);

	/*trim leading whitespace*/
	while (line[lineIndex] == ' ')
	{
		lineIndex++;
	}
	current = line[lineIndex];
	while(current != 0)
	{
		/*if its a non-space or it is the first space after a string*/
		if (current != ' ' || (current == ' ' && !isSpaceInserted))
		{
			/*if its a reserved symbol*/
			if (isAsciiMatch(current, "|<>&"))
			{
				if (!isSpaceInserted)
				{
					tempLine[newLineIndex++] = ' ';
				}
				tempLine[newLineIndex++] = current;
				tempLine[newLineIndex++] = ' ';
				isSpaceInserted = true;
 			}
			else
			{
				isSpaceInserted = (current == ' ');
				tempLine[newLineIndex++] = current;
			}	
		}
		current = line[++lineIndex];
	}
	/* trim trailing whitespace */
	while (tempLine[strlen(tempLine) - i] == ' ')
	{
		tempLine[strlen(tempLine) - i] = 0;
	}
	strcpy(line, tempLine);
}

Array split_args(char* line, char splitOnSymbol)
{
	char* token, s[2];
	int i = 0;
	Array lineArgs = getNewStringArray(MAXLENGTH);
	s[0] = splitOnSymbol;
	s[1] = 0;
	token = strtok(line, s);
	while (token != NULL)
	{
		strcpy(lineArgs.data[i], token);
		strcat(lineArgs.data[i++], "\0");
		token = strtok(NULL, s);
	}
	return lineArgs;
}

int getCommandId(char* cmdStr)
{
	int i, size = sizeof(commands)/sizeof(char*);
	const char* validCmd;
	for (i = 0; i < size; i++ )
	{
		validCmd = commands[i];
		if (strcmp(validCmd, cmdStr) == 0)
		{
			return i;
		}
	}
	return -1;
}


void resolve_paths(Array lineArgs)
{
	int i, j, k, cmdId, usedSize = get_used_size(lineArgs), len;
	char* arg, *path;
	char commandError[MAXLENGTH];
	bool commandFound = false, isEcho = false, checkForBP = true, isEtime = false, isLimits = false;
	memset(commandError, 0, MAXLENGTH);
	strcpy(commandError, lineArgs.data[0]);
	for (i = 0; i < usedSize; i++)
	{
		if (!commandFound && i > 0)
		{
			fprintf(stderr, "%s: Command not found.\n", commandError);
			isError = true;
			return;
		}
		arg = lineArgs.data[i];
		if (checkForBP && arg[0] == '&')
		{
			for (j = i; j < usedSize - 1; j++)
			{
				strcpy(lineArgs.data[j], lineArgs.data[j + 1]);
			}
			usedSize--;
			memset(lineArgs.data[usedSize], 0, MAXLENGTH);
			arg = lineArgs.data[i];
			checkForBP = false;
		}
		if (isAsciiMatch(arg[0], "<>"))
		{
			checkForBP = true;
			continue;
		}
		if (isAsciiMatch(arg[0], "-&"))
		{
			continue;
		}
		cmdId = getCommandId(arg);
		if (!isEcho && cmdId >= 0)
		{
			char* builtInString = getNewString();
			strcat(builtInString, "$$");
			strcat(builtInString, arg);
			strcpy(lineArgs.data[i], builtInString);
			commandFound = true;
			free(builtInString);
			switch(cmdId)
			{
				case 0:
					if (usedSize > 1)
					{
						fprintf(stderr, "exit: Expression Syntax.\n");
						isError = true;
						return;
					}
					fprintf(stderr, "Exiting Shell....\n");
					exitApplication = true;
					return;
				case 1:
					if (usedSize == 1)
					{
						usedSize++;
						strcpy(lineArgs.data[i + 1], "~");
					}
					else if (usedSize > 2)
					{
						fprintf(stderr,"cd: Too many arguments.\n");
						isError = true;
						return;
					}	
					break;
				case 2:
					isEcho = true;
					break;
				case 3:
					isEtime = true;
					break;
				case 4:
					isLimits = true;
					break;
				default:
					break;
			}
			continue;
		}
		if (isEcho)
		{
			char* globalPtr = strstr(arg, "$");
			if (arg[0] == '~')
			{
				expand_home(lineArgs.data[i]);
			}
			if (globalPtr != NULL)
			{
				char name[MAXLENGTH], *str;
				j = 0, k = 1;
				memset(name, 0, MAXLENGTH);
				while ((globalPtr[k] >= 48 && globalPtr[k] <= 57) 
					|| (globalPtr[k] >= 65 && globalPtr[k] <= 90)
					|| (globalPtr[k] >= 97 && globalPtr[k] <= 122)
					|| (globalPtr[k] == 95))
				{
					name[j++] = globalPtr[k];
					k++;
				}
				str = getenv(name);
				if (str == NULL)
				{
					fprintf(stderr,"%s: Undefined variable.\n", name);
					isError = true;
					return;
				}
				strcpy(arg, str);
			}			
			continue;
		}
		if (!commandFound || isEtime || isLimits)
		{
			char checkPath[MAXLENGTH];
			memset(checkPath, 0, MAXLENGTH);
			for (j = 0; j < pathDir.size; j++)
			{
				path = pathDir.data[j];
				strcpy(checkPath, path);
				strcat(checkPath, "/");
				strcat(checkPath, arg);
				if (access(checkPath, F_OK) != -1)
				{
					expand_path(checkPath);
					if (isError)
					{
						return;
					}
					memset(lineArgs.data[i], 0, MAXLENGTH);
					strcpy(lineArgs.data[i], checkPath);
					commandFound = true;
					if (isEtime)
					{
						isEtime = false;
					}
					if (isLimits)
					{
						isLimits = false;
					}
					break;
				}
			}
			if (commandFound)
			{
				continue;
			}
		}
		
		len = strlen(arg);
		j = 0;
		for (k = 0; k < len; k++)
		{
			if (arg[k] >= 48 && arg[k] <= 57)
			{
				j++;
			}
		}
		if (len != j)
		{
			expand_path(arg);
		}
		if (isError)
		{
			return;
		}
	}	
}

void expand_path(char* arg)
{
	Array path = getNewStringArray(MAXLENGTH);
	char* token, *a, *b;
	char buffer[MAXLENGTH], s[2] = "/";
	char cwd[MAXLENGTH]; 
	int i = 0, usedSize;
	size_t argLen = strlen(arg);
	getcwd(cwd, sizeof(cwd));
	if (strcmp(cwd, "/") == 0)
	{
		strcpy(cwd, "");
	}
	memset(buffer, 0, MAXLENGTH);
	if (arg[0] == '~')
	{
		expand_home(arg);
	}
	if (argLen <= 1)
	{
		freeStringArray(path);
		return;
	}
	if (strncmp(arg, "./", sizeof(char) * 2) == 0)
	{
		char newStr[MAXLENGTH];
		a = arg + 1;
		strcpy(newStr, cwd);
		strcat(newStr, a);
		strcpy(arg, newStr);
	}
	if (strncmp(arg, "../", sizeof(char) * 3) == 0)
	{
		char newStr[MAXLENGTH];
		a = arg + 2;
		strcpy(newStr, cwd);
		strcat(newStr, a);
		strcpy(arg, newStr);
	}
	if ((strstr(arg, s) == NULL && strstr(arg, "$") == NULL) || strcmp(arg, "../") == 0)
	{
		if (arg[0] ==  '.' && strlen(arg) == 1)
		{
			strcpy(arg, "");
		}
		strcpy(buffer, cwd);
		if (strcmp(arg, "..") == 0 || strcmp(arg, "../") == 0)
		{
			size_t len = strlen(buffer) - 1;
			for (i = 0; i < len; i++)
			{
				if (len - i - 1 <= 0)
				{
					strcpy(buffer, "/");
					break;
				}
				if (buffer[len - i - 1] == '/')
				{

					buffer[len - i - 1] = 0;
					break;
				}
			}
		}
		else
		{
			strcat(buffer, "/");
			strcat(buffer, arg);
		}
		strcpy(arg, buffer);
		freeStringArray(path);
		return;
	}
	a = b = arg;
	while (b[0] != 0)
	{
		if (strncmp(b, "./", sizeof(char) * 2) == 0)
		{
			strcpy(b, b + 2);
			continue;
		}
		if (strncmp(b, "../", sizeof(char) * 3) == 0)
		{
			a = b;
			b -= 2;
			while(b[0] != '/')
			{
				b--;
			}
			strcpy(b, a + 2);
		}
		b++;
	}
	token = strtok(arg, s);
	while (token != NULL)
	{
		if (strcmp(token, ".") != 0)
		{
			strcpy(buffer, token);
			expand_global(buffer);
			if (isError)
			{
				freeStringArray(path);
				return;
			}
			strcpy(path.data[i++], buffer);
		}
		token = strtok(NULL, s);
		if (token != NULL)
		{
			strcpy(path.data[i++], "/");
		}
	}
	memset(buffer, 0, MAXLENGTH);
	usedSize = get_used_size(path);
	for (i = 0; i < usedSize; i++)
	{
		strcat(buffer, path.data[i]);
	}
	if (buffer[0] != '/')
	{
		char temp[MAXLENGTH];
		strcpy(temp, "/");
		strcat(temp, buffer);
		strcpy(buffer, temp);
	}
	strcpy(arg, buffer);
	freeStringArray(path);
}

void expand_global(char* arg)
{
	char* envStr;
	if (arg[0] == '$' && arg[1] != 0)
	{
		getSubstring(arg, 1, strlen(arg));
		envStr = getenv(arg); 
		if (envStr != NULL)
		{
			strcpy(arg, envStr);
			return;
		}
		else{
			fprintf(stderr, "%s: Undefined variable.\n", arg);
			return;
		}
	}
}
void expand_home(char* arg)
{
	if (arg[0] == '~')
	{
		char* homeEnv = getNewString();
		getSubstring(arg, 1, strlen(arg));
		strcat(homeEnv, getenv("HOME"));
		strcat(homeEnv, arg);
		strcpy(arg, homeEnv);
		free(homeEnv);
	}
}

void process_args(Array lineArgs)
{
	int usedSize = get_used_size(lineArgs);
	int fd[2], fd2[2], fd3[2], status = 0, status2 = 0, status3 = 0, status4 = 0;
	Array pipe1, pipe2;
	pid_t isShell, pid, pid2, pid3;
	if (usedSize == 1)
	{
		execute_command(lineArgs.data[0]);
		return;
	}
	if (usedSize == 2)/* 1 pipe present*/
	{	
		if ((isShell = fork()) == 0)
		{
			pipe(fd);
			if ((pid = fork()) == 0)
			{
				close(STDOUT_FILENO);
				dup(fd[1]);
				close(fd[0]);
				close(fd[1]);
				pipe1 = get_fitted_array(lineArgs.data[0]);
				execv(pipe1.data[0], pipe1.data);	
				exit(1);
			}
			else
			{
				waitpid(pid, &status2, 0);
				close(STDIN_FILENO);
				dup(fd[0]);
				close(fd[0]);
				close(fd[1]);
				pipe2 = get_fitted_array(lineArgs.data[1]);
				execv(pipe2.data[0], pipe2.data);
				exit(1);
			}
		}
		else
		{
			waitpid(isShell, &status, 0);
			return;
		}
	}
	else if (usedSize == 3)/* 2 pipes present*/
	{
		if ((isShell = fork()) == 0)
		{
			pipe(fd);
			if ((pid = fork()) == 0)
			{
				pipe(fd2);
				if ((pid2 = fork()) == 0)
				{
					close(STDOUT_FILENO);
					dup(fd2[1]);
					close(fd2[0]);
					close(fd2[1]);
					close(fd[0]);
					close(fd[1]);
					pipe1 = get_fitted_array(lineArgs.data[0]);
					execv(pipe1.data[0], pipe1.data);	
					exit(1);
				}
				else
				{
					waitpid(pid2, &status3, 0);
					close(STDIN_FILENO);
					dup(fd2[0]);
					close(fd2[0]);
					close(fd2[1]);
					close(STDOUT_FILENO);
					dup(fd[1]);
					close(fd[0]);
					close(fd[1]);	
					pipe1 = get_fitted_array(lineArgs.data[1]);
					execv(pipe1.data[0], pipe1.data);
					exit(1);
				}
			}
			else
			{
				waitpid(pid, &status2, 0);
				close(STDIN_FILENO);
				dup(fd[0]);
				close(fd[0]);
				close(fd[1]);
				pipe1 = get_fitted_array(lineArgs.data[2]);
				execv(pipe1.data[0], pipe1.data);
				exit(1);
			}
		}
		else
		{
			waitpid(isShell, &status, 0);
			return;
		}
	}
	else if (usedSize == 4) /* 3 pipes present*/
	{
		if ((isShell = fork()) == 0)
		{
			pipe(fd);
			if ((pid = fork()) == 0)
			{
				pipe(fd2);
				if ((pid2 = fork()) == 0)
				{
					pipe(fd3);
					if ((pid3 = fork()) == 0)
					{
						close(STDOUT_FILENO);
						dup(fd3[1]);
						close(fd3[0]);
						close(fd3[1]);
						close(fd2[0]);
						close(fd2[1]);
						close(fd[0]);
						close(fd[1]);
						pipe1 = get_fitted_array(lineArgs.data[0]);
						execv(pipe1.data[0], pipe1.data);	
						exit(1);
					}
					else
					{
						waitpid(pid3, &status4, 0);
						close(STDIN_FILENO);
						dup(fd3[0]);
						close(fd3[0]);
						close(fd3[1]);
						close(STDOUT_FILENO);
						dup(fd2[1]);
						close(fd2[0]);
						close(fd2[1]);
						close(fd[0]);	
						close(fd[1]);
						pipe1 = get_fitted_array(lineArgs.data[1]);
						execv(pipe1.data[0], pipe1.data);
						exit(1);
					}

				}
				else
				{
					waitpid(pid2, &status3, 0);
					close(STDIN_FILENO);
					dup(fd2[0]);
					close(fd2[0]);
					close(fd2[1]);
					close(STDOUT_FILENO);
					dup(fd[1]);
					close(fd[0]);
					close(fd[1]);	
					pipe1 = get_fitted_array(lineArgs.data[2]);
					execv(pipe1.data[0], pipe1.data);
					exit(1);
				}
			}
			else
			{
				waitpid(pid, &status2, 0);
				close(STDIN_FILENO);
				dup(fd[0]);
				close(fd[0]);
				close(fd[1]);
				pipe1 = get_fitted_array(lineArgs.data[3]);
				execv(pipe1.data[0], pipe1.data);
				exit(1);
			}
		}
		else
		{
			waitpid(isShell, &status, 0);
			return;
		}		
	}
}

void execute_command(char* command)
{
	Array customArgs;
	int status, id, usedSize;
	bool isBackground, 	hasRedirect;
	customArgs = get_fitted_array(command);
	id = contains_builtin(customArgs);
	usedSize = customArgs.size;  
	hasRedirect = find_redirection(customArgs); 
	if (hasRedirect)
	{
		int i = 0;
		char io = 0;	
		char strLeft[MAXLENGTH], strRight[MAXLENGTH];
		memset(strLeft, 0, MAXLENGTH);
		memset(strRight, 0, MAXLENGTH);
		while (i < usedSize)
		{
			if (isAsciiMatch(customArgs.data[i][0], "<>"))
			{
				Array cmdArray = get_fitted_array(strLeft);
				isBackground = find_background(cmdArray);
				io = customArgs.data[i++][0];	
				while (i < usedSize)
				{
					if (isAsciiMatch(customArgs.data[i][0], "<>"))
					{
						/* continuing*/
						io = customArgs.data[i++][0];
						break;
					}
					strcat(strRight, customArgs.data[i]);
					if (i + 1 < usedSize)
					{
						strcat(strRight, " ");
					}
					i++;
				}
				if (strlen(strRight) == 0)
				{
					fprintf(stderr, "Missing Arguments.\n");
					break;
				}
				if (io == '<')
				{
					int fd;
					pid_t pid;
					if (access(strRight, F_OK) == -1)
					{
						fprintf(stderr, "%s: No such file or directory\n", strRight);
						break;
					}
					fd = open(strRight, O_RDWR);
					pid = fork();
					if (pid == 0)
					{
						close(STDIN_FILENO);
						dup(fd);
						close(fd);
						if (id < 0)
						{
							execv(cmdArray.data[0], cmdArray.data);
						}
						else
						{
							built_in_commands(command, id);
						}

					}
					else
					{
						waitpid(pid, &status, 0);
						close(fd);
					}
				}
				else if (io == '>')
				{
					int fd = open(strRight, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
					pid_t pid = fork();
					if (pid == 0)
					{
						close(STDOUT_FILENO);
						dup(fd);
						close(fd);
						if (id < 0)
						{
							execv(cmdArray.data[0], cmdArray.data);	
						}
						else
						{
							built_in_commands(command, id);
						}
						
					}
					else
					{
						waitpid(pid, &status, 0);
						close(fd);
					}
				}
				if (i < usedSize)
				{
					/*save process*/
					memset(strLeft, 0, MAXLENGTH);
					memset(strRight, 0, MAXLENGTH);		
				}
				freeStringArray(cmdArray);
			}
			if (i < usedSize)
			{
				strcat(strLeft, customArgs.data[i]);
			}
			if (i + 1 < usedSize && !isAsciiMatch(customArgs.data[i + 1][0], "<>" ))
			{
				strcat(strLeft, " ");
			}
			i++;
		}
	}
	else if(id >= 0)
	{
		isBackground = find_background(customArgs);
		built_in_commands(command, id);
	}
	else 
	{
		if (isAsciiMatch(customArgs.data[0][0], "<>"))
		{
			fprintf(stderr,"Missing name for redirect.\n");
		}
		else
		{
			pid_t pid = fork();
			if (pid == -1)
			{
				fprintf(stderr, "Failed to create process.\n");
			}
			else if (pid == 0)
			{	
				execv(customArgs.data[0], customArgs.data);
				fprintf(stderr, "%s: Execution failed.\n", customArgs.data[0]);
				exit(1);
			}
			else
			{
				/*parent*/
				waitpid(pid, &status, 0);
			}	
		}
	}
	freeStringArray(customArgs);
}

Array get_fitted_array(char* line)
{
	Array fitted, args;
	char tempLine[MAXLENGTH];
	int i, fittedSize;
	memset(tempLine, 0, MAXLENGTH);
	strcpy(tempLine, line);
	args = split_args(tempLine, ' ');
	fittedSize = get_used_size(args);
	fitted = getNewStringArray(fittedSize);
	for (i = 0; i < fittedSize; i++)
	{
		strcpy(fitted.data[i], args.data[i]);
	}
	freeStringArray(args);
	return fitted;
}

bool find_background(Array args)
{
	int i;
	for (i = 1; i < args.size; i++)
	{
		if (isAsciiMatch(args.data[i][0], "&"))
		{
			return true;
		}
	}
	return false;
}
bool find_redirection(Array args)
{
	int i;
	for (i = 1; i < args.size; i++)
	{
		if (isAsciiMatch(args.data[i][0], "<>"))
		{
			return true;
		}
	}
	return false;
}
int contains_builtin(Array args)
{
	int i;
	for (i = 0; i < args.size; i++)
	{
		if (strstr(args.data[i], "$$"))
		{
			char* a = args.data[i];
			a += 2;
			strcpy(args.data[i], a);
			return getCommandId(args.data[i]);
		}
	}
	return -1;
}

void built_in_commands(char* command, int id) {
	Array execCmd = get_fitted_array(command);
	char* justArgs;
	pid_t pid;
	int status;
	contains_builtin(execCmd);
	strtok(command, " ");
	justArgs = strtok(NULL, "\n");
	if (id == 1) 
	{ /*cd*/
		int x = chdir(justArgs);
		if(x == -1)
		{		
			fprintf(stderr, "cd: %s: No such file or directory\n", justArgs);
		}
		else if (x == 0)
		{
			setenv("PWD", justArgs, 1);
		}
	}
	else if(id == 2) 
	{ /*echo*/
		printf("%s\n", justArgs);
	}
	else if(id == 3)
	{ /*etime*/
		struct timeval time1, time2;
		gettimeofday(&time1, NULL);
		if((pid = fork()) < 0) 
		{
			fprintf(stderr, "Failed to create process\n");
		}
		else if(pid == 0) {
			execv(execCmd.data[1], execCmd.data + 1);
			fprintf(stderr,"%s: Failed to run\n", execCmd.data[1]);
			exit(1);
		}
		else {
			waitpid(pid, &status, 0);
			gettimeofday(&time2, NULL);
			printf("Elapsed time: %ld.%.6lds\n", (time2.tv_sec - time1.tv_sec), (time2.tv_usec - time1.tv_usec));
		}
	}
	else if(id == 4) 
	{ /*limits*/
		FILE *limitsFile;
		char limitsArray[30][80], path[30];
		int i;
		for (i = 0; i < 30; i++)
		{
			memset(limitsArray[i], 0, 80);
		}
		memset(path, 0, 30);
		strcpy(path, "/proc/");
		if ((pid = fork()) < 0) 
		{
			fprintf(stderr, "Failed to create process\n");
		}
		else if (pid == 0) 
		{
			execv(execCmd.data[1], execCmd.data + 1);
			fprintf(stderr, "%s: Failed to run\n", execCmd.data[1]);
			exit(1);
		}
		else 
		{
			int pidInt = pid;
			char pidNum[10];
			sprintf(pidNum, "%d", pidInt);
			strcat(path, pidNum);
			strcat(path, "/limits");
			limitsFile = fopen(path, "r");
			i = 0;
			while (i != 28)
			{
				fgets(limitsArray[i++], 78, limitsFile);
			}
			fclose(limitsFile);
			waitpid(pid, &status, 0);
		}
		printf("%s\n", limitsArray[4]);
		printf("%s\n", limitsArray[16]);
		printf("%s\n", limitsArray[14]);
		printf("%s\n", limitsArray[24]);
	}
	freeStringArray(execCmd);
}


/*helper functions*/
bool isAsciiMatch(char c, const char* str)
{
	const char* ptr = str;
	while(*ptr != 0)
	{
		if (*ptr == c)
		{
			return true;
		}
		ptr++;
	}
	return false;
}

void printStrArray(Array lineArgs)
{
	int i;
	printf("\n*****PRINTING VALUES*****\n");
	for (i = 0; i < lineArgs.size; i++)
	{
		if (lineArgs.data[i][0] != 0)
		{
			printf("%d = |%s|\n", i, lineArgs.data[i]);	
		}

	}
	printf("\n*************************\n");
}

Array getNewStringArray(int size)
{
	int i;
	Array newAry;
	newAry.size = size;
	newAry.data	= (char**) malloc(sizeof(char*) * (size + 1));
	for (i = 0; i < size; i++)
	{
		newAry.data[i] = getNewString();
	}
	newAry.data[size] = NULL;
	return newAry;
}

char* getNewString()
{
	char* temp = (char*) malloc(sizeof(char) * MAXLENGTH);
	memset(temp, 0, MAXLENGTH);
	return temp;
}

int get_used_size(Array ary)
{
	int i;
	for (i = 0; i < ary.size; i++)
	{
		if (ary.data[i][0] == 0)
		{
			return i;
		}
	}
	return -1;
}

void freeStringArray(Array ary)
{
	int i;
	if (ary.size != 0)
	{
		for (i = 0; i < ary.size + 1; i++)
		{
			if (ary.data[i] != NULL)
			{
				free(ary.data[i]);
				ary.data[i] = NULL;
			}
		}
		free(ary.data);
		ary.data = NULL;	
	}
}

void getSubstring(char* str, int start, int finish)
{
	int i, j = 0, len = strlen(str);	
	char* substr;
	if (start < 0 || finish > len)
	{
		return;
	}
	substr = getNewString();
	for (i = start; i < finish; i++)
	{
		substr[j++] = str[i];
	}
	substr[j] = 0;
	strcpy(str, substr);
	free(substr);	
}

void cleanUp(char* line, Array commandArgs)
{
	freeStringArray(pathDir);
	freeStringArray(commandArgs);
	free(line);
}
