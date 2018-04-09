
#include "Token.h"
#include <iostream>
#include "Debug.h"

using namespace std;

TokenClass::TokenClass(){

}


TokenClass::TokenClass(TokenType type, const string & lexeme){
    mType = type;
    mLexeme = lexeme;
}

void TokenClass::CheckReserved(){
    if (mType == IDENTIFIER_TOKEN){
        if (mLexeme == "void"){
            mType = VOID_TOKEN;
        }else if(mLexeme == "main"){
            mType = MAIN_TOKEN;
        }else if(mLexeme == "int"){
            mType = INT_TOKEN;
        }else if(mLexeme == "cout"){
            mType = COUT_TOKEN;
        }
        else if(mLexeme == "if"){
            mType = IF_TOKEN;
        }
        else if(mLexeme == "else"){
            mType = ELSE_TOKEN;
        }
        else if(mLexeme == "while"){
            mType = WHILE_TOKEN;
        }
        else if(mLexeme == "begin"){
            mType = LCURLY_TOKEN;
        }
        else if(mLexeme == "end"){
            mType = RCURLY_TOKEN;
        }
    }
}

std::ostream & operator<<(std::ostream & out, const TokenClass & tc){
    out << tc.GetTokenType() << " " << tc.GetTokenTypeName() << " " << tc.GetLexeme();
    return out;
}
