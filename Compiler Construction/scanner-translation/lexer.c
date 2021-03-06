/**** lexer.c ****/
#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

int lexan() //returns tokens it found
{
	int t;
	while (1)
	{ 
		t = getchar();
		if (t== ' ' || t == '\t') continue;
		else if (t == '\n') lineno = lineno + 1;
		else if (isdigit(t))
		{ 
			ungetc(t, stdin);
			scanf("%d", &tokenval);
			return NUM;
		}
		else if (isalpha(t) || t == '_')
		{ 
			int p, b = 0;
			while (isalnum(t) || t == '_')
			{ 
				lexbuf[b] = t;
				t = getchar();
				b = b + 1;
				if (b >= BSIZE) error("compiler error");
			}
			lexbuf[b] = EOS;
			if (t != EOF) ungetc(t, stdin);
			if(strcmp(lexbuf,"arg") == 0)
			{
				tokenval = NONE;
				return ARG;
			}				
			p = lookup(lexbuf);
			if (p == 0)
			{ 				
				p = insert(lexbuf, ID);
			}
			tokenval = p;
			return symtable[p].token;
		}
		else if (t == EOF) return DONE;
		else
		{ 
			tokenval = NONE;
			return t;
		}
	}
}