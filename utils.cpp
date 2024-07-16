#include "utils.hpp"

void isLegalBreak(int whileCounter){
    if(whileCounter == 0)
    {
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void isLegalContinue(int whileCounter){
    if(whileCounter == 0)
    {
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void isBool(Expression* expr){
    if(expr->m_type != "bool")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void isLegalType(const std::string& type){
    if(type != "int" && type != "byte")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void isLegalByte(const std::string& value){
    if(stoi(value) > 255)
    {
        output::errorByteTooLarge(yylineno, value);
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
        errorUndef(yylineno, name);
        exit(0);
    }
    return new Expression(sym->m_type, sym->m_value);
}

Expression* call_to_Exp(Call* call){
    if(call->m_value == "void")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
    
    return new Expression(call->m_type, call->m_value);
}

Expression* Not(Expression* expr){
    isBool(expr);
    string newVal = expr->m_value == "true" ? "false" : "true";
    return new Expression("bool", newVal);
}

Expression* And(Expression* left, Expression* right){
    isBool(left);
    isBool(right);

    string newVal = (left->m_value == "true" && right->m_value == "true") ? "true" : "false";
    return new Expression("bool", newVal);
}

Expression* Or(Expression* left, Expression* right){
    isBool(left);
    isBool(right);

    string newVal = (left->m_value == "true" || right->m_value == "true") ? "true" : "false";
    return new Expression("bool", newVal);
}

Expression* EqualOperations(Expression* left, Op* op, Expression* right){
    isLegalType(left->m_type);
    isLegalType(right->m_type);

    string newVal;
    string opVal = op->m_value;
    int leftVal = stoi(left->m_value);
    int rightVal = stoi(right->m_value);
    if(opVal == "<")
    {
        newVal = leftVal < rightVal ? "true" : "false";
    }
    else if(opVal == "<=")
    {
        newVal = leftVal <= rightVal ? "true" : "false";
    }
    else if(opVal == ">")
    {
        newVal = leftVal > rightVal ? "true" : "false";
    }
    else if(opVal == ">=")
    {
        newVal = leftVal >= rightVal ? "true" : "false";
    }
    else if(opVal == "==")
    {
        newVal = leftVal == rightVal ? "true" : "false";
    }
    else if(opVal == "!=")
    {
        newVal = leftVal != rightVal ? "true" : "false";
    }
    return new Expression("bool", newVal);
}

Expression* Casting(Type* type, Expression* expr){
    isLegalType(type->m_value);
    isLegalType(expr->m_type);
    
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

Expression* addSub(Expression* left, Op* op, Expression* right){
    isLegalType(left->m_type);
    isLegalType(right->m_type);

    std::string newType = left->m_type == "int" || right->m_type == "int" ? "int" : "byte";
    int newVal = op->m_value == "+" ? stoi(left->m_value) + stoi(right->m_value) 
                            : stoi(left->m_value) - stoi(right->m_value);

    return new Expression(newType, to_string(newVal));
}

Expression* mulDiv(Expression* left, Op* op, Expression* right){
    isLegalType(left->m_type);
    isLegalType(right->m_type);

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

Call* expressionToCall(const std::string& name, Expression* expr){
    Symbol* sym = parm_stack.findSymbol(name);
    if(sym == nullptr || !isFunc(sym))
    {
        errorUndefFunc(yylineno, name);
        exit(0);
    }
    std::string* argAndType= new std::string[2];

    auto argFirst = sym->m_type.find('(');
    auto argLast = sym->m_type.find(')');

    auto typeFirst = sym->m_type.find('>');
    
    argAndType[0] = sym->m_type.substr(argFirst + 1, argLast - argFirst - 1);
    argAndType[1] = sym->m_type.substr(typeFirst + 1, sym->m_type.size() - typeFirst - 1);



    if(expr->m_type == argAndType[0] || (expr->m_type == "byte" && argAndType[0] == "int"))
    {
        return new Call(argAndType[1], expr->m_value);
    }
    else
    {
        std::string upper_type = std::string(argAndType[0]);
        std::transform(upper_type.begin(), upper_type.end(), upper_type.begin(), ::toupper);
        errorPrototypeMismatch(yylineno, name, upper_type);
        exit(0);
    }
}