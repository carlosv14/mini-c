%code requires{
    #include "ast.h"
}

%{
//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
    #include "asm.h"
    #include <fstream>
    #include <iostream>

    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
    #define YYDEBUG 1
    #define EQUAL 1
    #define PLUSEQUAL 2
    #define MINUSEQUAL 3

    Asm assemblyFile;

    void writeFile(string name){
        ofstream file;
        file.open(name);
        file << assemblyFile.data << endl
        << assemblyFile.global <<endl
        << assemblyFile.text << endl;
        file.close();
    }
%}

%union{
    const char * string_t;
    int int_t;
    float float_t;
    Expr * expr_t;
    ArgumentList * argument_list_t;
    Statement * statement_t;
    StatementList * statement_list_t;
    InitDeclaratorList * init_declarator_list_t;
    InitDeclarator * init_declarator_t;
    Declarator * declarator_t;
    Initializer * initializer_t;
    InitializerElementList * initializer_list_t;
    Declaration * declaration_t;
    DeclarationList * declaration_list_t;
    Parameter * parameter_t;
    ParameterList * parameter_list_t;
}

%token<string_t>  TK_LIT_STRING TK_ID
%token<int_t>  TK_LIT_INT
%token<float_t>  TK_LIT_FLOAT
%token TK_IF TK_ELSE
%token TK_WHILE TK_RETURN
%token TK_VOID TK_INT_TYPE TK_FLOAT_TYPE
%token TK_PRINTF
%token TK_PLUS_EQUAL TK_MINUS_EQUAL TK_PLUS_PLUS TK_MINUS_MINUS TK_NOT
%token TK_OR TK_AND
%token TK_EQUAL TK_NOT_EQUAL TK_GREATER_OR_EQUAL TK_LESS_OR_EQUAL

%type<expr_t> assignment_expression logical_or_expression
%type<statement_list_t> statement_list input
%type<statement_t> external_declaration method_definition block_statement statement
%type<declaration_t> declaration
%type<declaration_list_t> declaration_list
%type<initializer_t> initializer
%type<initializer_list_t> initializer_list
%type<declarator_t> declarator
%type<init_declarator_t> init_declarator
%type<init_declarator_list_t> init_declarator_list
%type<parameter_t> parameter_declaration
%type<parameter_list_t> parameters_type_list
%type<int_t> type assignment_operator
%type<expr_t> constant expression logical_and_expression additive_expression multiplicative_expression equality_expression relational_expression
%type<expr_t> unary_expression postfix_expression primary_expression
%type<argument_list_t> argument_expression_list
%type <statement_t> if_statement while_statement expression_statement jump_statement
%%

start: input{
    assemblyFile.global = ".globl main";
    assemblyFile.data = ".data\n";
    assemblyFile.text = ".text\n";
    list<Statement *>::iterator it = $1->begin();
    string code;
    while(it != $1->end()){
        printf("semantic result: %d \n",(*it)->evaluateSemantic());
        code += (*it)->genCode();
        it++;
    }
    assemblyFile.text += code;
    writeFile("result.s");
}

input: input external_declaration {$$ = $1; $$->push_back($2);}
    | external_declaration {$$ = new StatementList; $$->push_back($1);}
    ;

external_declaration: method_definition {$$ = $1;}
            | declaration {$$ = new GlobalDeclaration($1);}
            ;

method_definition: type TK_ID '(' parameters_type_list ')' block_statement {
                    $$ = new MethodDefinition((Type)$1, $2, *$4, $6, yylineno );
                    delete $4;
                 }
                 | type TK_ID '(' ')' block_statement{
                     ParameterList * pm = new ParameterList;
                     $$ = new MethodDefinition((Type)$1, $2, *pm, $5, yylineno );
                     delete pm;
                 }
                 | type TK_ID '(' parameters_type_list ')' ';'{
                     $$ = new MethodDefinition((Type)$1, $2, *$4, NULL, yylineno);
                 }
                 | type TK_ID '(' ')' block_statement ';'{
                     ParameterList * pm = new ParameterList;
                     $$ = new MethodDefinition((Type)$1, $2, *pm , NULL, yylineno);
                     delete pm;
                 }
                ;

declaration_list: declaration_list declaration { $$ = $1; $$->push_back($2); }
                | declaration {$$ = new DeclarationList; $$->push_back($1);}
                ;

declaration: type init_declarator_list ';' { $$ = new Declaration((Type)$1, *$2, yylineno); delete $2;  }
           ;

init_declarator_list: init_declarator_list ',' init_declarator { $$ = $1; $$->push_back($3); }
                | init_declarator { $$ = new InitDeclaratorList; $$->push_back($1); }
                ;

init_declarator: declarator {$$ = new InitDeclarator($1, NULL, yylineno);}
                | declarator '=' initializer { $$ = new InitDeclarator($1, $3, yylineno); }
                ;

declarator: TK_ID {$$ = new Declarator($1, NULL, false, yylineno);}
          | TK_ID '[' assignment_expression ']' { $$ = new Declarator($1, $3, true, yylineno);}
          | TK_ID '[' ']' {$$ = new Declarator($1, NULL, true, yylineno);}
          ;

parameters_type_list: parameters_type_list ',' parameter_declaration {$$ = $1; $$->push_back($3);}
                   | parameter_declaration { $$ = new ParameterList; $$->push_back($1); }
                   ;

parameter_declaration: type declarator { $$ = new Parameter((Type)$1, $2, false, yylineno); }
                     | type { $$ = new Parameter((Type)$1, NULL, false, yylineno); }
                     | type '[' ']'  { $$ = new Parameter((Type)$1, NULL, true, yylineno); }
                    ;

initializer: assignment_expression {
    InitializerElementList * list = new InitializerElementList;
    list->push_back($1);
    $$ = new Initializer(*list, yylineno);
}
           | '{' initializer_list '}'{ $$ = new Initializer(*$2, yylineno); delete $2;  }
           ;

initializer_list: initializer_list ',' logical_or_expression { $$ = $1; $$->push_back($3); }
                | logical_or_expression {$$ = new InitializerElementList; $$->push_back($1);}
                ;

statement: while_statement {$$ = $1;}
        | expression_statement {$$ = $1;}
        | if_statement {$$ = $1;}
        | block_statement {$$ = $1;}
        | jump_statement {$$ = $1;}
        | TK_PRINTF expression ';' {$$ = new PrintStatement($2, yylineno);}
        ;

statement_list: statement_list statement { $$ = $1; $$->push_back($2); }
              | statement { $$ = new StatementList; $$->push_back($1); }
              ;

if_statement: TK_IF '(' expression ')' statement {$$ = new IfStatement($3, $5, yylineno);}
            | TK_IF '(' expression ')' statement TK_ELSE statement {$$ = new ElseStatement($3, $5, $7, yylineno);}
            ;

expression_statement: expression ';' {$$ = new ExprStatement($1, yylineno);}
                    ;

while_statement: TK_WHILE '(' expression ')' statement { $$ = new WhileStatement($3, $5, yylineno);}
               ;

jump_statement: TK_RETURN expression ';' {$$ = new ReturnStatement($2, yylineno);}
              ;

block_statement: '{' statement_list '}' { 
                    DeclarationList * list = new DeclarationList();
                    $$ = new BlockStatement(*$2, *list, yylineno);
                    delete list;
               }
               | '{' declaration_list  statement_list'}'  {$$ = new BlockStatement(*$3, *$2, yylineno); delete $2; delete $3; }
               | '{' '}' {
                   StatementList * stmts = new StatementList();
                   DeclarationList * decls = new DeclarationList();
                   $$ = new BlockStatement(*stmts, *decls, yylineno);
                   delete stmts;
                   delete decls;

               }
               ;

type: TK_VOID {$$ = VOID;}
    | TK_INT_TYPE{$$ = INT;}
    | TK_FLOAT_TYPE{$$ = FLOAT;}
    ;

primary_expression: '(' expression ')' {$$ = $2;}
    | TK_ID {$$ = new IdExpr($1, yylineno);}
    | constant {$$ = $1;}
    | TK_LIT_STRING { $$ = new StringExpr($1, yylineno); }
    ;

assignment_expression: unary_expression assignment_operator assignment_expression {
        if($2 == EQUAL){
            $$ = new AssignExpr($1,$3,yylineno);
        }else if($2 == PLUSEQUAL){
            $$ = new PlusAssignExpr($1,$3,yylineno);
        }else if($2 == MINUSEQUAL){
            $$ = new MinusAssignExpr($1,$3,yylineno);
        }
}
                     | logical_or_expression { $$ = $1; }
                     ;

postfix_expression: primary_expression {$$ = $1;}
                    | postfix_expression '[' expression ']' { $$ = new ArrayExpr((IdExpr*)$1, $3, yylineno); }
                    | postfix_expression '(' ')' { $$ = new MethodInvocationExpr((IdExpr*)$1, *(new ArgumentList), yylineno); }
                    | postfix_expression '(' argument_expression_list ')' { $$ = new MethodInvocationExpr((IdExpr*)$1, *$3, yylineno); }
                    | postfix_expression TK_PLUS_PLUS { $$ = new PostIncrementExpr((IdExpr*)$1, yylineno); }
                    | postfix_expression TK_MINUS_MINUS { $$ = new PostDecrementExpr((IdExpr*)$1, yylineno); }
                    ;


argument_expression_list: argument_expression_list ',' assignment_expression {$$ = $1;  $$->push_back($3);}
                        | assignment_expression { $$ = new ArgumentList; $$->push_back($1);}
                        ;

unary_expression: TK_PLUS_PLUS unary_expression {$$ = new UnaryExpr(INCREMENT, $2, yylineno);}
                | TK_MINUS_MINUS unary_expression {$$ = new UnaryExpr(DECREMENT, $2, yylineno);}
                | TK_NOT unary_expression  {$$ = new UnaryExpr(NOT, $2, yylineno);}
                | postfix_expression { $$ = $1;}
                ;

multiplicative_expression: multiplicative_expression '*' unary_expression { $$ = new MulExpr($1, $3, yylineno); }
      | multiplicative_expression '/' unary_expression { $$ = new DivExpr($1, $3, yylineno); }
      | unary_expression {$$ = $1;}
      ;

additive_expression:  additive_expression '+' multiplicative_expression{ $$ = new AddExpr($1, $3, yylineno); }
                    | additive_expression '-' multiplicative_expression { $$ = new SubExpr($1, $3, yylineno); }
                    | multiplicative_expression {$$ = $1;}
                    ;

relational_expression: relational_expression '>' additive_expression { $$ = new GtExpr($1, $3, yylineno); }
                     | relational_expression '<' additive_expression { $$ = new LtExpr($1, $3, yylineno); }
                     | relational_expression TK_GREATER_OR_EQUAL additive_expression { $$ = new GteExpr($1, $3, yylineno); }
                     | relational_expression TK_LESS_OR_EQUAL additive_expression { $$ = new LteExpr($1, $3, yylineno); }
                     | additive_expression {$$ = $1;}
                     ;

equality_expression:  equality_expression TK_EQUAL relational_expression { $$ = new EqExpr($1, $3, yylineno); }
                   | equality_expression TK_NOT_EQUAL relational_expression { $$ = new NeqExpr($1, $3, yylineno); }
                   | relational_expression {$$ = $1;}
                   ;

logical_or_expression: logical_or_expression TK_OR logical_and_expression { $$ = new LogicalOrExpr($1, $3, yylineno); }
                    | logical_and_expression {$$ = $1;}
                    ;

logical_and_expression: logical_and_expression TK_AND equality_expression { $$ = new LogicalAndExpr($1, $3, yylineno); }
                      | equality_expression {$$ = $1;}
                      ;

assignment_operator: '=' { $$ = EQUAL; }
                   | TK_PLUS_EQUAL {$$ = PLUSEQUAL; }
                   | TK_MINUS_EQUAL { $$ = MINUSEQUAL; }
                   ;

expression: assignment_expression {$$ = $1;}
          ;

constant: TK_LIT_INT { $$ = new IntExpr($1 , yylineno);}
        | TK_LIT_FLOAT { $$ = new FloatExpr($1 , yylineno);}
        ;
%%