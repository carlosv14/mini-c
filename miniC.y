%{
//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
    #define YYDEBUG 1
%}

/* %union{
    const char * string_t;
    int int_t;
    float float_t;
    Expr * expr_t;
    ArgumentList * argument_list_t;
    Statement * statement_t;
    StatementList * statement_list_t;
    InitDeclarationList * init_declaration_list_t;
    InitDeclaration * init_declaration_t;
    Declarator * declarator_t;
    Initializer * initializer_t;
    InitializerList * initializer_list_t;
    Parameter * parameter_t;
    ParameterList * parameter_list_t;
%} */

%token  TK_LIT_STRING TK_ID
%token  TK_LIT_INT
%token  TK_LIT_FLOAT
%token TK_IF TK_ELSE
%token TK_FOR TK_WHILE TK_BREAK TK_CONTINUE TK_RETURN
%token TK_VOID TK_INT_TYPE TK_FLOAT_TYPE
%token TK_PRINTF
%token TK_PLUS_EQUAL TK_MINUS_EQUAL TK_PLUS_PLUS TK_MINUS_MINUS
%token TK_OR TK_AND
%token TK_EQUAL TK_NOT_EQUAL TK_GREATER_OR_EQUAL TK_LESS_OR_EQUAL

/* %type <expr_t> literals factor term post_fix_expression expression additive_expression argument
%type <expr_t> relational_expression equality_expression logical_and_expression logical_or_expression constant_expression
%type <expr_t> assignment_expression unary_expression
%type <argument_list_t> arg_list argument_expression_list
%type <statement_t> print_statement while_statement if_statement for_statement expression_statement jump_statement statement block_statement
%type <statement_t> method_definition global_declaration declaration
%type <statement_list_t> statement_list input
%type <init_declaration_t> init_declaration
%type <init_declaration_list_t> declaration_list
%type <declarator_t> declarator
%type <initializer_t> initializer
%type <initializer_list_t> initializer_list
%type <parameter_t> parameter_declaration */

%%

input: input external_declaration
    | external_declaration
    ;

external_declaration: method_definition
            | declaration
            ;

method_definition: declaration_specifiers declarator declaration_list block_statement
                | declaration_specifiers declarator block_statement
                ;

declaration_list: declaration_list declaration
                | declaration
                ;

declaration: declaration_specifiers init_declarator_list';'
           | declaration_specifiers ';'
           ;

declaration_specifiers: type declaration_specifiers
                      | type
                      ;

init_declarator_list: init_declarator_list ',' init_declarator
                | init_declarator
                ;

init_declarator: declarator
                | declarator '=' initializer
                ;

declarator: TK_ID
          | declarator '[' assignment_expression ']'
          | declarator '[' ']'
          | declarator '(' parameters_type_list ')'
          | declarator '(' identifier_list ')'
          | declarator '(' ')'
          ;

identifier_list: TK_ID
               | identifier_list ',' TK_ID

parameters_type_list: parameters_type_list ',' parameter_declaration
                   | parameter_declaration
                   ;

parameter_declaration: declaration_specifiers declarator
                    ;

initializer: assignment_expression
           | '{' initializer_list '}'
           ;

initializer_list: designation initializer
                | initializer_list ',' designation initializer
                | initializer
                | initializer_list ',' initializer     
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

block_statement: '{' statement_list '}'
               | '{' declaration_list  statement_list'}' 
               | '{' '}'
               ;


constant_expression: logical_or_expression
                   ;

type: TK_VOID
    | TK_INT_TYPE
    | TK_FLOAT_TYPE
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