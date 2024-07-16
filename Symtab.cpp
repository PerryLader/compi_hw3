#include "Symtab.hpp"



Symtab::Symtab(){}

Symtab::~Symtab(){
    for(auto s : m_symbols)
    {
        delete s;
    }
}

Symbol* Symtab::addToSymTab(const string& type, const string& name, const string& value, int offset){
    Symbol* s = nullptr;
    try{
        s = new Symbol(type, name, value, offset);
    }
    catch(const exception& e){
        cout << e.what() << '\n';
        cout << "Type: " << type << " Name: " << name << " Value: " << value << endl;
        
        throw;
    }

    m_symbols.push_back(s);
    return s;
}

Symbol* Symtab::addFuncToSymTab(const string& type, const string& name, const string& returnValue){
    Symbol* s = new Symbol(type, name, returnValue, 0);
    m_symbols.push_back(s);
    return s;
}

void Symtab::printAllParam(){
    for(auto s : m_symbols)
    {
        s->printSymbol();
    }
}