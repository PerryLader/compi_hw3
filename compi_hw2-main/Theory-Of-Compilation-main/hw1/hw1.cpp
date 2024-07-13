#include "tokens.hpp"
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <exception>
using namespace std;

const vector<string> tokens = 
{
	"",
	"VOID",
    "INT",
    "BYTE",
    "B",
    "BOOL",
    "AND",
    "OR",
    "NOT",
    "TRUE",
    "FALSE",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE",
    "BREAK",
    "CONTINUE", 
    "SC",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "ASSIGN",
    "RELOP",
    "BINOP",
    "COMMENT",
    "ID",
    "NUM",
    "STRING"
};
void simplePrint(int token);
void simplePrint(int token, string customContent);
void printString();

int main()
{
	int token;
	while(token = yylex())
	{
        switch (token){
            case COMMENT:
                simplePrint(token, "//");
                break;
            
            case STRING_START:
                printString();
                break;

            case UNRECOGNIZED_SYMBOL:
                std::cout << "Error " << yytext << std::endl;
		        exit(0);

            default:
                simplePrint(token);
        }
	}
	return 0;
}

void simplePrint(int token){
	cout << yylineno << " " << tokens[token] << " " << yytext << endl;
}

void simplePrint(int token, string customContent){
	cout << yylineno << " " << tokens[token] << " " << customContent << endl;
}

void printString(){
    string stringContent = "", lexema, escaped0String;
    int token, hex;
    bool escaped0 = false;

    while((token = yylex()) != STRING_END){
        switch (token){
            case STRING_ESCAPE_N:
                stringContent += "\n";
                break;
            
            case STRING_ESCAPE_R:
                stringContent += "\r";
                break;
            
            case STRING_ESCAPE_T:
                stringContent += "\t";
                break;

            case STRING_ESCAPE_BACKSLASH:
                stringContent += "\\";
                break;

            case STRING_ESCAPE_QUOTES:
                stringContent += "\"";
                break;
            
            case STRING_ESCAPE_HEX:
                //extract the hex code
                lexema = yytext;
                lexema = lexema.substr(2, lexema.size() - 1);
                hex = stoi(lexema, 0, 16);
                if ((hex >= 0x20 && hex <= 0x7E) || hex == 0x09 || hex == 0x0A || hex == 0x0D){
                    stringContent += static_cast<char>(hex);
                }
                else{
                    lexema = yytext;
                    cout << "Error undefined escape sequence " << lexema.substr(1) << endl;
                    exit(0);
                }
                break;

            case STRING_ESCAPE_0:
                //std::string doesn't append \0 - must truncate manually
                if(!escaped0)
                {
                    escaped0 = true;
                    escaped0String = stringContent;
                }
                break;

            case STRING_CHAR:
                stringContent += yytext;
                break;

            case UNRECOGNIZED_SYMBOL:
                lexema = yytext;
                cout << "Error undefined escape sequence " << lexema.substr(1) << endl;
                exit(0);
                break;
            
            case UNCLOSED_STRING:
                cout << "Error unclosed string" << std::endl;
		        exit(0);
                break;

            case END_OF_FILE: //Catch EOF during string
                cout << "Error unclosed string" << std::endl;
		        exit(0);
                break;

            case UNPRINTABLE_CHAR:
                cout << "Error " << yytext << endl;
                exit(0);
                break;
                
            default:
                throw new out_of_range("FATAL ERROR! We should never be here!");
                break;
        }
    }
    string final = escaped0 ? escaped0String : stringContent;
    simplePrint(STRING, final);
}
