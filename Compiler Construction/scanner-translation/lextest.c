#include <stdio.h>
#include "global.h"

/*
{ n = 2; m = 1000*n+arg[0]; }

<{,-1> <ID,3> <=,-1> <INT8, 2> <;,-1> <ID,4> <=,-1> <INT16,1000> <*,-1> <ID,3> <+,-1><ARG,-1> <[,-1> <INT8,0> <],-1> <;,-1> <},-1>
*/

int main()
{
	init();
	while(1)
	{
		int token = lexan();
		if (token == DONE) break;
		if (token <= 255) /* WTF - is it ADD/MULT/ETC? */
		{
			printf("<%c,%d>\n", token ,tokenval);
		}
		else
		{
			switch(token)
			{
				case ID:
					printf("<ID,%d>\n", lookup(lexbuf) - keywords_count + 2); /* WTF - offset from keywords? */
					break;
				case INT8:
					printf("<INT8,%d>\n", tokenval);
					break;
				case INT16:
					printf("<INT16,%d>\n", tokenval);
					break;
				case INT32:
					printf("<INT32,%d>\n", tokenval);
					break;
				case ARG:
					printf("<ARG,%d>\n", tokenval);
					break;
				default:
					break;				
			}
		}
	}
	return 0;
}