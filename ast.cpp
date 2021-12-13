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
    cout<<"No more int registers!"<<endl;
    //exit(1);
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
    cout<<"No more float registers!"<<endl;
    //exit(1);
    return "";
}

void releaseIntTemp(string temp){
    intTempMap.erase(temp);
}

void releaseFloatTemp(string temp){
    floatTempMap.erase(temp);
}

void releaseRegister(string temp){
    releaseIntTemp(temp);
    releaseFloatTemp(temp);
}

string saveState(){
    set<string>::iterator it = floatTempMap.begin();
    stringstream ss;
    ss<<"sw $ra, " <<globalStackPointer<< "($sp)\n";
    globalStackPointer+=4;
    return ss.str();
}

string retrieveState(string state){
    std::string::size_type n = 0;
    string s = "sw";
    while ( ( n = state.find( s, n ) ) != std::string::npos )
    {
    state.replace( n, s.size(), "lw" );
    n += 2;
    globalStackPointer-=4;
    }
    return state;
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
        }else{
            codeGenerationVars[declaration->declarator->id] = new VariableInfo(globalStackPointer, true, false, this->type);
            if(declaration->initializer == NULL){
                if(declaration->declarator->arrayDeclaration != NULL){
                    int size = ((IntExpr *)declaration->declarator->arrayDeclaration)->value;
                    globalStackPointer += (size * 4);
                }
            }
        }

        //int arr[] = {1,3,4,5}
        if(declaration->initializer != NULL){
            list<Expr *>::iterator itExpr = declaration->initializer->expressions.begin();
            int offset = codeGenerationVars[declaration->declarator->id]->offset;
            for (int i = 0; i < declaration->initializer->expressions.size(); i++)
            {
                Code exprCode;
                (*itExpr)->genCode(exprCode);
                code << exprCode.code <<endl;
                if(exprCode.type == INT)
                    code << "sw " << exprCode.place <<", "<< offset << "($sp)"<<endl;
                else if(exprCode.type == FLOAT)
                    code << "s.s " << exprCode.place <<", "<< offset << "($sp)"<<endl;
                releaseRegister(exprCode.place);
                itExpr++;
                if (declaration->declarator->isArray)
                {
                    globalStackPointer+=4;
                    offset += 4;
                }
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
        data << declaration->declarator->id <<": .word 0";
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
                }else{
                    string temp = getIntTemp();
                    code << "la "<<temp<<", "<<declaration->declarator->id<<endl;
                    if(exprCode.type == INT)
                    {
                        code <<"sw "<<exprCode.place<<", "<< i*4<<"("<<temp<<")"<<endl;
                    }else if(exprCode.type == FLOAT)
                    {
                        code <<"s.s "<<exprCode.place<<", "<< i*4<<"("<<temp<<")"<<endl;
                    }
                }
                releaseRegister(exprCode.place);
                itExpr++;
            }
        }else if(declaration->declarator->isArray){
            if(declaration->declarator->arrayDeclaration != NULL){
                int size = ((IntExpr*)declaration->declarator->arrayDeclaration)->value;
                for (int i = 0; i < size - 1; i++)
                {
                    data<<", 0";
                }
            }
        }
        data<<endl;
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
    if(this->statement == NULL)
        return "";

    int stackPointer = 4;
    globalStackPointer = 0;
    stringstream code;
    code << this->id<<": "<<endl;
    string state = saveState();
    code <<state<<endl;
    if(this->params.size() > 0){
        list<Parameter *>::iterator it = this->params.begin();
        for(int i = 0; i< this->params.size(); i++){
            code << "sw $a"<<i<<", "<< stackPointer<<"($sp)"<<endl;
            codeGenerationVars[(*it)->declarator->id] = new VariableInfo(stackPointer, false, true, (*it)->type);
            stackPointer +=4;
            globalStackPointer +=4;
            it++;
        }
    }
    code<< this->statement->genCode()<<endl;
    stringstream sp;
    int currentStackPointer = globalStackPointer;
    sp << endl<<"addiu $sp, $sp, -"<<currentStackPointer<<endl;
    code << retrieveState(state);
    code << "addiu $sp, $sp, "<<currentStackPointer<<endl;
    code <<"jr $ra"<<endl;
    codeGenerationVars.clear();
    string result = code.str();
    result.insert(id.size() + 2, sp.str());
    return result;
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
        releaseRegister(code.place);
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
        releaseRegister(leftCode.place);\
        releaseRegister(rightCode.place);\
        ss<< leftCode.code << endl\
        << rightCode.code <<endl\
        << intArithmetic(leftCode, rightCode, code, op)<< endl;\
    }else{\
        code.type = FLOAT;\
        toFloat(leftCode);\
        toFloat(rightCode);\
        releaseRegister(leftCode.place);\
        releaseRegister(rightCode.place);\
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
            ss << "div "<< leftCode.place <<", "<< rightCode.place<<endl
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
    Code arrayCode;
    string name = this->id->id;
    stringstream ss;
    this->expr->genCode(arrayCode);
    //a[1]
    releaseRegister(arrayCode.place);
    if (codeGenerationVars.find(name) == codeGenerationVars.end())
    {
        string temp = getIntTemp();
        string labelAddress = getIntTemp();
        ss << arrayCode.code<<endl
        << "li $a0, 4"<<endl
        << "mult $a0, "<< arrayCode.place<<endl
        <<"mflo "<<temp<<endl
        << "la "<< labelAddress<<", "<< name<<endl
        << "add "<<temp<<", "<<labelAddress<<", "<<temp<<endl;
        releaseRegister(labelAddress);
        if(globalVariables[name] == INT){
           ss <<"lw "<< temp<<", 0("<<temp<<")"<<endl;
           code.place = temp;
        }else{
            string floatTemp = getFloatTemp();
            ss <<"l.s "<< floatTemp<<", 0("<<temp<<")"<<endl;
            code.place = floatTemp;
        }
    }else{
        string temp = getIntTemp();
        string address = getIntTemp();
        ss << arrayCode.code<<endl
        << "li $a0, 4"<<endl
        << "mult $a0, "<< arrayCode.place<<endl
        <<"mflo "<<temp<<endl;
        if(!codeGenerationVars[name]->isParameter)
            ss<< "la " + address +", " <<codeGenerationVars[name]->offset<<"($sp)\n";
        else
            ss << "lw "<<address<<", "<<codeGenerationVars[name]->offset<<"($sp)"<<endl;
        ss<< "add "<<temp<<", "<<address<<", "<<temp<<endl;
        releaseRegister(address);
        if(codeGenerationVars[name]->type == INT){
           ss <<"lw "<< temp<<", 0("<<temp<<")"<<endl;
           code.place = temp;
           code.type = INT;
        }else{
            string floatTemp = getFloatTemp();
            ss <<"l.s "<< floatTemp<<", 0("<<temp<<")"<<endl;
           code.place = floatTemp;
           code.type = FLOAT;
        }
    }
    code.code = ss.str();
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
        if(globalVariables[this->id] == INT_ARRAY || globalVariables[this->id] == FLOAT_ARRAY){
            string intTemp = getIntTemp();
            code.code = "la " + intTemp+ ", "+ this->id + "\n";
            code.place = intTemp;
        }
        if(globalVariables[this->id] == FLOAT){
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s "+ floatTemp + ", "+ this->id + "\n";
        }else{
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw "+ intTemp + ", "+ this->id + "\n";
        }
    }
   else{
        code.type = codeGenerationVars[this->id]->type;
        if(codeGenerationVars[this->id]->type == FLOAT && !codeGenerationVars[this->id]->isArray){
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s "+ floatTemp + ", " +to_string(codeGenerationVars[this->id]->offset) +"($sp)\n";
        }else if(codeGenerationVars[this->id]->type == INT && !codeGenerationVars[this->id]->isArray){
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw "+ intTemp + ", " + to_string(codeGenerationVars[this->id]->offset) +"($sp)\n";
        }else if(codeGenerationVars[this->id]->isArray){
            string intTemp = getIntTemp();
            code.code = "la "+ intTemp + ", " + to_string(codeGenerationVars[this->id]->offset)+"($sp)\n";
            code.place = intTemp;
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
    list<Expr *>::iterator it = this->args.begin();
    list<Code> codes;
    stringstream ss;
    Code argCode;
    while (it != this->args.end())
    {
        (*it)->genCode(argCode);
        ss << argCode.code <<endl;
        codes.push_back(argCode);
        it++;
    }

    int i = 0;
    list<Code>::iterator placesIt = codes.begin();
    while (placesIt != codes.end())
    {
        releaseRegister((*placesIt).place);
        if((*placesIt).type == FLOAT){
            ss << "mfc1 $a"<<i<<", "<< (*placesIt).place<<endl;
        }else{
            ss << "move $a"<<i<<", "<< (*placesIt).place<<endl;
        }
        i++;
        placesIt++;
    }

    ss<< "jal "<< this->id->id<<endl;
    string reg;
    if(methods[this->id->id]->returnType == FLOAT){
        reg = getFloatTemp();
        ss << "mtc1 $v0, "<< reg<<endl;
    }else{
        reg = getIntTemp();
        ss << "move "<< reg<<", $v0";
    }
    code.code = ss.str();
    code.place = reg;
    code.type = methods[this->id->id]->returnType;
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
    ss << strLabel <<": .asciiz" << this->value << ""<<endl;
    assemblyFile.data += ss.str(); 
    code.code = "";
    code.place = strLabel;
    code.type = STRING;
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
    releaseRegister(code.place);
    ss << whileLabel << ": "<< endl
    << code.code <<endl;
    if(code.type == INT){
        ss<< "beqz "<< code.place << ", " << endWhileLabel <<endl;
    }else{
        ss << "bc1f "<< endWhileLabel <<endl;
    }
    ss<< this->stmt->genCode() <<endl
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
    code << exprCode.code << endl;
    if(exprCode.type == INT){
        code<< "beqz "<< exprCode.place << ", " << elseLabel <<endl;
    }else{
        code << "bc1f "<< elseLabel <<endl;
    }
    code << this->trueStatement->genCode() << endl
    << "j " <<endIfLabel << endl
    << elseLabel <<": " <<endl
    << this->falseStatement->genCode() <<endl
    << endIfLabel <<" :"<< endl;
    releaseRegister(exprCode.place);
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
    code << exprCode.code << endl;
    if(exprCode.type == INT){
        code<< "beqz "<< exprCode.place << ", " << endIfLabel <<endl;
    }else{
        code << "bc1f "<< endIfLabel <<endl;
    }
    code<< this->trueStatement->genCode() << endl
    << endIfLabel <<" :"<< endl;
    releaseRegister(exprCode.place);
    
    return code.str();
}

int ExprStatement::evaluateSemantic(){
    return this->expr->getType();
}

string ExprStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    releaseRegister(exprCode.place);
    return exprCode.code;
}

int ReturnStatement::evaluateSemantic(){
    return this->expr->getType();
}

string ReturnStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    releaseRegister(exprCode.place);
    stringstream ss;
    ss << exprCode.code << endl;
    if(exprCode.type == INT)
        ss<< "move $v0, "<< exprCode.place <<endl;
    else
        ss<< "mfc1 $v0, "<<exprCode.place<<endl;
    return ss.str();
}

int PrintStatement::evaluateSemantic(){
    return this->expr->getType();
}

string PrintStatement::genCode(){
    Code exprCode;
    this->expr->genCode(exprCode);
    releaseRegister(exprCode.place);
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
    }else if(exprCode.type == STRING){
        code << "la $a0, "<< exprCode.place<<endl
        << "li $v0, 4"<<endl
        << "syscall"<<endl;
    }
    return code.str();
}

void EqExpr::genCode(Code &code){
    Code leftSideCode; 
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss<< leftSideCode.code <<endl
        << rightSideCode.code <<endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        string label = getNewLabel("label");
        string finalLabel = getNewLabel("finalLabel");
        ss << "beq " << leftSideCode.place << ", " << rightSideCode.place << ", " << label + "\n";
        ss << "addi " << temp << ", $zero, 0"<<endl << " j " << finalLabel <<endl;
        ss<< label <<":"<<endl<< "addi " << temp << ", $zero, 1"<<endl<<finalLabel<<":"<<endl;
        code.place = temp;
    }else{
        code.type = FLOAT;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
        << rightSideCode.code <<endl;
    }
    code.code = ss.str();
}

void NeqExpr::genCode(Code &code){

}

void GteExpr::genCode(Code &code){

}

void LteExpr::genCode(Code &code){
    Code leftSideCode; 
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        ss << leftSideCode.code <<endl<< rightSideCode.code<<endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss<< "sle "<< temp<< ", "<< leftSideCode.place<< ", "<< rightSideCode.place<<endl;
        code.place = temp;
    }else{
        code.type = FLOAT;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code <<endl<< rightSideCode.code<<endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss<< "c.le.s "<< leftSideCode.place<< ", "<< rightSideCode.place<<endl;
    }
    code.code = ss.str();
}

void GtExpr::genCode(Code &code){
    
}

void LtExpr::genCode(Code &code){
    Code leftSideCode; 
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        ss << leftSideCode.code <<endl<< rightSideCode.code<<endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss<< "slt "<< temp<< ", "<< leftSideCode.place<< ", "<< rightSideCode.place<<endl;
        code.place = temp;
    }else{
        code.type = FLOAT;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code <<endl<< rightSideCode.code<<endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss<< "c.lt.s "<< leftSideCode.place<< ", "<< rightSideCode.place<<endl;
    }
    code.code = ss.str();
}

void LogicalAndExpr::genCode(Code &code){
    Code leftSideCode; 
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    ss<< leftSideCode.code<<endl << rightSideCode.code <<endl;
    releaseRegister(leftSideCode.place);
    releaseRegister(rightSideCode.place);
    string temp = getIntTemp();
    string label = getNewLabel("label");
    string finalLabel = getNewLabel("finalLabel");
    ss<< "addi "<<temp<< ", $zero, 0"<<endl;
    ss<< "beq "<< leftSideCode.place<< ", "<<temp<<", "<< finalLabel<<endl;
    ss<< "beq "<< rightSideCode.place<< ", "<<temp<<", "<< finalLabel<<endl;
    ss<< label<< ":"<<endl<< "addi "<< temp<< ", $zero, 1"<<endl<<finalLabel<<":"<<endl;
    code.place = temp;
    code.code = ss.str();
}

void LogicalOrExpr::genCode(Code &code){
    Code leftSideCode; 
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    ss<< leftSideCode.code<<endl<< rightSideCode.code<<endl;
    releaseRegister(leftSideCode.place);
    releaseRegister(rightSideCode.place);
    string temp = getIntTemp();
    string label = getNewLabel("label");
    string finalLabel = getNewLabel("finalLabel");
    ss<< "addi "<<temp<< ", $zero, 1"<<endl;
    ss<< "beq "<< leftSideCode.place<< ", "<<temp <<", " << finalLabel <<endl;
    ss<< "beq "<<rightSideCode.place<< ", "<<temp <<", " << finalLabel <<endl;
    ss<< label <<":"<<endl<< "addi "<< temp<< ", $zero, 0"<<finalLabel<<":";
    code.place = temp;
    code.code = ss.str();
}

void AssignExpr::genCode(Code &code){
    Code rightSideCode;
    stringstream ss;
    this->expr2->genCode(rightSideCode);
    ss<< rightSideCode.code <<endl;
    string name = ((IdExpr *)this->expr1)->id;
    if(name != ""){
        if(codeGenerationVars.find(name) == codeGenerationVars.end()){
        if(rightSideCode.type == INT)
            ss << "sw "<<rightSideCode.place << ", "<<name <<endl;
        else if(rightSideCode.type == FLOAT)
            ss << "s.s "<<rightSideCode.place << ", "<<name <<endl;
        }else{
            if(rightSideCode.type == INT)
                ss<< "sw "<< rightSideCode.place <<", "<<codeGenerationVars[name]->offset<<"($sp)"<<endl;
            else if(rightSideCode.type == FLOAT)
                ss<< "s.s "<< rightSideCode.place <<", "<<codeGenerationVars[name]->offset<<"($sp)"<<endl;
        }
        releaseRegister(rightSideCode.place);
    }else{
        Code arrayExpr;
        string name = ((ArrayExpr *)this->expr1)->id->id;
        ((ArrayExpr *)this->expr1)->expr->genCode(arrayExpr);
        releaseRegister(arrayExpr.place);
        ss << arrayExpr.code<<endl;
        string temp = getIntTemp();
        string address = getIntTemp();
        if(codeGenerationVars.find(name) == codeGenerationVars.end()){
            ss<< "li $a0, 4"<<endl
            << "mult $a0, "<< arrayExpr.place<<endl
            <<"mflo "<<temp<<endl
            << "la " <<address<< ", "<< name<<endl
            <<"add "<< temp << ", "<< temp << ", "<< address<<endl;
            Code rightSideCode;
            this->expr2->genCode(rightSideCode);
            ss<< rightSideCode.code <<endl
            << "sw "<< rightSideCode.place << ", 0(" <<temp<< ")"<<endl;
        }else{
            ss << "li $a0, 4"<<endl
            << "mult $a0, "<< arrayExpr.place<<endl
            <<"mflo "<<temp<<endl;
            if(!codeGenerationVars[name]->isParameter)
                ss<< "la " + address +", " <<codeGenerationVars[name]->offset<<"($sp)"<<endl;
            else
                ss << "lw "<<address<<", "<<codeGenerationVars[name]->offset<<"($sp)"<<endl;
            ss <<"add "<< temp << ", "<< temp << ", "<< address<<endl;
            Code rightSideCode;
            this->expr2->genCode(rightSideCode);
            ss<< rightSideCode.code <<endl;
            ss<< "sw "<< rightSideCode.place << ", 0("<<temp<<")"<<endl;
        }    
        releaseRegister(temp);     
        releaseRegister(address);     
        releaseRegister(rightSideCode.place);
        releaseRegister(arrayExpr.place);
    }
    code.code = ss.str();
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
