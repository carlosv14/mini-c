#include <string>
#include <list>

using namespace std;

class Expr;
class InitDeclarator;
class Declaration;
class Parameter;
class StatementList;
typedef list<Expr *> InitializerElementList;
typedef list<InitDeclarator *> InitDeclaratorList;
typedef list<Declaration *> DeclarationList;
typedef list<Parameter *> ParameterList;
typedef list<Statement *> StatementList;

enum StatementKind{
    WHILE_STATEMENT,
    FOR_STATEMENT,
    IF_STATEMENT,
    EXPRESSION_STATEMENT,
    RETURN_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT,
    BLOCK_STATEMENT,
    PRINT_STATEMENT,
    FUNCTION_DEFINITION_STATEMENT,
    GLOBAL_DECLARATION_STATEMENT
};

enum Type{
    STRING,
    INT,
    FLOAT,
    VOID,
    INT_ARRAY,
    FLOAT_ARRAY,
    BOOL
};

class Statement{
    public:
        int line;
        virtual int evaluateSemantic() = 0;
        virtual StatementKind getKind() = 0;
};

class Expr{
    public:
        int line;
        virtual Type getType() = 0;
};

class Initializer{
    public:
        Initializer(InitializerElementList expressions, int line){
            this->expressions = expressions;
            this->line = line;
        }
        InitializerElementList expressions;
        int line;
};

class Declarator{
    public:
        Declarator(string id, Expr* arrayDeclaration, bool isArray, int line){
            this->id = id;
            this->isArray = isArray;
            this->line = line;
            this->arrayDeclaration = arrayDeclaration;
        }
        string id;
        bool isArray;
        int line;
        Expr * arrayDeclaration;
};

class InitDeclarator{
    public:
        InitDeclarator(Declarator * declarator, Initializer * initializer, int line){
            this->declarator = declarator;
            this->initializer = initializer;
            this->line = line;
        }
        Declarator * declarator;
        Initializer * initializer;
        int line;
};

class Declaration{
    public:
        Declaration(int type, InitDeclaratorList declarations, int line){
            this->type = type;
            this->declarations = declarations;
            this->line = line;
        }
        int type;
        InitDeclaratorList declarations;
        int line;
};

class Parameter{
    public:
        Parameter(int type, Declarator * declarator, bool isArray, int line){
            this->type = type;
            this->declarator = declarator;
            this->line = line;
        }
        int type;
        Declarator* declarator;
        bool isArray;
        int line;
};

class BlockStatement : public Statement{
    public:
        BlockStatement(StatementList statements, DeclarationList declarations, int line){
            this->statements = statements;
            this->declarations = declarations;
            this->line = line;
        }
        StatementList statements;
        DeclarationList declarations;
        int line;
};

class GlobalDeclaration : public Statement {
    public:
        GlobalDeclaration(Declaration * declaration){
            this->declaration = declaration;
        }
        Declaration * declaration;
};