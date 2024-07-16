#ifndef _PARAM_HPP
#define _PARAM_HPP

#include "Node.hpp"
#include <stack>
#include <vector>
#include "Symtab.hpp"
#include "hw3_output.hpp"

class parmStack{
    void addGlobalScope();
    void checkType(const std::string& type, Expression* expr);
public:
    std::vector<Symtab*> m_symtabs;
    std::stack<int> m_offsetsStuck;

    parmStack(){
        m_offsetsStuck.push(0);
        addGlobalScope();
    }

    void addScope();
    void popAndPrintScope();
    Symbol* addNewSymbolNoExp(const std::string& type, const std::string& name);
    Symbol* addNewSymbolWithExp(const std::string& type, const std::string& name, Expression* value);
    Symbol* findSymbol(const std::string& name);
    void assignToSymbol(const std::string& name, Expression* val);
};
#endif