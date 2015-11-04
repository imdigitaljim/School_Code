#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	/*char input1[10], input2[10];
	scanf("%s", input1);*/
	char *const args[] = {"/bin/ls", "-l", NULL};
	pid_t pid;
	int status;
	struct timeval time1, time2;
	gettimeofday(&time1, NULL);
	if((pid = fork()) < 0) {
		printf("fork failed\n");
		exit(0);
	}
	else if(pid == 0) {
		/*printf("child process\n");*/
		execv("/bin/ls", args);
	}
	else {
		/*printf("test");*/
		waitpid(pid, &status, 0);
		gettimeofday(&time2, NULL);
		printf("Elapsed time: %ld.%.6ld\n", (time2.tv_sec - time1.tv_sec), (time2.tv_usec - time1.tv_usec));
	}
	/*scanf("%s", input2);
	printf("%s   %s\n", input1, input2);*/
	return 0;
}
