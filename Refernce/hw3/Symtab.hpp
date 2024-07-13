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
    std::vector<Symbol*> symbols;

    Symtab(){
    }

    ~Symtab(){
        for(auto s : symbols)
        {
            delete s;
        }
    }

    Symbol* insert(const std::string& type, const std::string& name, const std::string& value, int offset){
        Symbol* s = nullptr;
        try{
            s = new Symbol(type, name, value, offset);
        }
        catch(const std::exception& e){
            std::cout << e.what() << '\n';
            //print all vars function insert got
            std::cout << "Type: " << type << " Name: " << name << " Value: " << value << std::endl;
            //throw e
            throw;
        }

        // offsets.top()++;
        symbols.push_back(s);
        return s;
    }

    //Function offsets are always 0 and don't affect id offsets
    Symbol* insertFunc(const std::string& type, const std::string& name, const std::string& returnValue){
        Symbol* s = new Symbol(type, name, returnValue, 0);
        symbols.push_back(s);
        return s;
    }

    void print(){
        for(auto s : symbols)
        {
            s->printSymbol();
        }
    }
};

class Stacks{
    void addGlobalScope();
    void checkTypeCompatibility(const std::string& type, Expression* expr);
public:
    std::vector<Symtab*> symtabs;
    std::stack<int> offsets;

    Stacks(){
        offsets.push(0);
        addGlobalScope();
    }

    void addNewScope();
    void popAndPrintScope();
    Symbol* addSymbol(const std::string& type, const std::string& name);
    Symbol* addSymbol(const std::string& type, const std::string& name, Expression* value);
    Symbol* findSymbol(const std::string& name);
    void assignToSymbol(const std::string& name, Expression* val);
};


#endif // _SYMTAB_HPP