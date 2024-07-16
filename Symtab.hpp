#ifndef _SYMTAB_HPP
#define _SYMTAB_HPP

#include "Node.hpp"
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Symtab{    
public:
    std::vector<Symbol*> m_symbols;
    Symtab();
    ~Symtab();
    Symbol* addToSymTab(const string& type, const string& name, const string& value, int offset);
    Symbol* addFuncToSymTab(const string& type, const string& name, const string& returnValue);
    void printAllParam();
};

#endif 