%option c++ 
%option yylineno 
%option noyywrap 
%option caseless 

%{ 
#define MaxLexemeSize 32
#include "token.h" 
OpType Oper = op_NONE; 
DataType Type = dt_NONE; 
%} 

newline				[\n\r]
tab					[\t]
space				[ ]
letter				[A-Za-z]
digit				[0-9]
id					{letter}({letter}|{digit})* 
digits				{digit}+ 
int_num				{digits} 
optional_fraction	([.]{int_num})?
optional_exponent	([E]([+]|[-])?{int_num})? 
real_num			{int_num}{optional_fraction}{optional_exponent}
comment				[{](.*[\n]?)*[}]
err					[!]

%%
{newline}	{ Oper = op_NONE; Type = dt_NONE; return(tc_NEWLINE);}
{tab}		{ Oper = op_NONE; Type = dt_NONE; return(tc_TAB);}
{space}		{ Oper = op_NONE; Type = dt_NONE; return(tc_SPACE);}
{comment}	{ Oper = op_NONE; Type = dt_NONE; return(tc_COMMENT);}

"="			{ Oper = op_EQ; Type = dt_OP; return(tc_RELOP);}
"<>"		{ Oper = op_NE; Type = dt_OP; return(tc_RELOP);} 
"<"			{ Oper = op_LT; Type = dt_OP; return(tc_RELOP);} 
"<="		{ Oper = op_LE; Type = dt_OP; return(tc_RELOP);} 
">="		{ Oper = op_GE; Type = dt_OP; return(tc_RELOP);} 
">"			{ Oper = op_GT; Type = dt_OP; return(tc_RELOP);}

"+"			{ Oper = op_PLUS; 	Type = dt_OP; return(tc_ADDOP);} 
"-"			{ Oper = op_MINUS; 	Type = dt_OP; return(tc_ADDOP);}
"or"		{ Oper = op_OR; 	Type = dt_OP; return(tc_ADDOP);}

"*"			{ Oper = op_MULT; 	Type = dt_OP; return(tc_MULOP);}
"/"			{ Oper = op_DIVIDE; Type = dt_OP; return(tc_MULOP);}
"div"		{ Oper = op_DIV; 	Type = dt_OP; return(tc_MULOP);}
"mod"		{ Oper = op_MOD; 	Type = dt_OP; return(tc_MULOP);}
"and"		{ Oper = op_AND; 	Type = dt_OP; return(tc_MULOP);} 

":="		{ Oper = op_NONE; Type = dt_OP; return(tc_ASSIGNOP);}

";"			{ Oper = op_NONE; Type = dt_NONE; return(tc_SEMICOL);}
":"			{ Oper = op_NONE; Type = dt_NONE; return(tc_COLON);}
","			{ Oper = op_NONE; Type = dt_NONE; return(tc_COMMA);}
"."			{ Oper = op_NONE; Type = dt_NONE; return(tc_DOT);}
".."		{ Oper = op_NONE; Type = dt_NONE; return(tc_DOTDOT);}
"("			{ Oper = op_NONE; Type = dt_NONE; return(tc_LPAREN);}
"["			{ Oper = op_NONE; Type = dt_NONE; return(tc_LBRACKET);}
")"			{ Oper = op_NONE; Type = dt_NONE; return(tc_RPAREN);}
"]"			{ Oper = op_NONE; Type = dt_NONE; return(tc_RBRACKET);}

"program"	{Oper = op_NONE; Type = dt_KEYWORD; return(tc_PROGRAM);} 
"var"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_VAR);} 
"array"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_ARRAY);} 
"of"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_OF);} 
"integer"	{Oper = op_NONE; Type = dt_KEYWORD; return(tc_INTEGER);} 
"real"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_REAL);} 
"function"	{Oper = op_NONE; Type = dt_KEYWORD; return(tc_FUNCTION);} 
"procedure"	{Oper = op_NONE; Type = dt_KEYWORD; return(tc_PROCEDURE);} 
"begin"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_BEGIN);} 
"end"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_END);} 
"if"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_IF);} 
"then"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_THEN);} 
"else"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_ELSE);} 
"while"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_WHILE);} 
"do"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_DO);} 
"not"		{Oper = op_NONE; Type = dt_KEYWORD; return(tc_NOT);} 

{int_num}	{ Oper = op_NONE; Type = dt_INTEGER;	return(tc_NUMBER);} 
{real_num}	{ Oper = op_NONE; Type = dt_REAL;		return(tc_NUMBER);} 
{id}		{ Oper = op_NONE; Type = dt_ID;	if(strlen(yytext) > MaxLexemeSize) return (tc_ERROR2); return(tc_ID);} 

<<EOF>>		{ Oper = op_NONE; Type = dt_NONE; return(tc_EOF);}
{err}|. 	{ Oper = op_NONE; Type = dt_NONE; return(tc_ERROR);}

%%

