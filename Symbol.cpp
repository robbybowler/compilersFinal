#include "Symbol.h"
#include <cstdlib>
#include <iostream>

SymbolTableClass::SymbolTableClass(){
}

bool SymbolTableClass::Exists(std::string s){
    for( int i = 0; i < sTable.size(); i++){
        if ( s == sTable[i].mLabel){
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(std::string s){
    if (!Exists(s)){
        Variable newVar;
        newVar.mLabel = s;
        newVar.mValue = 0;
        sTable.push_back(newVar);
    }
    else{
        std::cerr << "Error duplicate variable.";
        exit(1);
    }
}

int SymbolTableClass::GetValue(std::string s){
    if (Exists(s)){
        for( int i = 0; i < sTable.size(); i++){
            if ( s == sTable[i].mLabel){
                return sTable[i].mValue;
            }
        }
    }
    std::cerr << "Variable" << s << "does not exists.";

    exit(1);
}

void SymbolTableClass::SetValue(std::string s, int v){
    if (Exists(s)){
        for( int i = 0; i < sTable.size(); i++){
            if ( s == sTable[i].mLabel){
                sTable[i].mValue = v;
            }
        }
    }
    else{
        std::cerr << "Error setting value";

        exit(1);
    }
}

int SymbolTableClass::GetIndex(std::string s){
    for( int i = 0; i < sTable.size(); i++){
        if ( s == sTable[i].mLabel){
            return i;
        }
    }
    return -1;
}

int SymbolTableClass::GetCount(){
    return sTable.size();
}
