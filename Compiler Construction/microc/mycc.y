/* TO BE COMPLETED */

%{

#include "lex.yy.h"
#include "global.h"
#include "utilities.h"
#define MAXFUN 100
#define MAXFLD 100

static struct ClassFile cf;

extern int current_layer;
extern struct BreakNode* top;

/* stacks of symbol tables and offsets, depth is just 2 in C (global/local) */
static Table *tblptr[2];
static int offset[2];

/* stack pointers (index into tblptr[] and offset[]) */
static int tblsp = -1;
static int offsp = -1;

static Type return_type;

/* stack operations */
#define top_tblptr	(tblptr[tblsp])
#define top_offset	(offset[offsp])
#define push_tblptr(t)	(tblptr[++tblsp] = t)
#define push_offset(n)	(offset[++offsp] = n)
#define pop_tblptr	(tblsp--)
#define pop_offset	(offsp--)

/* flag to indicate we are compiling main's body (to differentiate 'return') */
static int is_in_main = 0;




void emit_comparison(Expr& result, u1 opcode)
{
	result.is_short_circuit = true;
	result.truelist = makelist(pc);			
	emit3(opcode, 0);
	result.falselist = makelist(pc);
	emit3(goto_, 0);
}



void emit_assignment(Symbol* lval, Expr& expr, bool duplicate = true)
{ 
	if (duplicate) emit(dup); 
	int place = getplace(top_tblptr, lval);
	Type t = gettype(top_tblptr, lval);
	if (isint(t))
	{
		if (isfloat(expr.type))emit(f2i);
		if (getlevel(top_tblptr, lval) == 0) emit3(putstatic, place);
		else emit2(istore, place);
	}
	else if (isfloat(t))
	{
		if (isint(expr.type)) emit(i2f);
		if (getlevel(top_tblptr, lval) == 0) emit3(putstatic, place);
		else emit2(fstore, place);
	}
	else if (isstr(t) && isstr(expr.type))
	{
		if (getlevel(top_tblptr, lval) == 0) emit3(putstatic, place);
		else emit2(astore, place);
	}
	else error("Type error EMIT_ASSIGNMENT");	 
}

Type load_id(Symbol * lval)
{
	int place = getplace(top_tblptr, lval);
	if (isint(gettype(top_tblptr, lval)))
	{
		if (getlevel(top_tblptr, lval) == 0)
		{
			emit3(getstatic, place);	
		}										
		else emit2(iload, place);
		return mkint();
	}
	else if (isfloat(gettype(top_tblptr, lval)))
	{
		if (getlevel(top_tblptr, lval) == 0)
		{
			emit3(getstatic, place);
		}				
		else emit2(fload, place);
		return mkfloat();
	}
	else if (isstr(gettype(top_tblptr, lval)))
	{	
		if (getlevel(top_tblptr, lval) == 0)
		{
			emit3(getstatic, place);
		}				
		else emit2(aload, place);
		return mkstr();
	}
	else error ("Type error LOAD");
	return Type();
}

%}


/* declare YYSTYPE attribute types of tokens and nonterminals */
%union
{
	Expr exp;
	Symbol *sym;  /* token value yylval.sym is the symbol table entry of an ID */
    unsigned num; /* token value yylval.num is the value of an int constant */
    float flt;    /* token value yylval.flt is the value of a float constant */
    char *str;    /* token value yylval.str is the value of a string constant */
    unsigned loc; /* location of instruction to backpatch */  
	Type typ;
	SpclDec val;
}

/* declare ID token and its attribute type */
%token <sym> ID 

/* Declare INT tokens (8 bit, 16 bit, 32 bit) and their attribute type 'num' */
%token <num> INT8 INT16 INT32

/* Declare FLT token for literal floats */
%token <flt> FLT

/* Declare STR token for literal strings */
%token <str> STR

/* declare tokens for keywords */
/* Note: install_id() returns Symbol* for keywords and identifiers */
%token <sym> BREAK CHAR DO ELSE FLOAT FOR IF INT MAIN RETURN VOID WHILE

/* declare operator tokens */
%token PA NA TA DA MA AA XA OA LA RA OR AN EQ NE LE GE LS RS AR PP NN
%right '=' PA NA TA DA MA AA XA OA LA RA
%left OR
%left AN
%left '|'
%left '^'
%left '&'
%left EQ NE LE '<' GE '>'
%left LS RS
%left '+' '-'
%left '*' '/' '%'
%right '!' '~'
%left '.' AR
%nonassoc PP NN 

/* Declare attribute types for marker nonterminals, such as K L M and N */
/* TODO: TO BE COMPLETED WITH ADDITIONAL NONMARKERS AS NECESSARY */
%type <loc> K L M N X

%type <typ> type list args

%type <num> ptr

%type <exp> expr SCEXP

%type <sym> ftype SID 

%type <val> SDECL

%%

prog	: Mprog exts	{ addwidth(top_tblptr, top_offset);
			  pop_tblptr;
			  pop_offset;
			}
	;

Mprog	: /* empty */	{ 
		
				push_tblptr(mktable(NULL));
			  push_offset(0);
			}
	;

exts	: exts func
	| exts decl
	| /* empty */
	;

func	: MAIN '(' ')' Mmain block
			{ // need a temporary table pointer
			  Table *table;
			  // the type of main is a JVM type descriptor
			  Type type = mkfun("[Ljava/lang/String;", "V");
			  // emit the epilogue part of main()
			  emit3(getstatic, constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;"));
			  emit(iload_2);
			  emit3(invokevirtual, constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V"));
			  emit(return_);
			  // method has public access and is static
			  cf.methods[cf.method_count].access = (enum access_flags)(ACC_PUBLIC | ACC_STATIC);
			  // method name is "main"
			  cf.methods[cf.method_count].name = "main";
			  // method descriptor of "void main(String[] arg)"
			  cf.methods[cf.method_count].descriptor = type;
			  // local variables
			  cf.methods[cf.method_count].max_locals = top_offset;
			  // max operand stack size of this method
			  cf.methods[cf.method_count].max_stack = 100;
			  // length of bytecode is in the emitter's pc variable
			  cf.methods[cf.method_count].code_length = pc;
			  // must copy code to make it persistent
			  cf.methods[cf.method_count].code = copy_code();
			  if (!cf.methods[cf.method_count].code)
				error("Out of memory");
			  // advance to next method to store in method array
			  cf.method_count++;
			  if (cf.method_count > MAXFUN)
			  	error("Max number of functions exceeded");
			  // add width information to table
			  addwidth(top_tblptr, top_offset);
			  // need this table of locals for enterproc
			  table = top_tblptr;
			  // exit the local scope by popping
			  pop_tblptr;
			  pop_offset;
			  // enter the function in the global table
			  enterproc(top_tblptr, $1, type, table);
			  cf.access = ACC_PUBLIC;
			}
	|   SDECL block 
	{
		cf.methods[cf.method_count].access = (enum access_flags)(ACC_PUBLIC | ACC_STATIC);
		cf.methods[cf.method_count].name = $1.sym->lexptr;
		cf.methods[cf.method_count].descriptor = $1.type;
		cf.methods[cf.method_count].code_length = pc; // the code size
		cf.methods[cf.method_count].code = copy_code();
		
		if (!cf.methods[cf.method_count].code) error("Out of memory");
		
		cf.methods[cf.method_count].max_stack = 100;
		cf.methods[cf.method_count].max_locals = top_offset + 1 ;
		cf.method_count++;
		if (cf.method_count > MAXFUN) error("Max number of functions exceeded");
	}
;

ftype : type ptr ID '('{
		if (ischar($1) && $2) return_type = mkstr();
		else return_type = $1;
		$$ = $3;
	}
;

SDECL : ftype Margs args ')'
	{
		
		Type type = mkfun($3, return_type);
		$$.sym = $1;
		$$.type = type;
		pop_tblptr;
		pop_offset;
		addwidth(top_tblptr, top_offset);
		// need this table of locals for enterproc
		Table* table = top_tblptr;	
		// enter the function in the global table
		enterproc(top_tblptr, $1, type, table);			
		++tblsp;
		++offsp;
		
		
		}		
;

Mmain	:		{ int label1, label2;
			  Table *table;
			  // create new table for local scope of main()
			  table = mktable(top_tblptr);
			  // push it to create new scope
			  push_tblptr(table);
			  // for main(), we must start with offset 3 in the local variables of the frame
			  push_offset(3);
			  // init code block to store stmts
			  init_code();
			  // emit the prologue part of main()
			  emit(aload_0);
			  emit(arraylength);
			  emit2(newarray, T_INT);
			  emit(astore_1);
			  emit(iconst_0);
			  emit(istore_2);
			  label1 = pc;
			  emit(iload_2);
			  emit(aload_0);
			  emit(arraylength);
			  label2 = pc;
			  emit3(if_icmpge, PAD);
			  emit(aload_1);
			  emit(iload_2);
			  emit(aload_0);
			  emit(iload_2);
			  emit(aaload);
			  emit3(invokestatic, constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I"));
			  emit(iastore);
			  emit32(iinc, 2, 1);
			  emit3(goto_, label1 - pc);
			  backpatch(label2, pc - label2);
			  // global flag to indicate we're in main()
			  is_in_main = 1;
			}
	;

Margs	:	{ 
			  Table* table = mktable(top_tblptr);
			  push_tblptr(table);
			  push_offset(0);  
			  init_code();
			  is_in_main = 0;
			}
	;

block	: '{' decls stmts '}'
	;

decls	: decls decl
	| /* empty */
	;

decl	: list ';'
	;

type	: VOID		{ $$ = mkvoid(); }
	| INT		{ $$ = mkint(); }
	| FLOAT		{ $$ = mkfloat(); }
	| CHAR		{ $$ = mkchar(); }
	;

args	: args ',' type ptr ID{
				if ($4 && ischar($3))
					enter(top_tblptr, $5, mkstr(), top_offset++);
				else
					enter(top_tblptr, $5, $3, top_offset++);
				$$ = mkpair($1, $3);
			}
	| type ptr ID	{ 
				if ($2 && ischar($1))
					enter(top_tblptr, $3, mkstr(), top_offset++);
				else
					enter(top_tblptr, $3, $1, top_offset++);
				$$ = $1;
			}
	;

list	: list ',' ptr ID    { 
				if (top_tblptr->level == 0)
				{
					cf.fields[cf.field_count].access = ACC_STATIC;
					cf.fields[cf.field_count].name = $4->lexptr;
					cf.fields[cf.field_count].descriptor = $1;
					cf.field_count++;
					enter(top_tblptr, $4, $1, constant_pool_add_Fieldref(&cf, cf.name, $4->lexptr, $1));					
				}
				else
				{
					if ($3 && ischar($1))
						enter(top_tblptr, $4, mkstr(), top_offset++);
					else
						enter(top_tblptr, $4, $1, top_offset++);
				}
			  $$ = $1;
			}
	| type ptr ID	{ 
					if (top_tblptr->level == 0)
					{	
						cf.fields[cf.field_count].access = ACC_STATIC;
						cf.fields[cf.field_count].name = $3->lexptr;
						cf.fields[cf.field_count].descriptor = $1;
						cf.field_count++;
						enter(top_tblptr, $3, $1, constant_pool_add_Fieldref(&cf, cf.name, $3->lexptr, $1));
					}
				if ($2 && ischar($1))
					enter(top_tblptr, $3, mkstr(), top_offset++);
				else
					enter(top_tblptr, $3, $1, top_offset++);		
			  $$ = $1;
			}
	;

ptr	: /* empty */	{ $$ = 0; }
	| '*'		{ $$ = 1; }
	;

stmts   : stmts stmt
        | /* empty */
        ;

/* TASK 1: TO BE COMPLETED: */
stmt    : ';'
        | expr ';'      { emit(pop); }
        | IF '(' expr ')' L stmt
						{ 
							if (!$3.is_short_circuit) error("Not short circuit");
							backpatchlist($3.truelist, $5);
							backpatchlist($3.falselist, pc);
						}
        | IF '(' expr ')' L stmt ELSE N L stmt
					    { 
							if (!$3.is_short_circuit) error("Not short circuit");
							backpatchlist($3.truelist, $5);
							backpatch($8, pc - $8);
							backpatchlist($3.falselist, $9);						  
						}
        | X WHILE L '('  expr ')' L stmt N
                        { 
							if (!$5.is_short_circuit) error("Not short circuit");
							backpatchlist($5.truelist , $7);
							backpatchlist($5.falselist, pc);
							backpatch($9, $3 - $9);
							while(true)
							{
								int breakPC = pop_top(current_layer);
								if (breakPC == -1) break;
								backpatch(breakPC, pc - breakPC);
							}
							current_layer--;
						}
		| X DO L stmt WHILE '(' expr ')' ';' 
                        { 
							if (!$7.is_short_circuit) error("Not short circuit");
							backpatchlist($7.truelist, $3);
							backpatchlist($7.falselist, pc); 
							while(true)
							{
								int breakPC = pop_top(current_layer);
								if (breakPC == -1) break;
								backpatch(breakPC, pc - breakPC);
							}
							current_layer--;
						}
        | X FOR '(' expr P ';' L  expr ';' L expr P N ')' L stmt N 
                        {
							if (!$8.is_short_circuit) error("Not short circuit");
							backpatchlist($8.truelist, $15);
							backpatchlist($8.falselist, pc);
							backpatch($13, $7 - $13); //after expression update eg i++ goto conditional
							backpatch($17, $10 - $17); //upon reaching the end of the for loop go to the update
							while(true)
							{
								int breakPC = pop_top(current_layer);
								if (breakPC == -1) break;
								backpatch(breakPC, pc - breakPC);
							}
							current_layer--;
						}
        | RETURN expr ';' {
				if (is_in_main)
				{
					emit(istore_2); 
				}
				else if (isint(return_type) && isint($2.type))
					emit(ireturn);
				else if (isfloat(return_type) && isfloat($2.type))
					emit(freturn);
				else if (isstr(return_type) && isstr($2.type))
					emit(areturn);
				else error("Type error RETURN");
			}
        | BREAK ';'
					{ push_top(pc); emit3(goto_, 0); }
        | '{' stmts '}'
        | error ';'     { yyerrok; }
        ;

exprs	: exprs ',' expr
	| expr
	;

expr    : ID  '=' expr { 
			emit_assignment($1, $3);
			$$.type = $3.type;
			$$.is_short_circuit = false;
		}
        | SID  PA  expr { 
			Type t = gettype(top_tblptr, $1);
			if (isint(t))
			{
				if (isfloat($3.type)) emit(f2i);				
				emit(iadd);
			}
			else if (isfloat(t))
			{
				if (isint($3.type)) emit(i2f);
				emit(fadd);
			}
			else error("Type error PA");
			$$.type = $3.type = t;
			emit_assignment($1, $3);
			$$.is_short_circuit = false;	
						}
        | SID   NA  expr { 
			Type t = gettype(top_tblptr, $1);
			if (isint(t))
			{
				if (isfloat($3.type)) emit(f2i);
				emit(isub);
			}
			else if (isfloat(t))
			{
				if (isint($3.type)) emit(i2f);
				emit(fsub);
			}
			else error("Type error NA");
			$$.type = $3.type = t;
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
				
		} // -=
        | SID   TA  expr { 
			Type t = gettype(top_tblptr, $1);
			if (isint(t))
			{
				if (isfloat($3.type)) emit(f2i);
				emit(imul);
			}
			else if (isfloat(t))
			{
				if (isint($3.type)) emit(i2f);
				emit(fmul);
			}
			else error("Type error TA");
			$$.type = $3.type = t;
			emit_assignment($1, $3);
			$$.is_short_circuit = false;	
		}
        | SID   DA  expr {
			Type t = gettype(top_tblptr, $1);
			if (isint(t))
			{
				if (isfloat($3.type)) emit(f2i);
				emit(idiv);
			}
			else if (isfloat(t))
			{
				if (isint($3.type)) emit(i2f);
				emit(fdiv);
			}
			else error("Type error DA");
			$$.type = $3.type = t;
			emit_assignment($1, $3);
			$$.is_short_circuit = false;	
		} 
        | SID   MA  expr {
			Type t = gettype(top_tblptr, $1);
			if (isint(t))
			{
				if (isfloat($3.type)) emit(f2i);
				emit(irem);
			}
			else if (isfloat(t))
			{
				if (isint($3.type)) emit(i2f);
				emit(frem);
			}
			else error("Type error MA");
			$$.type = $3.type = t;
			emit_assignment($1, $3);
			$$.is_short_circuit = false;	
		} 
        | SID   AA  expr {
			if (!isint(gettype(top_tblptr, $1)) || !isint($3.type)) error("Type error AA");
			emit(iand);
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
			$$.type = $3.type;		
		} 
        | SID   XA  expr { //^=
			if (!isint(gettype(top_tblptr, $1)) || !isint($3.type)) error("Type error XA");
			emit(ixor);
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
			$$.type = $3.type;		
		} 
        | SID   OA  expr{ //|=
			if (!isint(gettype(top_tblptr, $1)) || !isint($3.type)) error("Type error OA");
			emit(ior);
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
			$$.type = $3.type;		

		} 
        | SID   LA  expr { //<<=
			if (!isint(gettype(top_tblptr, $1)) || !isint($3.type)) error("Type error ishl");
			emit(ishl);
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
			$$.type = $3.type;		
		} 
        | SID   RA  expr { // >>=
			if (!isint(gettype(top_tblptr, $1)) || !isint($3.type)) error("Type error ishr");
			emit(ishr);
			emit_assignment($1, $3);
			$$.is_short_circuit = false;
			$$.type = $3.type;		
		} 
		
        | SCEXP OR L expr { 
			if (!$4.is_short_circuit)
			{
				$4.is_short_circuit = true;
				$4.truelist = makelist(pc);			
				emit3(ifne, 0);
				$4.falselist = makelist(pc);
				emit3(goto_, 0);
			}
			backpatchlist($1.falselist, $3);
			$$.truelist = mergelist($1.truelist, $4.truelist);
			$$.falselist = $4.falselist;
		}
        | SCEXP AN L expr { 
			if (!$4.is_short_circuit)
			{
				$4.is_short_circuit = true;
				$4.truelist = makelist(pc);			
				emit3(ifne, 0);
				$4.falselist = makelist(pc);
				emit3(goto_, 0);
			}
			backpatchlist($1.truelist, $3);
			$$.truelist = $4.truelist;
			$$.falselist = mergelist($1.falselist, $4.falselist);
		}
		
        | expr '|' expr { 
			if (!isint($1.type) || !isint($3.type))error("Type error |");				
			emit(ior);
			$$.type = $1.type;
			$$.is_short_circuit = false;	
		}
        | expr '^' expr { 
			if (!isint($1.type) || !isint($3.type))error("Type error ^");	
			emit(ixor);
			$$.type = $1.type;
			$$.is_short_circuit = false;
		}
        | expr '&' expr { 
			if (!isint($1.type) || !isint($3.type))error("Type error &");
			emit(iand);
			$$.type = $1.type;
			$$.is_short_circuit = false;
		} 
		| expr LS expr { 
			if (!isint($1.type) || !isint($3.type))error("Type error <<");
			emit(ishl);
			$$.type = $1.type;
			$$.is_short_circuit = false;
		}
        | expr RS  expr{ 
			if (!isint($1.type) || !isint($3.type)) error("Type error >>");
			emit(ishr);
			$$.type = $1.type;
			$$.is_short_circuit = false;
		} 
        | expr EQ expr  { emit_comparison($$, if_icmpeq);   }
        | expr NE  expr { emit_comparison($$, if_icmpne);	}
        | expr '<' expr { emit_comparison($$, if_icmplt);	}
        | expr '>' expr { emit_comparison($$, if_icmpgt);   }									
        | expr LE  expr { emit_comparison($$, if_icmple);	}
        | expr GE  expr { emit_comparison($$, if_icmpge);   }
		
        | expr '+' expr { 
			if (iseq($1.type, $3.type))
			{	
				if (isint($1.type)) emit(iadd);
				else emit(fadd);
			}
			else error("Type error +");
			$$.type = $1.type;
			$$.is_short_circuit = false;
		}
		
        | expr '-' expr { 	
			if (iseq($1.type, $3.type))
			{	
				if (isint($1.type)) emit(isub);
				else emit(fsub);
			}
			else error("Type error -");
			$$.type = $1.type; 
			$$.is_short_circuit = false;
		}
		
        | expr '*' expr{ 	
			if (iseq($1.type, $3.type))
			{	
				if (isint($1.type)) emit(imul);
				else emit(fmul);
			}
			else error("Type error *");
			$$.type = $1.type; 
			$$.is_short_circuit = false;
		} 
		
        | expr '/' expr{ 			
			if (iseq($1.type, $3.type))
			{	
				if (isint($1.type)) emit(idiv);
				else emit(fdiv);
			}
			else error("Type error /");
			$$.type = $1.type; 
			$$.is_short_circuit = false;
		}
       
	   | expr '%' expr{ 			
			if (iseq($1.type, $3.type))
			{	
				if (isint($1.type)) emit(irem);
				else emit(frem);
			}
			else error("Type error %");
			$$.type = $1.type; 
			$$.is_short_circuit = false;
		} 
		
        | '!' expr      { 
							if (!$2.is_short_circuit)
							{
								$2.is_short_circuit = true;
								$2.truelist = makelist(pc);			
								emit3(ifne, 0);
								$2.falselist = makelist(pc);
								emit3(goto_, 0);
							}
							$$ = $2;
							$$.truelist = $2.falselist;
							$$.falselist = $2.truelist;		
						}
        | '~' expr      { 
							if (!isint($2.type))error("Type error ~");		
							emit2(ldc, constant_pool_add_Integer(&cf, 2147483647)); 
							emit(ixor);
							$$.type = $2.type;
							$$.is_short_circuit = false;
		
						 }
        | '+' expr %prec '!' /* '+' at same precedence level as '!' */
                        { $$ = $2;}
        | '-' expr %prec '!' /* '-' at same precedence level as '!' */
                        { $$ = $2; 
						if (isint($$.type)) emit(ineg); 
						else emit(fneg);
						}
        | '(' expr ')'   {
							$$ = $2;
						 }
        | '$' INT8      { // check that we are in main()	
			  if (is_in_main)
			  {	emit(aload_1);
				emit2(bipush, $2);
				emit(iaload);
			  }
			  else
				error("invalid use of $# in function");
			$$.type = mkint();
			$$.is_short_circuit = false;
			}
		| PP ID         {
			if (!isint(gettype(top_tblptr, $2))) error("Type error ++x");
			int place = getplace(top_tblptr, $2);
			if (getlevel(top_tblptr, $2) == 0) emit3(getstatic, place);			
			else emit2(iload, place);
			$$.type = mkint();
			$$.is_short_circuit = false;
			emit2(bipush, 1); 
			emit(iadd); 
			emit_assignment($2, $$);		
			}
        | NN ID         { 
			if (!isint(gettype(top_tblptr, $2))) error("Type error --x");
			int place = getplace(top_tblptr, $2);
			if (getlevel(top_tblptr, $2) == 0) emit3(getstatic, place);			
			else emit2(iload, place);
			$$.type = mkint();
			$$.is_short_circuit = false;
			emit2(bipush, 1); 
			emit(isub); 
			emit_assignment($2, $$);				
			}
        | ID PP         { 
			if (!isint(gettype(top_tblptr, $1))) error("Type error x++");
			int place = getplace(top_tblptr, $1);
			if (getlevel(top_tblptr, $1) == 0) emit3(getstatic, place);			
			else emit2(iload, place);
			$$.type = mkint();
			$$.is_short_circuit = false;
			emit(dup);
			emit2(bipush, 1); 
			emit(iadd); 
			emit_assignment($1, $$, false);		
		}
        | ID NN         { 
			if (!isint(gettype(top_tblptr, $1))) error("Type error x--");
			int place = getplace(top_tblptr, $1);
			if (getlevel(top_tblptr, $1) == 0) emit3(getstatic, place);			
			else emit2(iload, place);
			$$.type = mkint();
			$$.is_short_circuit = false;
			emit(dup);
			emit2(bipush, 1); 
			emit(isub); 
			emit_assignment($1, $$, false);		
		
		}
        | ID            { 
						
							$$.type = load_id($1);
							$$.is_short_circuit = false;
						}
        | INT8          { 
			emit2(bipush, $1); 
			$$.type = mkint();
			$$.is_short_circuit = false;
		}
        | INT16         { 
			emit3(sipush, $1); 
			$$.type = mkint();
			$$.is_short_circuit = false;
		
		}
        | INT32         { 
			emit2(ldc, constant_pool_add_Integer(&cf, $1)); 
			$$.type = mkint();
			$$.is_short_circuit = false;
		}
		| FLT		{ 
			emit2(ldc, constant_pool_add_Float(&cf, $1)); 
			$$.type = mkfloat();
			$$.is_short_circuit = false;	
			
		}
		| STR		{ 
			emit2(ldc, constant_pool_add_String(&cf, constant_pool_add_Utf8(&cf, $1))); 
			$$.type = mkstr();
			$$.is_short_circuit = false;		
		}
		| ID '(' exprs ')'
			{ 
			  //issues calling itself out of scope
			  
				int tbp_before =  tblsp;
				int off_before = offsp;
				tblsp = 0, offsp = 0;
			  //int constant_pool_add_Methodref(struct ClassFile *cf, const char *class_name, const char *method_name, const char *descriptor);
			  emit3(invokestatic, constant_pool_add_Methodref(&cf, cf.name, $1->lexptr, gettype(top_tblptr, $1)));
			  tblsp = tbp_before;
			  offsp = off_before;
			  $$.type = mkret(gettype(top_tblptr, $1));
			}
        ;

K       : /* empty */   { $$ = pc; emit3(ifne, 0); }
        ;

L       : /* empty */   { $$ = pc; }
        ;

M       : /* empty */   { $$ = pc;	/* location of inst. to backpatch */
			  emit3(ifeq, 0);
			}
        ;

N       : /* empty */   { $$ = pc;	/* location of inst. to backpatch */
			  emit3(goto_, 0);
			}
        ;

P       : /* empty */   { emit(pop); }
        ;
		
X	    : /* empty */  { current_layer++; }

SID     : ID
		{
			
				load_id($1);
				$$ = $1;
		}
		;
SCEXP    : expr {
		if (!$1.is_short_circuit)
		{
			$$.is_short_circuit = true;
			$$.truelist = makelist(pc);			
			emit3(ifne, 0);
			$$.falselist = makelist(pc);
			emit3(goto_, 0);
		}
		else{
			$$ = $1;
		}
}


%%

int main(int argc, char **argv)
{
	// init the compiler
	init();

	// set up a new class file structure
	init_ClassFile(&cf);

	// class has public access
	cf.access = ACC_PUBLIC;

	// class name is "Code"
	cf.name = "Code";

	// field counter (incremented for each field we add)
	cf.field_count = 0;

	// method counter (incremented for each method we add)
	cf.method_count = 0;

	// allocate an array of MAXFLD fields
	cf.fields = (struct FieldInfo*)malloc(MAXFLD * sizeof(struct FieldInfo));

	// allocate an array of MAXFUN methods
	cf.methods = (struct MethodInfo*)malloc(MAXFUN * sizeof(struct MethodInfo));

	if (!cf.methods)
		error("Out of memory");

	if (argc > 1)
		if (!(yyin = fopen(argv[1], "r")))
			error("Cannot open file for reading");

	if (yyparse() || errnum > 0)
		error("Compilation errors: class file not saved");

	fprintf(stderr, "Compilation successful: saving %s.class\n", cf.name);

	// save class file
	save_classFile(&cf);

	return 0;
}

