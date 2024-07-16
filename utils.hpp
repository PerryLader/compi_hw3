#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "paramStuck.hpp"
#include "Symtab.hpp"
#include "hw3_output.hpp"

using namespace std;
extern parmStack parm_stack;

void isLegalBreak(int whileCounter);

void isLegalContinue(int whileCounter);

void isBool(Expression* expr);

void isLegalType(const std::string& type);

void isLegalByte(const std::string& value);

bool isFunc(Symbol* sym);

Expression* id_to_Exp(const std::string& name);

Expression* call_to_Exp(Call* call);

Expression* Not(Expression* expr);
Expression* And(Expression* left, Expression* right);

Expression* Or(Expression* left, Expression* right);

Expression* EqualOperations(Expression* left, Op* op, Expression* right);

Expression* Casting(Type* type, Expression* expr);

Expression* addSub(Expression* left, Op* op, Expression* right);

Expression* mulDiv(Expression* left, Op* op, Expression* right);


Call* expressionToCall(const std::string& name, Expression* expr);
#endif