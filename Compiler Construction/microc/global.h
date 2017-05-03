#ifndef GLOBAL_H
#define GLOBAL_H

#include "javaclass.h"
#include "bytecode.h"

typedef const char* Type;	/* a type descriptor (JVM) */

typedef struct Backpatchlist
{
	Backpatchlist(int loc)
	{
		location = loc;
		next = NULL;
	}
	int location;
	Backpatchlist* next;	
} Backpatchlist;

typedef struct Expr
{
	Backpatchlist* truelist;
	Backpatchlist* falselist;
	Type type;
	bool is_short_circuit;	
} Expr;


typedef struct Symbol
{
	const char *lexptr;
	int  token;
	int  localvar;		/* not needed any longer */
} Symbol;

typedef struct Entry
{
	struct Entry *next;	/* next in linked list or NULL */
	Symbol *sym;		/* symbol (identifier) */
	Type type;		/* its type */
	int place;		/* its place */
	struct Table *table;	/* its table (when entry is a function) */
} Entry;

typedef struct Table
{
	struct Table *prev;	/* the previous table (parent) */
	struct Entry *list;	/* linked list of entries */
	int width;		/* cumulative width of entries in table */
	int level;		/* global (0) or local (1) level */
} Table;

typedef struct SpclDec {
	Symbol* sym;
	Type type;
	
} SpclDec;


Backpatchlist *makelist(int location);
void backpatchlist(Backpatchlist* list, int location);
Backpatchlist *mergelist(Backpatchlist* list1, Backpatchlist* list2);



Symbol *lookup(const char*);
Symbol *insert(const char*, int);

// create a new table and link to previous table in hierarchy:
Table *mktable(Table *prev);
// print table
void dumptable(Table *table);
// add width information to table:
void addwidth(Table *table, int width);
// enter a declaration to the table for symbol with type and place:
Entry *enter(Table *table, Symbol *sym, Type type, int place);
// enter a procedure (function) to the table:
Entry *enterproc(Table *table, Symbol *sym, Type type, Table *newtable);
// find the level at which the variable is declared (0=global, 1=local, -1 when not found):
int getlevel(Table *table, Symbol *sym);
// find the type of a variable (NULL when not found):
Type gettype(Table *table, Symbol *sym);
// find the place of a variable:
int getplace(Table *table, Symbol *sym);

// return a new function type:
 Type mkfun(Type args, Type result);
// return a pair of types to construct argument list for functions:
 Type mkpair(Type type1, Type type2);
// return void type:
 Type mkvoid();
// return int type:
 Type mkint();
// return char type:
 Type mkchar();
// return string type:
 Type mkstr();
// return float type:
 Type mkfloat();
// if type is function, get return type (or NULL):
 Type mkret(Type type);

// check if type is void:
 int isvoid(Type type);
// check if type is int:
 int isint(Type type);
// check if type is float:
 int isfloat(Type type);
// check if type is char:
 int ischar(Type type);
// check if type is string:
 int isstr(Type type);
// check if two types are equal:
 int iseq(Type type1, Type type2);

 void init(void);
 void error(const char*);

 extern char *yytext;
 extern int yylineno;

 int yylex();
 int yyparse();
 int yyerror(const char*);

extern int errnum;

#endif
