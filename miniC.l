%option noyywrap
%option yylineno
%option caseless
%x comment

%{
    #include <stdio.h>
    #include "main.cpp"
    enum yytokentype{
    TK_ELSE = 258,
    TK_FOR = 259,
    TK_WHILE = 260,
    TK_VOID = 261,
    TK_RETURN = 262,
    TK_INT_TYPE = 263,
    TK_FLOAT_TYPE = 264,
    TK_BREAK = 265,
    TK_CONTINUE = 266,
    TK_IF = 267,
    TK_PRINTF = 268,
    TK_LIT_STRING = 269,
    TK_ID = 270,
    TK_LIT_INT = 271,
    TK_LIT_FLOAT =272,
    TK_PLUS_EQUAL =273,
    TK_MINUS_EQUAL =274,
    TK_PLUS_PLUS =275,
    TK_MINUS_MINUS =276,
    TK_OR = 277,
    TK_AND = 278,
    TK_EQUAL = 279,
    TK_NOT_EQUAL = 280,
    TK_GREATER_OR_EQUAL = 281,
    TK_LESS_OR_EQUAL = 282
    };

    int yylval;
%}

DIGIT [0-9]

%%

[\t \r \n] { /* nada */ }
"/*" {BEGIN(comment);}
")" { return ')'; }
"if" { return TK_IF; }
"else" { return TK_ELSE; }
"for" { return TK_FOR; }
"while" { return TK_WHILE; }
"void" { return TK_VOID; }
"return" { return TK_RETURN; }
"int" { return TK_INT_TYPE; }
"float" { return TK_FLOAT_TYPE;  }
"break" { return TK_BREAK; }
"continue" { return TK_CONTINUE; }
"printf" { return TK_PRINTF; }
\".*\" { return TK_LIT_STRING; }
{DIGIT}+ { yylval = atoi(yytext); return TK_LIT_INT; }
{DIGIT}+"."{DIGIT}+ { return TK_LIT_FLOAT; }
[a-zA-Z]({DIGIT}|[a-zA-Z_0-9]|_)* {return TK_ID; }
"!" {return '!'; }
";" {return ';'; }
"," {return ','; }
"+" {return '+'; }
"-" {return '-'; }
"/" {return '/'; }
"*" {return '*'; }
"%" {return '%'; }
"=" {return '='; }
"[" { return '['; }
"]" { return ']'; }
"{" { return '{'; }
"}" { return '}'; }
"+=" { return TK_PLUS_EQUAL; }
"-=" { return TK_MINUS_EQUAL; }
"++" { return TK_PLUS_PLUS; }
"--" { return TK_MINUS_MINUS; }
"||" { return TK_OR; }
"&&" { return TK_AND; }
"==" { return TK_EQUAL; }
"!=" { return TK_NOT_EQUAL; }
">" { return '>'; }
"<" { return '<'; }
">=" { return TK_GREATER_OR_EQUAL; }
"<=" { return TK_LESS_OR_EQUAL; }
"(" { return '('; }
"//"[^\n]* {/* nada */}
. {printf("caracter '%c' invalido en la linea %d\n", yytext[0], yylineno);}

<comment>"*/" {BEGIN(INITIAL);}
<comment>.|\n {/*nada*/}
<comment><<EOF>> {printf("comentario incompleto en la linea %d\n", yylineno); return 0;}
%%