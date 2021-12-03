#include "ast.h"
#include <iostream>
#include <sstream>
#include <set>
#include "asm.h"

extern Asm assemblyFile;

int globalStackPointer = 0;

class VariableInfo{
    public:
        VariableInfo(int offset, bool isArray, bool isParameter, Type type){
            this->offset = offset;
            this->isArray = isArray;
            this->isParameter = isParameter;
            this->type = type;
        }
        int offset;
        bool isArray;
        bool isParameter;
        Type type;
};

map<string, VariableInfo *> codeGenerationVars;

class ContextStack{
    public:
        struct ContextStack* prev;
        map<string, Type> variables;
};

class FunctionInfo{
    public:
        Type returnType;
        list<Parameter *> parameters;
};

int labelCounter = 0;
map<string, Type> globalVariables = {};
map<string, Type> variables;
map<string, FunctionInfo*> methods;
map<string, Type> resultTypes ={
    {"INT,INT", INT},
    {"FLOAT,FLOAT", FLOAT},
    {"INT,FLOAT", FLOAT},
    {"FLOAT,INT", FLOAT},
};

const char * intTemps[] = {"$t0","$t1", "$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9" };
const char * floatTemps[] = {"$f0",
                            "$f1",
                            "$f2",
                            "$f3",
                            "$f4",
                            "$f5",
                            "$f6",
                            "$f7",
                            "$f8",
                            "$f9",
                            "$f10",
                            "$f11",
                            "$f12",
                            "$f13",
                            "$f14",
                            "$f15",
                            "$f16",
                            "$f17",
                            "$f18",
                            "$f19",
                            "$f20",
                            "$f21",
                            "$f22",
                            "$f23",
                            "$f24",
                            "$f25",
                            "$f26",
                            "$f27",
                            "$f28",
                            "$f29",
                            "$f30",
                            "$f31"
                        };

#define INT_TEMP_COUNT 10
#define FLOAT_TEMP_COUNT 32
set<string> intTempMap;
set<string> floatTempMap;

string getIntTemp(){
    for (int i = 0; i < INT_TEMP_COUNT; i++)
    {
        if(intTempMap.find(intTemps[i]) == intTempMap.end()){
            intTempMap.insert(intTemps[i]);
            return string(intTemps[i]);
        }
    }
    return "";
}

string getFloatTemp(){
    for (int i = 0; i < FLOAT_TEMP_COUNT; i++)
    {
        if(floatTempMap.find(floatTemps[i]) == floatTempMap.end()){
            floatTempMap.insert(floatTemps[i]);
            return string(floatTemps[i]);
        }
    }
    return "";
}

void releaseIntTemp(string temp){
    intTempMap.erase(temp);
}

void releaseFloatTemp(string temp){
    floatTempMap.erase(temp);
}

string getTypeName(Type type){
    switch(type){
        case INT:
            return "INT";
        case FLOAT:
            return "FLOAT";
        case VOID:
            return "VOID";
        case INT_ARRAY:
            return "INT";
        case FLOAT_ARRAY:
            return "FLOAT";
        case BOOL:
            return "BOOL";
    }

    cout<<"Unknown type"<<endl;
    exit(0);
}

ContextStack * context = NULL;

void pushContext(){
    variables.clear();
    ContextStack * c = new ContextStack();
    c->variables = variables;
    c->prev = context;
    context = c;
}

void popContext(){
    if(context != NULL){
        ContextStack * previous = context->prev;
        free(context);
        context = previous;
    }
}

string getNewLabel(string prefix){
    stringstream ss;
    ss<<prefix << labelCounter;
    labelCounter++;
    return ss.str();
}

Type getLocalVariableType(string id){
    ContextStack * currContext = context;
    while(currContext != NULL){
        if(currContext->variables[id] != 0)
            return currContext->variables[id];
        currContext = currContext->prev;
    }
    if(!context->variables.empty())
        return context->variables[id];
    return INVALID;
}


Type getVariableType(string id){
    if(!globalVariables.empty())
        return globalVariables[id];
    return INVALID;
}


bool variableExists(string id){
  Type value;
  if(context != NULL){
    value = getLocalVariableType(id);
    //context->variables[id] != 0
    if(value != 0)
      return true;
  }
  return false;
}

int BlockStatement::evaluateSemantic(){
    list<Declaration *>::iterator itd = this->declarations.begin();
    while (itd != this->declarations.end())
    {
        Declaration * dec = *itd;
        if(dec != NULL){
            dec->evaluateSemantic();
        }

        itd++;
    }

    list<Statement *>::iterator its = this->statements.begin();
    while (its != this->statements.end())
    {
        Statement * stmt = *its;
        if(stmt != NULL){
            stmt->evaluateSemantic();
        }

        its++;
    }

    return 0;
}

string BlockStatement::genCode(){
    stringstream ss;

    list<Declaration *>::iterator itd = this->declarations.begin();
    while (itd != this->declarations.end())
    {
        Declaration * dec = *itd;
        if(dec != NULL){
            ss<<dec->genCode()<<endl;
        }

        itd++;
    }

    list<Statement *>::iterator its = this->statements.begin();
    while (its != this->statements.end())
    {
        Statement * stmt = *its;
        if(stmt != NULL){
            ss<<stmt->genCode()<<endl;
        }

        its++;
    }
    return ss.str();
}

int Declaration::evaluateSemantic(){
    list<InitDeclarator * >::iterator it = this->declarations.begin();
    while(it != this->declarations.end()){
        InitDeclarator * declaration = (*it);
        if(declaration->declarator->isArray){
            if(declaration->declarator->arrayDeclaration == NULL && declaration->initializer == NULL){
                cout<<"error: storage size of: "<<declaration->declarator->id  <<" is unknown line: "<<this->line<<endl;
                exit(0);
            }
        }
        if(declaration->initializer != NULL){
            list<Expr *>::iterator ite = declaration->initializer->expressions.begin();
            while(ite!= declaration->initializer->expressions.end()){
                Type exprType = (*ite)->getType();
                if(exprType != FLOAT && exprType != INT){
                    cout<<"error: invalid conversion from: "<< getTypeName(exprType) <<" to " <<getTypeName(this->type)<< " line: "<<this->line <<endl;
                    exit(0);
                }
                ite++;
            }
        }
        if(!variableExists(declaration->declarator->id)){
            context->variables[declaration->declarator->id] = this->type;
        }else{
            cout<<"error: redefinition of variable: "<< declaration->declarator->id<< " line: "<<this->line <<endl;
            exit(0);
        }
    it++;
  }
  return 0;
}

string Declaration::genCode(){
    stringstream code;
    list<InitDeclarator *>::iterator it = this->declarations.begin();
    while(it != this->declarations.end()){
        InitDeclarator * declaration = (*it);
        if (!declaration->declarator->isArray)
        {
           codeGenerationVars[declaration->declarator->id] = new VariableInfo(globalStackPointer, false, false, this->type);
           globalStackPointer +=4;
        }

        if(declaration->initializer != NULL){
            list<Expr *>::iterator itExpr = declaration->initializer->expressions.begin();
            for (int i = 0; i < declaration->initializer->expressions.size(); i++)
            {
                Code exprCode;
                (*itExpr)->genCode(exprCode);
                code << exprCode.code <<endl;
                if(exprCode.type == INT)
                    code << "sw " << exprCode.place <<", "<< codeGenerationVars[declaration->declarator->id]->offset<< "($sp)"<<endl;
                else if(exprCode.type == FLOAT)
                    code << "s.s " << exprCode.place <<", "<< codeGenerationVars[declaration->declarator->id]->offset<< "($sp)"<<endl;

                releaseIntTemp(exprCode.place);
                itExpr++;
            }
            
        }
       it++; 
    }
    return code.str();
}

int GlobalDeclaration::evaluateSemantic(){
    //TODO: evaluar semántica.
    return 0;
}

string GlobalDeclaration::genCode(){
    list<InitDeclarator *>::iterator it = this->declaration->declarations.begin();
    stringstream data;
    stringstream code;
    while (it != this->declaration->declarations.end())
    {
        InitDeclarator * declaration = (*it);
        data << declaration->declarator->id <<": .word 0"<<endl;
        if(declaration->initializer != NULL){
            list<Expr *>::iterator itExpr = declaration->initializer->expressions.begin();
            for(int i = 0; i < declaration->initializer->expressions.size(); i++){
                Code exprCode;
                (*itExpr)->genCode(exprCode);
                code << exprCode.code;
                if(!declaration->declarator->isArray){
                    if(exprCode.type == INT)
                        code << "sw "<< exprCode.place<< ", " << declaration->declarator->id<<endl;
                    else if(exprCode.type == FLOAT)
                        code << "s.s "<< exprCode.place<< ", " << declaration->declarator->id<<endl;
                }
                releaseIntTemp(exprCode.place);
                itExpr++;
            }
        }

        it++;
    }

    assemblyFile.data += data.str();
    return code.str();
}


void addMethodDeclaration(string id, int line, Type type, ParameterList params){
    if(methods[id] != 0){
        cout<<"redefinition of function "<<id<<" in line: "<<line<<endl;
        exit(0);
    }
    methods[id] = new FunctionInfo();
    methods[id]->returnType = type;
    methods[id]->parameters = params;
}

int MethodDefinition::evaluateSemantic(){
    if(this->params.size() > 4){
        cout<< "Method: "<<this->id << " can't have more than 4 parameters, line: "<< this->line<<endl;
        exit(0);
    }

    addMethodDeclaration(this->id, this->line, this->type, this->params);
    pushContext();
   
    list<Parameter* >::iterator it = this->params.begin();
    while(it != this->params.end()){
        (*it)->evaluateSemantic();
        it++;
    }

    if(this->statement !=NULL ){
        this->statement->evaluateSemantic();
    }
    
    popContext();

    return 0;
}

string MethodDefinition::genCode(){
    return this->statement->genCode();
}

Type IntExpr::getType(){
    return INT;
}

void IntExpr::genCode(Code &code){
    string temp = getIntTemp();
    code.place = temp;
    stringstream ss;
    ss << "li " << temp <<", "<< this->value <<endl;
    code.code = ss.str();
    code.type = INT;
}

Type FloatExpr::getType(){
    return FLOAT;
}

void FloatExpr::genCode(Code &code){
    string floatTemp = getFloatTemp();
    code.place = floatTemp;
    stringstream ss;
    ss << "li.s " << floatTemp <<", "<< this->value <<endl;
    code.code = ss.str();
    code.type = FLOAT;
}

#define IMPLEMENT_BINARY_GET_TYPE(name)\
Type name##Expr::getType(){\
    string leftType = getTypeName(this->expr1->getType());\
    string rightType = getTypeName(this->expr2->getType());\
    Type resultType = resultTypes[leftType+","+rightType];\
    if(resultType == 0){\
        cerr<< "Error: type "<< leftType <<" can't be converted to type "<< rightType <<" line: "<<this->line<<endl;\
        exit(0);\
    }\
    return resultType; \
}\

void toFloat(Code &code){
    if(code.type == INT){
        string floatTemp = getFloatTemp();
        stringstream ss;
        ss << code.code
        << "mtc1 "<< code.place << ", " << floatTemp <<endl
        << "cvt.s.w " << floatTemp<< ", " << floatTemp <<endl;
        releaseFloatTemp(code.place);
        code.place = floatTemp;
        code.type = FLOAT;
        code.code =  ss.str();
    }
    else{
        /* nothing */
    }
}

#define IMPLEMENT_BINARY_ARIT_GEN_CODE(name, op)\
void name##Expr::genCode(Code &code){\
    Code leftCode, rightCode;\
    stringstream ss;\
    this->expr1->genCode(leftCode);\
    this->expr2->genCode(rightCode);\
    if(leftCode.type == INT && rightCode.type == INT){\
        code.type = INT;\
        releaseIntTemp(leftCode.place);\
        releaseIntTemp(rightCode.place);\
        ss<< leftCode.code << endl\
        << rightCode.code <<endl\
        << intArithmetic(leftCode, rightCode, code, op)<< endl;\
    }else{\
        code.type = FLOAT;\
        toFloat(leftCode);\
        toFloat(rightCode);\
        releaseIntTemp(leftCode.place);\
        releaseIntTemp(rightCode.place);\
        releaseFloatTemp(leftCode.place);\
        releaseFloatTemp(rightCode.place);\
        ss << leftCode.code << endl\
        << rightCode.code <<endl\
        << floatArithmetic(leftCode, rightCode, code, op)<<endl;\
    }\
    code.code = ss.str();\
}\

#define IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(name)\
Type name##Expr::getType(){\
    string leftType = getTypeName(this->expr1->getType());\
    string rightType = getTypeName(this->expr2->getType());\
    Type resultType = resultTypes[leftType+","+rightType];\
    if(resultType == 0){\
        cerr<< "Error: type "<< leftType <<" can't be converted to type "<< rightType <<" line: "<<this->line<<endl;\
        exit(0);\
    }\
    return BOOL; \
}\


string intArithmetic(Code &leftCode, Code &rightCode, Code &code, char op){
    stringstream ss;
    code.place = getIntTemp();
    switch (op)
    {
        case '+':
            ss << "add "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        case '-':
            ss << "sub "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        case '*':
            ss << "mult "<< leftCode.place <<", "<< rightCode.place <<endl
            << "mflo "<< code.place;
            break;
        case '/':
            ss << "div "<< leftCode.place <<", "<< rightCode.place
            << "mflo "<< code.place;
            break;
        default:
            break;
    }
    return ss.str();
}

string floatArithmetic(Code &leftCode, Code &rightCode, Code &code, char op){
    stringstream ss;
    code.place = getFloatTemp();
    switch (op)
    {
        case '+':
            ss << "add.s "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        case '-':
            ss << "sub.s "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        case '*':
            ss << "mul.s "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        case '/':
            ss << "div.s "<< code.place<<", "<< leftCode.place <<", "<< rightCode.place;
            break;
        default:
            break;
    }
    return ss.str();
}

Type getUnaryType(Type expressionType, int unaryOperation){
    switch(unaryOperation){
        case INCREMENT:
        case DECREMENT:
            if(expressionType == INT || expressionType == FLOAT)
                return expressionType;
        case NOT:
            if(expressionType == BOOL)
                return BOOL;
    }

    cerr<<"Error: Invalid type"<<endl;
    exit(0);
}

int Parameter::evaluateSemantic(){
    if(!variableExists(this->declarator->id)){
        context->variables[declarator->id] = this->type;
    }else{
        cout<<"error: redefinition of variable: "<< declarator->id<< " line: "<<this->line <<endl;
        exit(0);
    }
    return 0;
}


Type UnaryExpr::getType(){
    Type exprType = this->expr->getType();
    return getUnaryType(exprType, this->type);
}

void UnaryExpr::genCode(Code &code){
    
}

Type ArrayExpr::getType(){
    return this->id->getType();
}

void ArrayExpr::genCode(Code &code){
    
}

Type IdExpr::getType(){
    Type value;
    if(context != NULL){
        value = getLocalVariableType(this->id);
        if(value != 0)
            return value;
    }
    value = getVariableType(this->id);
    if(value == 0){
        cout<<"error: '"<<this->id<<"' was not declared in this scope line: "<<this->line<<endl;
        exit(0);
    }
    return value;
}

void IdExpr::genCode(Code &code){
    if(codeGenerationVars.find(this->id) == codeGenerationVars.end()){
        code.type = globalVariables[this->id];
        if(globalVariables[this->id] == INT){
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw "+ intTemp + ", "+ this->id + "\n";
        }else if(globalVariables[this->id] == FLOAT){
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s "+ floatTemp + ", "+ this->id + "\n";
        }
    }
   else{
        code.type = codeGenerationVars[this->id]->type;
        if(codeGenerationVars[this->id]->type == INT && !codeGenerationVars[this->id]->isArray){
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw "+ intTemp + ", " + to_string(codeGenerationVars[this->id]->offset) +"($sp)\n";
        }else if(codeGenerationVars[this->id]->type == FLOAT && !codeGenerationVars[this->id]->isArray){
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s "+ floatTemp + ", " +to_string(codeGenerationVars[this->id]->offset) +"($sp)\n";
        }
    }
}

Type MethodInvocationExpr::getType(){
    FunctionInfo * func = methods[this->id->id];
    if(func == NULL){
        cout<<"error: function "<<this->id->id<<" not found, line: "<<this->line<<endl;
        exit(0);
    }
    Type funcType = func->returnType;
    if(func->parameters.size() > this->args.size()){
        cout<<"error: to few arguments to function"<<this->id->id<<" line: "<<this->line<<endl;
        exit(0);
    }
    if(func->parameters.size() < this->args.size()){
        cout<<"error: to many arguments to function "<<this->id->id<<" line: "<<this->line<<endl;
        exit(0);
    }

    list<Parameter *>::iterator paramIt = func->parameters.begin();
    list<Expr *>::iterator argsIt =this->args.begin();
    while(paramIt != func->parameters.end() && argsIt != this->args.end()){
        string paramType = getTypeName((*paramIt)->type);
        string argType = getTypeName((*argsIt)->getType());
        if( paramType != argType){
            cout<<"error: invalid conversion from: "<< argType <<" to " <<paramType<< " line: "<<this->line <<endl;
            exit(0);
        }
        paramIt++;
        argsIt++;
    }

    return funcType;
}

void MethodInvocationExpr::genCode(Code &code){
    
}

Type PostIncrementExpr::getType(){
    return this->expr->getType();
}

void PostIncrementExpr::genCode(Code &code){
    
}

Type PostDecrementExpr::getType(){
    return this->expr->getType();
}

void PostDecrementExpr::genCode(Code &code){

}

Type StringExpr::getType(){
    return STRING;
}

void StringExpr::genCode(Code &code){
    string strLabel = getNewLabel("string");
    stringstream ss;
    ss << strLabel <<": \"" << this->value << "\""<<endl;
    assemblyFile.data += ss.str(); 
    code.code = "";
    code.place = strLabel;
}

int WhileStatement::evaluateSemantic(){
    if(this->expr->getType() != BOOL){
        cout<<"Expression for while must be boolean";
        exit(0);
    }
    
    pushContext();
    if(this->stmt != NULL){
        this->stmt->evaluateSemantic();
    }
    popContext();
    return 0;
}

string WhileStatement::genCode(){
    stringstream ss;
    string whileLabel = getNewLabel("while");
    string endWhileLabel = getNewLabel("endWhile");
    Code code;
    this->expr->genCode(code);
    ss << whileLabel << ": "<< endl
    << code.code <<endl
    << "beqz "<< code.place << ", " << endWhileLabel <<endl
    << this->stmt->genCode() <<endl
    << "j " << whileLabel <<endl
    << endWhileLabel << ": "<<endl;
    return ss.str();
}

int ElseStatement::evaluateSemantic(){
    if(this->conditionalExpr->getType() != BOOL){
        cout<<"Expression for if must be boolean";
        exit(0);
    }
    pushContext();
    this->trueStatement->evaluateSemantic();
    popContext();
    pushContext();
    if(this->falseStatement != NULL)
        this->falseStatement->evaluateSemantic();
    popContext();
    return 0;
}

string ElseStatement::genCode(){
    string elseLabel = getNewLabel("else");
    string endIfLabel = getNewLabel("endif");
    Code exprCode;
    this->conditionalExpr->genCode(exprCode);
    stringstream code;
    code << exprCode.code << endl
    << "beqz "<< exprCode.place << ", " << elseLabel <<endl
    << this->trueStatement->genCode() << endl
    << "j " <<endIfLabel << endl
    << elseLabel <<": " <<endl
    << this->falseStatement->genCode() <<endl
    << endIfLabel <<" :"<< endl;
    releaseIntTemp(exprCode.place);
    return code.str();
}

int IfStatement::evaluateSemantic(){
    if(this->conditionalExpr->getType() != BOOL){
        cout<<"Expression for if must be boolean";
        exit(0);
    }
    pushContext();
    this->trueStatement->evaluateSemantic();
    popContext();
    return 0;
}

string IfStatement::genCode(){
    string endIfLabel = getNewLabel("endif");
    Code exprCode;
    this->conditionalExpr->genCode(exprCode);
    stringstream code;
    code << exprCode.code << endl
    << "beqz "<< exprCode.place << ", " << endIfLabel <<endl
    << this->trueStatement->genCode() << endl
    << endIfLabel <<" :"<< endl;
    releaseIntTemp(exprCode.place);
    return code.str();
}

int ExprStatement::evaluateSemantic(){
    return this->expr->getType();
}

string ExprStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    return exprCode.code;
}

int ReturnStatement::evaluateSemantic(){
    return this->expr->getType();
}

string ReturnStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    if(this->expr->getType() == INT){
        releaseIntTemp(exprCode.place);
    }else{
        releaseFloatTemp(exprCode.place);
    }

    stringstream ss;
    ss << exprCode.code << endl
    << "move $v0, "<< exprCode.place <<endl;
    return ss.str();
}

int PrintStatement::evaluateSemantic(){
    return this->expr->getType();
}

string PrintStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    stringstream code;
    code<< exprCode.code<<endl;
    if(exprCode.type == INT){
        code <<"move $a0, "<< exprCode.place<<endl
        << "li $v0, 1"<<endl
        << "syscall"<<endl;
    }else if(exprCode.type == FLOAT){
        code << "mov.s $f12, "<< exprCode.place<<endl
        << "li $v0, 2"<<endl
        << "syscall"<<endl;
    }
    return code.str();
}

void EqExpr::genCode(Code &code){

}

void NeqExpr::genCode(Code &code){
    
}

void GteExpr::genCode(Code &code){
    
}

void LteExpr::genCode(Code &code){
    
}

void GtExpr::genCode(Code &code){
    
}

void LtExpr::genCode(Code &code){
    
}

void LogicalAndExpr::genCode(Code &code){
    
}

void LogicalOrExpr::genCode(Code &code){
    
}

void AssignExpr::genCode(Code &code){
    
}
void PlusAssignExpr::genCode(Code &code){
    
}

void MinusAssignExpr::genCode(Code &code){
    
}

IMPLEMENT_BINARY_GET_TYPE(Add);
IMPLEMENT_BINARY_GET_TYPE(Sub);
IMPLEMENT_BINARY_GET_TYPE(Mul);
IMPLEMENT_BINARY_GET_TYPE(Div);
IMPLEMENT_BINARY_GET_TYPE(Assign);
IMPLEMENT_BINARY_GET_TYPE(PlusAssign);
IMPLEMENT_BINARY_GET_TYPE(MinusAssign);

IMPLEMENT_BINARY_ARIT_GEN_CODE(Add, '+');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Sub, '-');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Mul, '*');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Div, '/');

IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Eq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Neq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalAnd);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalOr);
