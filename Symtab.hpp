#ifndef _SYMTAB_HPP
#define _SYMTAB_HPP

#include "Node.hpp"
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Symtab{    
public:
    std::vector<Symbol*> m_symbols;
    Symtab();
    ~Symtab();
    Symbol* addToSymbolTable(const string& m_type, const string& m_name, const string& m_value, int offset);
    Symbol* addFuncToSymbolTable(const string& m_type, const string& m_name, const string& retVal);
    void printAllParam();
};

#endif 