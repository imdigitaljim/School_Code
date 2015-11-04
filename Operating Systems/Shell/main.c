#define MAXLENGTH 255
#define MAXVAR 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "shellops.h"

int main(int argc, char** argv)
{
	/*setup*/
	char* line;
	Array lineArgs;
	bool isExit = false;
	while (true)
	{	
		setup();

		/*prompt user*/
		prompt();
		/*read*/
		line = readInput();

		/*parse*/
		lineArgs = begin_parse(line);
		if (lineArgs.size > 0)
		{
			process_args(lineArgs);
		}
		else if (lineArgs.size < 0)
		{
			isExit = true;
		}
		cleanUp(line, lineArgs);
		if (isExit)
		{
			exit(0);	
		}
	}
	return 0;
}


