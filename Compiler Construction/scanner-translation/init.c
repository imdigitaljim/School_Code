/**** init.c ****/

#include "global.h"

int keywords_count = 0;

struct entry keywords[] =
{ 
	{"if", IF}, {"else", ELSE}, 
	{"while", WHILE}, {"arg", ARG},
	{"return", RETURN},	{0,0}	
};

void init()
{ 
	struct entry *p;
	for (p = keywords; p->token; p++)
	{
		insert(p->lexptr, p->token);
		keywords_count++;
	}
		
}