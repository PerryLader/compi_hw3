#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include "Symtab.hpp"
#include "hw3_output.hpp"

using namespace std;
extern Stacks stacks;

void checkBreakInWhile(int whileCounter){
    if(whileCounter == 0)
    {
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void checkContinueInWhile(int whileCounter){
    if(whileCounter == 0)
    {
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void checkBool(Expression* expr){
    if(expr->type != "bool")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void numTypeCheck(const std::string& type){
    if(type != "int" && type != "byte")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

void checkByteLiteral(const std::string& value){
    if(stoi(value) > 255)
    {
        output::errorByteTooLarge(yylineno, value);
        exit(0);
    }
}

bool isFunc(Symbol* sym)
{
    return sym->type[0] == '('; // (only) function types start with '('
}

Expression* exprById(const std::string& name){
    Symbol* sym = stacks.findSymbol(name);
    if(sym == nullptr || isFunc(sym))
    {
        errorUndef(yylineno, name);
        exit(0);
    }
    return new Expression(sym->type, sym->value);
}

Expression* exprByCall(Call* call){
    if(call->value == "void")
    {
        output::errorMismatch(yylineno);
        exit(0);
    }
    
    return new Expression(call->type, call->value);
}

Expression* exprNot(Expression* expr){
    checkBool(expr);
    string newVal = expr->value == "true" ? "false" : "true";
    return new Expression("bool", newVal);
}

Expression* exprAnd(Expression* left, Expression* right){
    checkBool(left);
    checkBool(right);

    string newVal = (left->value == "true" && right->value == "true") ? "true" : "false";
    return new Expression("bool", newVal);
}

Expression* exprOr(Expression* left, Expression* right){
    checkBool(left);
    checkBool(right);

    string newVal = (left->value == "true" || right->value == "true") ? "true" : "false";
    return new Expression("bool", newVal);
}

Expression* exprRelop(Expression* left, Op* op, Expression* right){
    numTypeCheck(left->type);
    numTypeCheck(right->type);

    string newVal;
    string opVal = op->value;
    int leftVal = stoi(left->value);
    int rightVal = stoi(right->value);
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

Expression* exprCast(Type* type, Expression* expr){
    numTypeCheck(type->value);
    numTypeCheck(expr->type);
    
    if(type->value == "int" && expr->type == "byte")
    {
        return new Expression("int", expr->value);
    }
    else if(type->value == "byte" && expr->type == "int")
    {
        return new Expression("byte", expr->value);
    }
    else
    {
        return expr; // no need to cast
    }
}

Expression* exprAdditive(Expression* left, Op* op, Expression* right){
    numTypeCheck(left->type);
    numTypeCheck(right->type);

    std::string newType = left->type == "int" || right->type == "int" ? "int" : "byte";
    int newVal = op->value == "+" ? stoi(left->value) + stoi(right->value) 
                             /*-*/: stoi(left->value) - stoi(right->value);

    return new Expression(newType, to_string(newVal));
}

Expression* exprMultiplicative(Expression* left, Op* op, Expression* right){
    numTypeCheck(left->type);
    numTypeCheck(right->type);

    int newVal;
    if (op->value == "*") {
        newVal = stoi(left->value) * stoi(right->value);
    } else if (op->value == "/") {
        int rightVal = stoi(right->value);
        if (rightVal == 0) {
            // Handle division by zero error
            // You can throw an exception, return an error value, or handle it in any other appropriate way
        } else {
            newVal = stoi(left->value) / rightVal;
        }
    }

    std::string newType = left->type == "int" || right->type == "int" ? "int" : "byte";
    // int newVal = op->value == "*" ? stoi(left->value) * stoi(right->value) 
    //                          /*/*/: stoi(left->value) / stoi(right->value);

    return new Expression(newType, to_string(newVal));
}

std::string* argAndTypeFromFunc(Symbol* func){
    std::string* ret = new std::string[2];

    //(Arg)->Type
    auto argFirst = func->type.find('(');
    auto argLast = func->type.find(')');

    auto typeFirst = func->type.find('>');
    
    ret[0] = func->type.substr(argFirst + 1, argLast - argFirst - 1);
    ret[1] = func->type.substr(typeFirst + 1, func->type.size() - typeFirst - 1);
    return ret;
}

Call* parseFunc(const std::string& name, Expression* expr){
    Symbol* sym = stacks.findSymbol(name);
    if(sym == nullptr || !isFunc(sym))
    {
        errorUndefFunc(yylineno, name);
        exit(0);
    }

    std::string* argAndType = argAndTypeFromFunc(sym);
    if(expr->type == argAndType[0] || (expr->type == "byte" && argAndType[0] == "int"))
    {
        return new Call(argAndType[1], expr->value);
    }
    else
    {
        std::string upper_type = std::string(argAndType[0]);
        std::transform(upper_type.begin(), upper_type.end(), upper_type.begin(), ::toupper);
        errorPrototypeMismatch(yylineno, name, upper_type);
        exit(0);
    }
}

#endif // _UTILITY_HPP