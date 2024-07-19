#ifndef _PARAM_HPP
#define _PARAM_HPP

#include "Node.hpp"
#include <stack>
#include <vector>
#include "Symtab.hpp"
#include "hw3_output.hpp"
using namespace std;

class parmStack
{
    void addGlobalScope();
    void checkType(const string &type, Expression *expr);

public:
    vector<Symtab *> m_symtabs;
    stack<int> m_offsetsStuck;

    parmStack()
    {
        m_offsetsStuck.push(0);
        addGlobalScope();
    }

    void addScope();
    void popAndPrintScope();
    Symbol *addNewSymbolNoExp(const string &type, const string &name);
    Symbol *addNewSymbolWithExp(const string &type, const string &name, Expression *value);
    Symbol *findSymbol(const string &name);
    void assignToSymbol(const string &name, Expression *val);

private:
    void rememberToRemove();
};
#endif