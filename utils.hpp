#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "paramStuck.hpp"
#include "Symtab.hpp"
#include "hw3_output.hpp"

using namespace std;
extern parmStack parm_stack;

void isLegalToBreak(int whileCounter);

void isLegalToCont(int whileCounter);

void isBoolean(Expression *expr);

void isLegalTypeUsage(const std::string &type);

void isLegalByte(const std::string &value);

bool bothAreTrue(Expression* left, Expression* right);

bool oneIsTrue(Expression* left, Expression* right);

bool isFunc(Symbol *sym);

bool isLessThan(const string &operation);

bool isLessThanOrEqual(const string &operation);

bool isGreaterThan(const string &operation);

bool isGreaterThanOrEqual(const string &operation);

bool isEqual(const string &operation);

bool isNotEqual(const string &operation);

Expression *id_to_Exp(const std::string &name);

Expression *call_to_Exp(Call *call);

Expression *Not(Expression *expr);
Expression *And(Expression *left, Expression *right);

Expression *Or(Expression *left, Expression *right);

Expression *EqualOperations(Expression *left, Op *op, Expression *right);

Expression *Casting(Type *type, Expression *expr);

Expression *addOrSub(Expression *left, Op *op, Expression *right);

Expression *mulDiv(Expression *left, Op *op, Expression *right);

Call *expressionToCall(const std::string &name, Expression *expr);
#endif