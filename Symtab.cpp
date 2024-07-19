#include "Symtab.hpp"



Symtab::Symtab(){}

Symtab::~Symtab(){
    for(auto s : m_symbols)
    {
        delete s;
    }
}

Symbol* Symtab::addToSymbolTable(const string& m_type, const string& m_name, const string& m_value, int offset){
    Symbol* s = nullptr;
    try{
        s = new Symbol(m_type, m_name, m_value, offset);
    }
    catch(const exception& e){
        cout << e.what() << '\n';
        cout << "Type: " << m_type << " Name: " << m_name << " Value: " << m_value << endl;
        
        throw;
    }

    m_symbols.push_back(s);
    return s;
}

Symbol* Symtab::addFuncToSymbolTable(const string& m_type, const string& m_name, const string& retVal){
    Symbol* s = new Symbol(m_type, m_name, retVal, 0);
    m_symbols.push_back(s);
    return s;
}

void Symtab::printAllParam(){
    for(auto s : m_symbols)
    {
        s->printSymbol();
    }
}