#include "utils.hpp"

void isLegalToBreak(int whileCounter){
    if(whileCounter == 0)
    {
        output::errUnexpectedBrk(yylineno);
        exit(0);
    }
}

void isLegalToCont(int whileCounter){
    if(whileCounter == 0)
    {
        output::errUnexpectedCont(yylineno);
        exit(0);
    }
}

void isBoolean(Expression* expr){
    if(expr->m_type != "bool")
    {
        output::errMsmatch(yylineno);
        exit(0);
    }
}

void isLegalTypeUsage(const std::string& type){
    if(type != "int" && type != "byte")
    {
        output::errMsmatch(yylineno);
        exit(0);
    }
}

void isLegalByte(const std::string& value){
    if(stoi(value) > 255)
    {
        output::errByteTooBig(yylineno, value);
        exit(0);
    }
}

bool isFunc(Symbol* sym)
{
    return sym->m_type[0] == '('; 
}

Expression* id_to_Exp(const std::string& name){
    Symbol* sym = parm_stack.findSymbol(name);
    if(sym == nullptr || isFunc(sym))
    {
        output::errUndefind(yylineno, name);
        exit(0);
    }
    return new Expression(sym->m_type, sym->m_value);
}

Expression* call_to_Exp(Call* call){
    if(call->m_value == "void")
    {
        output::errMsmatch(yylineno);
        exit(0);
    }
    
    return new Expression(call->m_type, call->m_value);
}

Expression* Not(Expression* expr){
    isBoolean(expr);
    string newVal = expr->m_value == "true" ? "false" : "true";
    return new Expression("bool", newVal);
}


bool bothAreTrue(Expression* left, Expression* right) {
    return left->m_value == "true" && right->m_value == "true";
}

bool oneIsTrue(Expression* left, Expression* right) {
    return left->m_value == "true" || right->m_value == "true";
}

Expression* And(Expression* left, Expression* right){
    isBoolean(left);
    isBoolean(right);

    string newVal = (bothAreTrue(left, right)) ? "true" : "false";
    return new Expression("bool", newVal);
}

Expression* Or(Expression* left, Expression* right){
    isBoolean(left);
    isBoolean(right);

    string newVal = (oneIsTrue(left, right)) ? "true" : "false";
    return new Expression("bool", newVal);
}

bool isLessThan(const string& operation) {
    return operation == "<";
}

bool isLessThanOrEqual(const string& operation) {
    return operation == "<=";
}

bool isGreaterThan(const string& operation) {
    return operation == ">";
}

bool isGreaterThanOrEqual(const string& operation) {
    return operation == ">=";
}

bool isEqual(const string& operation) {
    return operation == "==";
}

bool isNotEqual(const string& operation) {
    return operation == "!=";
}


Expression* EqualOperations(Expression* left, Op* op, Expression* right) {
    isLegalTypeUsage(left->m_type);
    isLegalTypeUsage(right->m_type);

    string updatedValue;
    string operation = op->m_value;
    int leftVal = stoi(left->m_value);
    int rightVal = stoi(right->m_value);

    if (isLessThan(operation)) {
        updatedValue = leftVal < rightVal ? "true" : "false";
    } else if (isLessThanOrEqual(operation)) {
        updatedValue = leftVal <= rightVal ? "true" : "false";
    } else if (isGreaterThan(operation)) {
        updatedValue = leftVal > rightVal ? "true" : "false";
    } else if (isGreaterThanOrEqual(operation)) {
        updatedValue = leftVal >= rightVal ? "true" : "false";
    } else if (isEqual(operation)) {
        updatedValue = leftVal == rightVal ? "true" : "false";
    } else if (isNotEqual(operation)) {
        updatedValue = leftVal != rightVal ? "true" : "false";
    }

    return new Expression("bool", updatedValue);
}

Expression* Casting(Type* type, Expression* expr){
    isLegalTypeUsage(type->m_value);
    isLegalTypeUsage(expr->m_type);
    
    if(type->m_value == "int" && expr->m_type == "byte")
    {
        return new Expression("int", expr->m_value);
    }
    else if(type->m_value == "byte" && expr->m_type == "int")
    {
        return new Expression("byte", expr->m_value);
    }
    else
    {
        return expr; 
    }
}

Expression* addOrSub(Expression* left, Op* op, Expression* right){
    isLegalTypeUsage(left->m_type);
    isLegalTypeUsage(right->m_type);

    std::string newType = left->m_type == "int" || right->m_type == "int" ? "int" : "byte";
    int newVal = op->m_value == "+" ? stoi(left->m_value) + stoi(right->m_value) 
                            : stoi(left->m_value) - stoi(right->m_value);

    return new Expression(newType, to_string(newVal));
}

Expression* mulDiv(Expression* left, Op* op, Expression* right){
    isLegalTypeUsage(left->m_type);
    isLegalTypeUsage(right->m_type);

    int newVal;
    if (op->m_value == "*") {
        newVal = stoi(left->m_value) * stoi(right->m_value);
    } else if (op->m_value == "/") {
        int rightVal = stoi(right->m_value);
        if (rightVal == 0) {
           
        } else {
            newVal = stoi(left->m_value) / rightVal;
        }
    }

    std::string newType = left->m_type == "int" || right->m_type == "int" ? "int" : "byte";
    

    return new Expression(newType, to_string(newVal));
}

Call* expressionToCall(const std::string& m_name, Expression* expr){
    Symbol* sym = parm_stack.findSymbol(m_name);
    if(sym == nullptr || !isFunc(sym))
    {
        output::errUndefinedFunction(yylineno, m_name);
        exit(0);
    }
    std::string* typeAndArgument = new std::string[2];

    auto firstArg = sym->m_type.find('(');
    auto firstType = sym->m_type.find('>');
    auto lastArg = sym->m_type.find(')');
    
    typeAndArgument[0] = sym->m_type.substr(firstArg + 1, lastArg - firstArg - 1);
    typeAndArgument[1] = sym->m_type.substr(firstType + 1, sym->m_type.size() - firstType - 1);



    if(expr->m_type == typeAndArgument[0] || (expr->m_type == "byte" && typeAndArgument[0] == "int"))
    {
        return new Call(typeAndArgument[1], expr->m_value);
    }
    else
    {
        std::string upperType = std::string(typeAndArgument[0]);
        std::transform(upperType.begin(), upperType.end(), upperType.begin(), ::toupper);
        output::errProtoMismatch(yylineno, m_name, upperType);
        exit(0);
    }
}