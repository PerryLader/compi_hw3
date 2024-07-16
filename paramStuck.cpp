

#include "paramStuck.hpp"

using namespace output;

void parmStack::addGlobalScope() {
    auto* symtab = new Symtab();
    m_symtabs.push_back(symtab); 
    symtab->addFuncToSymTab(makeFunctionType("string", "void"), "print", "void");
    symtab->addFuncToSymTab(makeFunctionType("int", "void"), "printi", "void");
    symtab->addFuncToSymTab(makeFunctionType("int", "int"), "readi", "0");
}

Symbol* parmStack::findSymbol(const std::string& name){
    for(auto s : m_symtabs)
    {
        for(auto sym : s->m_symbols)
        {
            if(sym->m_name == name)
            {
                return sym;
            }
        }
    }

    return nullptr;
}

void parmStack::addScope() {
    if(m_offsetsStuck.empty())
    {
        m_offsetsStuck.push(0);
    }
    else
    {
        m_offsetsStuck.push(m_offsetsStuck.top());
    }
    m_symtabs.push_back(new Symtab());
}

void parmStack::popAndPrintScope() {
    endScope();
    m_symtabs.back()->printAllParam();
    m_symtabs.pop_back();
    m_offsetsStuck.pop();
}

void parmStack::checkType(const std::string& type, Expression* expr){
    if(expr->m_type == "byte" && type == "int")
    {
        return;
    }
    if(expr->m_type != type)
    {
        errorMismatch(yylineno);
        exit(0);
    }
}

Symbol* parmStack::addNewSymbolNoExp(const std::string& type, const std::string& name) {
    std::string defaultValue = type == "bool" ? "false" : "0";
    Symbol* symbol = addNewSymbolWithExp(type, name, new Expression(type, defaultValue));
    return symbol;

}

Symbol* parmStack::addNewSymbolWithExp(const std::string& sym_type, const std::string& name, Expression* value) {
  
    if(findSymbol(name) != nullptr)
    {
        errorDef(yylineno, name);
        exit(0);
    }
    checkType(sym_type, value);

    Symbol* symbol = m_symtabs.back()->addToSymTab(sym_type, name, value->m_value, m_offsetsStuck.top());
    if(symbol){
        m_offsetsStuck.top()++;
    }
    return symbol;
}

void parmStack::assignToSymbol(const std::string& name, Expression* val){
   
    Symbol* sym = findSymbol(name);
    if(sym == nullptr || sym->m_type[0] == '(' /* isFunc(sym) */){
       
        errorUndef(yylineno, name);
        exit(0);
    }
    checkType(sym->m_type, val);
    sym->m_value = val->m_value;
}