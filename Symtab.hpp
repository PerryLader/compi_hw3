#ifndef _SYMTAB_HPP
#define _SYMTAB_HPP

#include "Node.hpp"
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;
using namespace output;

class Symtab{    
public:
    std::vector<Symbol*> m_symbols;
    Symtab();
    ~Symtab();
    Symbol* addToSymTab(const std::string& type, const std::string& name, const std::string& value, int offset);
    Symbol* addFuncToSymTab(const std::string& type, const std::string& name, const std::string& returnValue);
    void printAllParam();
};

#endif 