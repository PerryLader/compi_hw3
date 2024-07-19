#include <iostream>
#include "hw3_output.hpp"
#include <sstream>

using namespace std;

void output::endScope(){
    cout << "---end scope---" << endl;
}

void output::printID(const string& id, int offset, const string& type) {
    cout << id << " " << type <<  " " << offset <<  endl;
}

void output::errorLex(int lineno){
    cout << "line " << lineno << ":" << " lexical error" << endl;
}

void output::errorSyn(int lineno){
    cout << "line " << lineno << ":" << " syntax error" << endl;
}

void output::errUndefind(int lineno, const string& id){
    cout << "line " << lineno << ":" << " variable " << id << " is not defined" << endl;
}

void output::errDefined(int lineno, const string& id){
    cout << "line " << lineno << ":" << " identifier " << id << " is already defined" << endl;
}

void output::errUndefinedFunction(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " function " << id << " is not defined" << endl;
}

void output::errMsmatch(int lineno){
    cout << "line " << lineno << ":" << " type mismatch" << endl;
}

void output::errProtoMismatch(int lineno, const string& id, const string &type) {
    cout << "line " << lineno << ": prototype mismatch, function " << id << " expects arguments " << type << endl;
}

void output::errUnexpectedBrk(int lineno) {
    cout << "line " << lineno << ":" << " unexpected break statement" << endl;
}

void output::errUnexpectedCont(int lineno) {
    cout << "line " << lineno << ":" << " unexpected continue statement" << endl;	
}

void output::errByteTooBig(int lineno, const string& value) {
    cout << "line " << lineno << ": byte value " << value << " out of range" << endl;
}