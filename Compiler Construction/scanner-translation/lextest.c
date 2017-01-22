#include <stdio.h>
#include "global.h"

/*
{ n = 2; m = 1000*n+arg[0]; }
<{,-1> <ID,3> <=,-1> <INT8, 2> <;,-1> <ID,4> <=,-1> <INT16,1000> <*,-1> <ID,3> <+,-1><ARG,-1> <[,-1> <INT8,0> <],-1> <;,-1> <},-1>
*/
int stmt();
void parse(), opt_stmts(), expr(), moreterms(), term(), morefactors(), factor();
void match(int tok);

int lookahead;
int main()
{
	init();
	parse();
	return 0;
}

void parse()
{
	lookahead = lexan();
	stmt();
	match(DONE);
}

void match(int tok)
{
	if (lookahead <= 255)
	{
		printf("<%c,%d>\n", lookahead, tokenval);
	}
	if (lookahead == tok)
	{
		lookahead = lexan();
	}
	else
	{
		error("match mismatch");
	}
}

int stmt()
{
	if (lookahead == '{')
	{
		match('{'); opt_stmts(); match('}');
	}
	else if (lookahead == ID)
	{
		//int lexeme_sym_index = tokenval;
		printf("<ID,%d>\n", lookup(lexbuf) - keywords_count + 2); /* WTF - offset from keywords? */	
		match(ID); match('='); expr(); match(';');
	}
	else if (lookahead == IF)
	{
		match(IF); match('('); expr();match(')'); stmt(); match(ELSE); stmt();
	}
	else if (lookahead == WHILE)
	{
		match(WHILE); match('('); expr(); match(')'); stmt();
	}
	else if (lookahead == RETURN)
	{
		match(RETURN); expr(); match(';');
	}
	else
	{
		return NONE;
	}
	return 0;
}
void opt_stmts()
{
	if (stmt() != NONE)
	{
		opt_stmts();
	}
}

void expr()
{
	term(); moreterms();
}

void moreterms()
{
	if (lookahead == '+')
	{
		match('+');	term();	moreterms();
	}
	else if (lookahead == '-')
	{
		match('-');	term();	moreterms();
	}
	else
	{
		
	}
}

void term()
{
	factor(); morefactors();
}

void morefactors()
{
	if (lookahead == '*')
	{
		match('*'); factor(); moreterms();
	}
	else if (lookahead == '/')
	{
		match('/'); factor(); moreterms();
	}
	else if (lookahead == '%')
	{
		match('%'); factor(); moreterms();
	}
	else
	{
		
	}
}

void factor()
{
	if (lookahead == '(')
	{
		match('('); expr();	match(')');
	}
	else if (lookahead == '-')
	{
		match('-'); factor();
	}
	else if (lookahead == NUM)
	{
		int num = tokenval;
		match(NUM);
		if (num < 0)
		{
			error("non-negative integer expected");
		}
		if (num < INT8_MAX)
		{
			printf("<INT8,%d>\n", num);
		}
		else if (num < INT16_MAX)
		{
			printf("<INT16,%d>\n", num);
		}
		else 
		{
			printf("<INT32,%d>\n", num);
		}	
	}
	else if (lookahead == ID)
	{	
		//int lexeme_sym_index = tokenval;
		printf("<ID,%d>\n", lookup(lexbuf) - keywords_count + 2); /* WTF - offset from keywords? */
		match(ID);
	}
	else if (lookahead == ARG)
	{
		int t = tokenval;
		match(ARG);
		printf("<ARG,%d>\n", t);
		match('[');
		t = tokenval;
		match(NUM);
		if (t < INT8_MAX && t >= 0)
		{
			printf("<INT8,%d>\n", t);
		}
		else
		{
			error("integer constant out of range");
		}
		match(']');
	}
	else
	{
		error("factor syntax");
	}
}