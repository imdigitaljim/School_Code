/**** global.h ****/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define INT8_MAX 127
#define INT16_MAX 32767

/* tokens identifiers */
#define BSIZE 128
#define NONE -1
#define EOS '\0'


#define IF 256
#define ELSE 257
#define WHILE 258
#define RETURN 259


#define ARG 298
#define NUM 299
#define DONE 300
#define ID 301
#define INT8 302
#define INT16 303
#define INT32 304

struct entry
{ 
	char *lexptr;
	int token;
};

/*init.c*/
void init();

/*error.c*/
void error(char *m);

/*lexer.c*/
extern int lineno;
extern int tokenval; /*location in symbol table*/
extern char lexbuf[BSIZE];

int lexan();

/*symbol.c*/
extern int keywords_count;
extern struct entry symtable[];

int lookup(char s[]);
int insert(char s[], int tok);
