#ifndef _NODE_HPP
#define _NODE_HPP
#include <string>
#include <algorithm>
#include "hw3_output.hpp"

extern int yylineno;

class Node{
public:
    std::string value;
    
    Node(const std::string& value){
        this->value = value;
    }
    virtual ~Node() = default;
};

class Symbol : public Node {
public:
    int offset;
    std::string name;
    std::string type;
    Symbol(const std::string type, const std::string& name, const std::string& value, int offset):
        Node(value), offset(offset), name(name), type(type) {}

    void printSymbol(){
        std::string upperType = std::string(type);
        std::transform(upperType.begin(), upperType.end(), upperType.begin(), ::toupper); //convert the type to uppercase for prints
        output::printID(name, offset, upperType);
    } 
};

class Type : public Node {
public:
    Type(const std::string& type) : Node(type){}
};

class Number: public Node {
public:
    Number(const std::string& value) : Node(value){}
};

class Id: public Node {
public:
    Id(const std::string& name) : Node(name){}
};

class Op: public Node {
public:
    Op(const std::string& op) : Node(op){}
};

class Expression: public Node {
public:
    std::string type;
    Expression(const std::string& type, const std::string& value) : Node(value), type(type){}
};

class Call: public Node {
public:
    std::string type;
    Call(const std::string& type, const std::string& value) : Node(value), type(type){}
};
#endif // _NODE_HPP