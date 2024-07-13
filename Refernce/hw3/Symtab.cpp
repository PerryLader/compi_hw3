#include "Symtab.hpp"

using namespace output;


void Stacks::addGlobalScope() {
    auto* symtab = new Symtab();
    symtabs.push_back(symtab); //Adds symtab with offset 0 (when called at ctor)
    
    // add print and printi and readi to the global scope
    symtab->insertFunc(makeFunctionType("string", "void"), "print", "void");
    symtab->insertFunc(makeFunctionType("int", "void"), "printi", "void");
    symtab->insertFunc(makeFunctionType("int", "int"), "readi", "0");
}

Symbol* Stacks::findSymbol(const std::string& name){
    for(auto s : symtabs)
    {
        for(auto sym : s->symbols)
        {
            if(sym->name == name)
            {
                return sym;
            }
        }
    }

    return nullptr;
}

void Stacks::addNewScope() {
    if(offsets.empty())
    {
        offsets.push(0);
    }
    else
    {
        offsets.push(offsets.top());
    }
    symtabs.push_back(new Symtab());
}

void Stacks::popAndPrintScope() {
    endScope();
    symtabs.back()->print();
    symtabs.pop_back();
    offsets.pop();
}

void Stacks::checkTypeCompatibility(const std::string& type, Expression* expr){
    if(expr->type == "byte" && type == "int")
    {
        return;
    }
    if(expr->type != type)
    {
        errorMismatch(yylineno);
        exit(0);
    }
}

Symbol* Stacks::addSymbol(const std::string& type, const std::string& name) {
    std::string defaultValue = type == "bool" ? "false" : "0";
    Symbol* symbol = addSymbol(type, name, new Expression(type, defaultValue));
    return symbol;

}

Symbol* Stacks::addSymbol(const std::string& sym_type, const std::string& name, Expression* value) {
    // cout << "Adding symbol: " << sym_type << " " << name << std::endl;
    // cout << "to symtab ";
    // symtabs.back()->print();
    // cout << " with offset " << offsets.top() << std::endl;

    //check if name is already used
    if(findSymbol(name) != nullptr)
    {
        errorDef(yylineno, name);
        exit(0);
    }
    checkTypeCompatibility(sym_type, value);

    // cout << "Adding symbol: " << sym_type;
    // cout << " " << name ;
    // cout << "val " << value->value;
    // cout << "to symtab " << symtabs.back() ;
    // cout << " with offset " << offsets.top();
    // cout << std::endl;
    Symbol* symbol = symtabs.back()->insert(sym_type, name, value->value, offsets.top());
    if(symbol){
        offsets.top()++;
    }
    return symbol;
}

void Stacks::assignToSymbol(const std::string& name, Expression* val){
    // cout << "assignToSymbol: " << " " << name << std::endl;
    // cout << "to symtab ";
    // symtabs.back()->print();
    // cout << " with offset " << offsets.top() << std::endl;

    Symbol* sym = findSymbol(name);
    if(sym == nullptr || sym->type[0] == '(' /* isFunc(sym) */){
        // std::cout << "assignToSymbol" << std::endl;
        errorUndef(yylineno, name);
        exit(0);
    }
    checkTypeCompatibility(sym->type, val);
    sym->value = val->value;
}