#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>
using namespace std;

namespace output
{
    void endScope();
    void errUnexpectedCont(int lineno);
    void errByteTooBig(int lineno, const string &value);
    void printID(const string &id, int offset, const string &type);
    void errorLex(int lineno);
    void errorSyn(int lineno);
    void errUndefind(int lineno, const string &id);
    void errDefined(int lineno, const string &id);
    void errUndefinedFunction(int lineno, const string &id);
    void errMsmatch(int lineno);
    void errProtoMismatch(int lineno, const string &id, const string &type);
    void errUnexpectedBrk(int lineno);
}

#endif