#include "Symtab.hpp"



Symtab::Symtab(){}

Symtab::~Symtab(){
    for(auto s : m_symbols)
    {
        delete s;
    }
}

Symbol* Symtab::addToSymTab(const std::string& type, const std::string& name, const std::string& value, int offset){
    Symbol* s = nullptr;
    try{
        s = new Symbol(type, name, value, offset);
    }
    catch(const std::exception& e){
        std::cout << e.what() << '\n';
        std::cout << "Type: " << type << " Name: " << name << " Value: " << value << std::endl;
        
        throw;
    }

    m_symbols.push_back(s);
    return s;
}

Symbol* Symtab::addFuncToSymTab(const std::string& type, const std::string& name, const std::string& returnValue){
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