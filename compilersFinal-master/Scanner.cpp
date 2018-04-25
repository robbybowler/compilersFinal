

#include "Scanner.h"
#include <iostream>
#include "StateMachine.h"
#include "Debug.h"


ScannerClass::ScannerClass(std::string filename){
    mFin.open(filename);
    mLineNumber = 1;
    if(!mFin){
        std::cout << mFin.get();
        exit(1);
    }
}

int ScannerClass::GetLineNumber(){
    return mLineNumber;
}


TokenClass ScannerClass::GetNextToken(){

    StateMachineClass stateMachine;
    TokenType t;
    std::string lexeme;
    MachineState UpdatedState = START_STATE;
    char c;
    do{
        c = mFin.get();
        lexeme += c;
        UpdatedState = stateMachine.UpdateState(c,t);
        if (UpdatedState == START_STATE || UpdatedState == ENDFILE_STATE){
            lexeme = "";
            if (c == '\n'){
                mLineNumber ++;
            }
        }
    }while(UpdatedState != CANTMOVE_STATE);

    mFin.unget();

    lexeme.pop_back();
    TokenClass tc(t,lexeme);
    tc.CheckReserved();
    return tc;

}

TokenClass ScannerClass::PeekNextToken(){
    int lineNum = mLineNumber;
    std::streampos position = mFin.tellg();
    TokenClass tc = GetNextToken();
    if(!mFin) // if we triggered EOF, then seekg doesn't work,
        mFin.clear();// unless we first clear()
    mFin.seekg(position);

	position = mFin.tellg(); // for debugging...

    mLineNumber = lineNum;
    return tc;

}
