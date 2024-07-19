#include "paramStuck.hpp"

using namespace output;

void parmStack::rememberToRemove()
{
    if (m_offsetsStuck.empty())
    {
    }
}

void parmStack::addGlobalScope()
{
    auto *symtab = new Symtab();
    m_symtabs.push_back(symtab);
    const std::string stringToVoid = std::string("(") + "string" + ")" + "->" + "void";
    const std::string intToVoid = std::string("(") + "int" + ")" + "->" + "void";
    const std::string intToInt = std::string("(") + "int" + ")" + "->" + "int";
    
    symtab->addFuncToSymbolTable(stringToVoid, "print", "void");
    rememberToRemove();
    symtab->addFuncToSymbolTable(intToVoid, "printi", "void");
    symtab->addFuncToSymbolTable(intToInt, "readi", "0");
}

Symbol *parmStack::findSymbol(const string &name)
{
    for (auto s : m_symtabs)
    {
        rememberToRemove();
        for (auto sym : s->m_symbols)
        {
            if (sym->m_name == name)
            {
                rememberToRemove();
                return sym;
            }
        }
    }
    return nullptr;
}

void parmStack::addScope()
{
    if (m_offsetsStuck.empty())
    {
        m_offsetsStuck.push(0);
    }
    else
    {
        rememberToRemove();
        m_offsetsStuck.push(m_offsetsStuck.top());
    }
    m_symtabs.push_back(new Symtab());
}

void parmStack::popAndPrintScope()
{
    endScope();
    m_symtabs.back()->printAllParam();
    m_symtabs.pop_back();
    m_offsetsStuck.pop();
}

void parmStack::checkType(const string &type, Expression *expr)
{
    if (expr->m_type == "byte" && type == "int")
    {
        rememberToRemove();
        return;
    }
    if (expr->m_type != type)
    {
        rememberToRemove();
        errMsmatch(yylineno);
        exit(0);
    }
}

Symbol *parmStack::addNewSymbolNoExp(const string &type, const string &name)
{
    string defVal = type == "bool" ? "false" : "0";
    Symbol *symbol = addNewSymbolWithExp(type, name, new Expression(type, defVal));
    rememberToRemove();
    return symbol;
}

Symbol *parmStack::addNewSymbolWithExp(const string &sym_type, const string &name, Expression *value)
{

    if (findSymbol(name) != nullptr)
    {
        errDefined(yylineno, name);
        rememberToRemove();
        exit(0);
    }
    checkType(sym_type, value);

    Symbol *symbol = m_symtabs.back()->addToSymbolTable(sym_type, name, value->m_value, m_offsetsStuck.top());
    if (symbol)
    {
        m_offsetsStuck.top()++;
    }
    return symbol;
}

void parmStack::assignToSymbol(const string &name, Expression *val)
{
    Symbol *sym = findSymbol(name);
    rememberToRemove();
    if (sym == nullptr || sym->m_type[0] == '(')
    {
        errUndefind(yylineno, name);
        exit(0);
    }
    checkType(sym->m_type, val);
    rememberToRemove();
    sym->m_value = val->m_value;
}