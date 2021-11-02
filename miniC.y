%{
//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
    #include "ast.h"
    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
    #define YYDEBUG 1
%}

%union{
    const char * string_t;
    int int_t;
    float float_t;
    Expr * expr_t;
    // ArgumentList * argument_list_t;
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
%token TK_FOR TK_WHILE TK_BREAK TK_CONTINUE TK_RETURN
%token TK_VOID TK_INT_TYPE TK_FLOAT_TYPE
%token TK_PRINTF
%token TK_PLUS_EQUAL TK_MINUS_EQUAL TK_PLUS_PLUS TK_MINUS_MINUS
%token TK_OR TK_AND
%token TK_EQUAL TK_NOT_EQUAL TK_GREATER_OR_EQUAL TK_LESS_OR_EQUAL

%type<expr_t> assignment_expression logical_or_expression
%type<statement_list_t> statement_list
%type<statement_t> external_declaration method_definition block_statement
%type<declaration_t> declaration
%type<declaration_list_t> declaration_list
%type<initializer_t> initializer
%type<initializer_list_t> initializer_list
%type<declarator_t> declarator
%type<init_declarator_t> init_declarator
%type<init_declarator_list_t> init_declarator_list
%type<parameter_t> parameter_declaration
%type<parameter_list_t> parameters_type_list
%type<int_t> type;
%%

input: input external_declaration
    | external_declaration
    ;

external_declaration: method_definition
            | declaration {$$ = new GlobalDeclaration($1);}
            ;

method_definition: type TK_ID '(' parameters_type_list ')' block_statement
                 | type TK_ID '(' ')' block_statement
                 | type TK_ID '(' parameters_type_list ')' ';'
                 | type TK_ID '(' ')' block_statement ';'
                ;

declaration_list: declaration_list declaration { $$ = $1; $$->push_back($2); }
                | declaration {$$ = new DeclarationList; $$->push_back($1);}
                ;

declaration: type init_declarator_list ';' { $$ = new Declaration($1, *$2, yylineno); delete $2;  }
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

identifier_list: TK_ID
               | identifier_list ',' TK_ID

parameters_type_list: parameters_type_list ',' parameter_declaration {$$ = $1; $$->push_back($3);}
                   | parameter_declaration { $$ = new ParameterList; $$->push_back($1); }
                   ;

parameter_declaration: type declarator { $$ = new Parameter($1, $2, false, yylineno); }
                     | type { $$ = new Parameter($1, NULL, false, yylineno); }
                     | type '[' ']'  { $$ = new Parameter($1, NULL, true, yylineno); }
                    ;

initializer: assignment_expression {
    InitializerElementList * list = InitializerElementList;
    list->push_back($1);
    $$ = new Initializer(*list, yylineno);
}
           | '{' initializer_list '}'{ $$ = new Initializer(*$2, yylineno); delete $2;  }
           ;

initializer_list: initializer_list ',' logical_or_expression { $$ = $1; $$->push_back($3); }
                | logical_or_expression {$$ = new InitializerElementList; $$->push_back($1);}
                ;

designation: designator_list '='
           ;

designator_list: designator
               | designator_list designator
               ;

designator: '[' constant_expression ']'
          ;

statement: while_statement
        | expression_statement
        | if_statement
        | for_statement
        | block_statement
        | jump_statement
        | TK_PRINTF expression ';'
        ;

statement_list: statement_list statement
              | statement
              ;

if_statement: TK_IF '(' expression ')' statement
            | TK_IF '(' expression ')' statement TK_ELSE statement
            ;
  
for_statement: TK_FOR '(' expression_statement expression_statement expression ')' statement
            ;

expression_statement: ';'
                    | expression ';'
                    ;

while_statement: TK_WHILE '(' expression ')' statement
               ;

jump_statement: TK_RETURN ';'
              | TK_CONTINUE ';'
              | TK_BREAK ';'
              | TK_RETURN expression ';'
              ;

block_statement: '{' statement_list '}' { $$ = new BlockStatement($2, NULL, yylineno); }
               | '{' declaration_list  statement_list'}'  {$$ = new BlockStatement($3, $2, yylineno); delete $2; delete $3; }
               | '{' '}' {
                   StatementList * stmts = new StatementList();
                   DeclarationList * decls = new DEclarationList();
                   $$ = new BlockStatement(*stmts, *decls, yylineno);
                   delete stmts;
                   delete decls;

               }
               ;


constant_expression: logical_or_expression
                   ;

type: TK_VOID {$$ = $1;}
    | TK_INT_TYPE{$$ = $1;}
    | TK_FLOAT_TYPE{$$ = $1;}
    ;

primary_expression: '(' expression ')'
    | TK_ID
    | constant
    | TK_LIT_STRING
    ;

assignment_expression: unary_expression assignment_operator assignment_expression
                     | logical_or_expression
                     ;

postfix_expression: primary_expression
                    | postfix_expression '[' expression ']'
                    | postfix_expression '(' ')'
                    | postfix_expression '(' argument_expression_list ')'
                    | postfix_expression TK_PLUS_PLUS
                    | postfix_expression TK_MINUS_MINUS
                    ;


argument_expression_list: argument_expression_list ',' assignment_expression
                        | assignment_expression
                        ;

unary_expression: TK_PLUS_PLUS unary_expression
                | TK_MINUS_MINUS unary_expression
                | '!' cast_expression 
                | postfix_expression
                ;

cast_expression: unary_expression
               ;

multiplicative_expression: multiplicative_expression '*' cast_expression
      | multiplicative_expression '/' cast_expression
      | cast_expression
      ;

additive_expression:  additive_expression '+' multiplicative_expression
                    | additive_expression '-' multiplicative_expression
                    | multiplicative_expression
                    ;

relational_expression: relational_expression '>' additive_expression
                     | relational_expression '<' additive_expression
                     | relational_expression TK_GREATER_OR_EQUAL additive_expression
                     | relational_expression TK_LESS_OR_EQUAL additive_expression
                     | additive_expression
                     ;

equality_expression:  equality_expression TK_EQUAL relational_expression
                   | equality_expression TK_NOT_EQUAL relational_expression
                   | relational_expression
                   ;

logical_or_expression: logical_or_expression TK_OR logical_and_expression
                    | logical_and_expression
                    ;

logical_and_expression: logical_and_expression TK_AND equality_expression
                      | equality_expression
                      ;

assignment_operator: '='
                   | TK_PLUS_EQUAL
                   | TK_MINUS_EQUAL
                   ;

expression: assignment_expression
          | expression ',' assignment_expression
          ;

constant: TK_LIT_INT
        | TK_LIT_FLOAT
        ;
%%