#include <stdio.h>
#include "global.h"
#include "bytecode.h"
#include "javaclass.h"

/*
{ n = 2; m = 1000*n+arg[0]; }
<{,-1> <ID,3> <=,-1> <INT8, 2> <;,-1> <ID,4> <=,-1> <INT16,1000> <*,-1> <ID,3> <+,-1><ARG,-1> <[,-1> <INT8,0> <],-1> <;,-1> <},-1>
*/
int stmt();
void parse(), opt_stmts(), expr(), moreterms(), term(), morefactors(), factor();
void match(int tok);

int return_pcs[INT8_MAX];
int return_count = 0;
int lookahead;
struct ClassFile cf;

int main()
{
	int index1, index2, index3;
	int label1, label2;
	// set up new class file structure
	init_ClassFile(&cf);
	cf.access = ACC_PUBLIC;
	cf.name = "Code";
	cf.field_count = 0; // no fields
	cf.method_count = 1; // one method
	
	// allocate array of methods (just one "main" in our example)
	cf.methods = (struct MethodInfo*)malloc(cf.method_count * sizeof(struct MethodInfo));
	cf.methods[0].access = ACC_PUBLIC | ACC_STATIC;
	cf.methods[0].name = "main";
	cf.methods[0].descriptor = "([Ljava/lang/String;)V";
	cf.methods[0].max_stack = INT8_MAX;
	cf.methods[0].max_locals = INT8_MAX;

	// set up new bytecode buffer
	init_code();
	init();

	emit(aload_0);
	emit(arraylength);		// arg.length
	emit2(newarray, T_INT);
	emit(astore_1);			// val = new int[arg.length]
	emit(iconst_0);
	emit(istore_2);			// i = 0
	label1 = pc;			// label1:
	emit(iload_2);
	emit(aload_0);
	emit(arraylength);
	label2 = pc;
	emit3(if_icmpge, PAD);		// if i >= arg.length then goto label2
	emit(aload_1);
	emit(iload_2);
	emit(aload_0);
	emit(iload_2);
	emit(aaload);			// push arg[i] parameter for parseInt
	index1 = constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
	emit3(invokestatic, index1);	// invoke Integer.parseInt(arg[i])
	emit(iastore);			// val[i] = Integer.parseInt(arg[i])
	emit32(iinc, 2, 1);		// i++
	emit3(goto_, label1 - pc);	// goto label1
	backpatch(label2, pc - label2);	// label2:
	
	
	parse();
	/*** backpatching ***/
	int index;
	for (index = 0; index < return_count; index++)
	{
		backpatch(return_pcs[index], pc - return_pcs[index] );
	}
	
	index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
	emit3(getstatic, index2);	// get static field System.out of type PrintStream
	emit(iload_2);			// push parameter for println()
	index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
	emit3(invokevirtual, index3);	// invoke System.out.println(result)
	emit(return_);			// return
	
	// length of bytecode is in the emitter's pc variable
	cf.methods[0].code_length = pc;
	
	// must copy code to make it persistent
	cf.methods[0].code = copy_code();
	
	save_classFile(&cf);
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
		int lexeme_sym_index = lookup(lexbuf) - keywords_count + 2;
		match(ID); match('='); expr(); 	
		printf("storing in %d\n", lexeme_sym_index);
		emit2(istore, lexeme_sym_index);
		match(';');
	}
	else if (lookahead == IF)
	{
		match(IF); match('('); expr(); match(')'); 
		emit(iconst_0);
		int loc = pc;
		emit3(if_icmpeq, 0);
		stmt(); 
		backpatch(loc, pc - loc);
		match(ELSE); 
		//***missing emit "goto next statement"
		stmt();
	}
	else if (lookahead == WHILE)
	{
		match(WHILE); match('('); 
		int test = pc;
		expr(); match(')'); emit(iconst_0);
		int loc = pc;
		emit3(if_icmpeq, 0); stmt(); emit3(goto_, test - pc); backpatch(loc, pc - loc);
	}
	else if (lookahead == RETURN)
	{
		match(RETURN); expr(); emit(istore_2);
		return_pcs[return_count++] = pc;
		emit3(goto_, pc);
		match(';');
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
		match('+');	term();
		emit(iadd);
		moreterms();
	}
	else if (lookahead == '-')
	{
		match('-');	term();	
		emit(isub);
		moreterms();
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
		match('*'); factor(); 
		emit(imul);
		moreterms();
	}
	else if (lookahead == '/')
	{
		match('/'); factor(); 
		emit(idiv);
		moreterms();
	}
	else if (lookahead == '%')
	{
		match('%'); factor(); 
		emit(irem);
		moreterms();
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
		match('-'); 
		factor();
		emit(ineg);
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
			emit2(bipush, num);
		}
		else if (num < INT16_MAX)
		{
			emit3(sipush, num);
		}
		else 
		{
			emit2(ldc, constant_pool_add_Integer(&cf, num));
		}	
	}
	else if (lookahead == ID)
	{	
		int lexeme_sym_index = lookup(lexbuf) - keywords_count + 2;
		emit2(iload, lexeme_sym_index);
		match(ID);
	}
	else if (lookahead == ARG)
	{
		int t = tokenval;
		match(ARG);
		match('[');
		t = tokenval;
		match(NUM);
		if (t < INT8_MAX && t >= 0)
		{
			emit(aload_1); 
			emit2(bipush, t); 
			emit(iaload);
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