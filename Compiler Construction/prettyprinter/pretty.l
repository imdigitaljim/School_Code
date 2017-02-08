%top{
	#include <stdio.h>
	#include <stdlib.h>
	#define INDENT (4)
	#define KEYWORD 256
	#define ID 257
	#include <string>
	#include <vector>
	#include <unordered_map>
	
	using namespace std;
%}

%class{
	int line;
	int column;
	int paren;
	// symbol table to store identifier names with line numbers
	unordered_map<string, int> symbol_table;
	private: 
		void init_table();
	public:
		void write_indent();
		void write_html_char(int c);
		void write_html();
		void write_sep();
		void write_char();
		void write_string();
		void write_oct();
		void write_hex();
		void write_int();
		void write_fp();
		void write_id();
		void write_begin();
		void write_end();
		void write_open();
		void write_close();
		void write_bopen();
		void write_bclose();
		void write_comment();
		void write_inline();
		void write_directive();
		void write_op();
		void write_formatting();
%}

%init{
	line = 1;
	column = 4;
	paren = 0;
	write_indent();
	init_table();
	
%}

QUOTE	[']
DITTO	["]
DIGIT	[0-9]
OCT		[0-7]
EXP		[eE][+\-]?{DIGIT}+
HEX		{DIGIT}|[a-fA-F]
ALPHA	[a-zA-Z_]
OPWEQ	("<<"|">>"|"^"|"|"|"&"|"+"|"-"|"/"|"*"|"%"|"!"|"="|">"|"<")
 		
%%
{QUOTE}([^{QUOTE}]|\\{QUOTE})*{QUOTE} 						{ write_char(); 	}
{DITTO}([^{DITTO}]|\\{DITTO})*{DITTO}						{ write_string();  	}
0{OCT}+ 													{ write_oct();		}
0[Xx]{HEX}+													{ write_hex();		}
{DIGIT}+													{ write_int();		}
{DIGIT}*\.{DIGIT}*{EXP}?									{ write_fp();		}
{ALPHA}({ALPHA}|{DIGIT})*									{ write_id();		}
"{"															{ write_begin();	}
"}"															{ write_end();		}
"("															{ write_open();		}
")"															{ write_close();	}
{OPWEQ}[=]?|"++"|"--"|"||"|"&&"|"~"|","|"?"|":"|"."|"->"|","	{ write_op();	}
"["															{ write_bopen();	}
"]"															{ write_bclose();	}
";"															{ write_sep();		}
"/*"(.|\n)*"*/"												{ write_comment();	}
"//".*														{ write_inline(); 	}
^"#".*														{ write_directive();}
[ \t\v\n\r\f]+												{ write_formatting();}
.															{ fprintf(stderr, "Error: <%s> on line: %d\n", yytext, line);	}

%%

int main()
{
	printf("<html><pre>\n");
	yyFlexLexer().yylex();
	printf("\n</pre></html>\n");
	return 0;
}

void yyFlexLexer::init_table()
{
	vector<string> keywords = {
	"auto",	"break", "case", "char",
	"const", "continue", "default",
	"do", "double", "else",	"enum",
	"extern", "float", "for", "goto",
	"if", "int","long",	"register",
	"return", "short","signed",
	"sizeof","static", "struct",
	"switch", "typedef", "union",
	"unsigned",	"void",	"volatile",
	"while"	};

	for (size_t i = 0; i < keywords.size(); i++)
	{
		symbol_table[keywords[i]] = KEYWORD;
	}
}


void yyFlexLexer::write_formatting()
{
	char format = yytext[0];
	switch(format)
	{
		case '\n': case '\r': write_indent(); break;	
		default:
			break;
	}
}



void yyFlexLexer::write_indent()
{
	printf("\n%-*d", column, line++);
}

void yyFlexLexer::write_html_char(int c)
{
	switch (c)
	{ 
		case '<': printf("&lt;"); break;
		case '>': printf("&gt;"); break;
		case '"': printf("&quot;"); break;
		case '&': printf("&amp;"); break;
		case '\'': printf("&apos;"); break; 
		case '\n': case '\r': case '\v': case '\t': case '\f': break; // we don't want newlines to show up in HTML PRE blocks
		default: putchar(c);
	}
}

void yyFlexLexer::write_html()
{
	char *s = yytext;
	while (*s)
		write_html_char(*s++);
}

// output ';', i.e. statement terminator or for()-expression separator
void yyFlexLexer::write_sep()
{
	write_html();
	if (!paren)
		write_indent();
	else
		putchar(' ');
}


void yyFlexLexer::write_char()
{
	printf("<span style=\"text-decoration: underline; color: black;\"><span style=\"color: brown\">");
	write_html();
	printf("</span></span>");
	putchar(' ');
}
void yyFlexLexer::write_string()
{
	printf("<span style=\"color: red;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_oct()
{
	printf("<span style=\"font: italic; color: brown;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_hex()
{
	printf("<span style=\"font: italic; color: brown;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_int()
{
	printf("<span style=\"color: brown;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_fp()
{
	printf("<span style=\"color: brown;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}

void yyFlexLexer::write_op()
{
	printf("<span style=\"color: black; font-weight: bold;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}

void yyFlexLexer::write_id()
{
	string lexeme = yytext;
	auto it = symbol_table.find(lexeme);
	if (it == symbol_table.end())
	{
		symbol_table[lexeme] = ID;
		printf("<a name=\"%s\" style=\"text-decoration: underline; color: black;\"><span style=\"color: blue;\">", lexeme.c_str());
		write_html();
		printf("</span></a>");
		putchar(' ');
	}
	else if (it->second == KEYWORD) 
	{
		printf("<span style=\"color: blue; font-weight: bold;\">");
		write_html();
		printf("</span>");
		putchar(' ');
	}
	else
	{
		printf("<a href=\"#%s\" style=\"text-decoration: underline; color: black;\"><span style=\"color: blue;\">", lexeme.c_str());
		write_html();
		printf("</span></a>");
		putchar(' ');
	}

}

// begin {}-block
void yyFlexLexer::write_begin()
{
	write_indent();
	write_html();
	column += INDENT;
	write_indent();
}

// end {}-block
void yyFlexLexer::write_end()
{
	column -= INDENT;
	write_indent();
	write_html();
	write_indent();
}

// start opening paren
void yyFlexLexer::write_open()
{
	write_html();
	putchar(' ');
	paren++;
}
// close paren
void yyFlexLexer::write_close()
{
	write_html();
	putchar(' ');
	paren--;
}

void yyFlexLexer::write_bopen()
{
	printf("<span style=\"color: black; font-weight: bold;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_bclose()
{
	printf("<span style=\"color: black; font-weight: bold;\">");
	write_html();
	printf("</span>");
	putchar(' ');
}
void yyFlexLexer::write_comment()
{
	printf("<span style=\"color: green;\">");
	write_html();
	printf("</span>");
}
void yyFlexLexer::write_inline()
{
	printf("<span style=\"color: green;\">");
	write_html();
	printf("</span>");
}

void yyFlexLexer::write_directive()
{
	printf("<span style=\"color: magenta; font-weight: bold;\">");
	write_html();
	printf("</span>");
}