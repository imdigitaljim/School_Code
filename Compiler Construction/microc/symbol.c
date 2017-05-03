/* TODO: TO BE COMPLETED */

#include "global.h"

/* TODO: define a symbol table/array, reuse project Pr1 */

#define STRMAX 99999
#define SYMMAX 1000

char lexemes[STRMAX];
int lastchar = -1;
struct Symbol symtable[SYMMAX];
int lastentry = 0;
const int keyword_count = 8;
/*
struct Symbol
{
	char* lexptr;
	int  token;
	int  localvar; 
};
*/

Symbol* lookup(const char* s)
{ 
	for (int i = lastentry; i > 0; i = i - 1)
	{
		if (strcmp(symtable[i].lexptr, s) == 0)	return &symtable[i];
	}	
	return 0;
}
Symbol* insert(const char* s, int tok)
{ 
	int len = strlen(s);
	if (lastentry + 1 >= SYMMAX) error("symbol table full");
	if (lastchar + len + 1 >= STRMAX) error("lexemes array full");
	lastentry++;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];
	lastchar = lastchar + len + 1;
	strcpy((char *) symtable[lastentry].lexptr, s);
	return &symtable[lastentry];
}