#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	FILE *limitsFile;
	char limitsArray[30][80];
	char path[30];
	strcpy(path, "/proc/");
	int i;
	char *const args[] = {"/bin/ls", "-l", NULL};
	pid_t pid;
	int status;
	if((pid = fork()) < 0) {
		printf("fork failed\n");
		exit(0);
	}
	else if (pid == 0) {
		execv("/bin/ls", args);
	}
	else {
		int pidInt = pid;
		char pidNum[10];
		sprintf(pidNum, "%d", pidInt);
		strcat(path, pidNum);
		strcat(path, "/limits");
		limitsFile = fopen(path, "r");
		i = 0;
		while(i != 28)
			fgets(limitsArray[i++], 78, limitsFile);
		fclose(limitsFile);
		waitpid(pid, &status, 0);
	}
	printf("%s\n", limitsArray[4]);
	printf("%s\n", limitsArray[16]);
	printf("%s\n", limitsArray[14]);
	printf("%s\n", limitsArray[24]);
	return 0;
}
