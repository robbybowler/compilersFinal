#include "Symbol.h"
#include <cstdlib>
#include <iostream>

SymbolTableClass::SymbolTableClass(){
}

bool SymbolTableClass::Exists(std::string s){
	for (int i = sTable.size() - 1; i > -1; i--) {
		if ( s == sTable[i].mLabel){
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(std::string s){
	for (int i = scope[scope.size() - 1]; i < sTable.size(); i++) {
		if (s == sTable[i].mLabel) {
			std::cerr << "Error duplicate variable.";
			exit(1);
		}
	}
	Variable newVar;
	newVar.mLabel = s;
	newVar.mValue = 0;
	sTable.push_back(newVar);

 /*   if (!exists(s)){
        variable newvar;
        newvar.mlabel = s;
        newvar.mvalue = 0;
        stable.push_back(newvar);
    }
    else{
        std::cerr << "error duplicate variable.";
        exit(1);
    }*/
}

int SymbolTableClass::GetValue(std::string s){
    if (Exists(s)){
		for (int i = sTable.size() - 1; i > -1; i--) {
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
        for( int i = sTable.size()-1; i > -1; i--){
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
	for (int i = sTable.size() - 1; i > -1; i--) {
		if ( s == sTable[i].mLabel){
            return i;
        }
    }
    return -1;
}

int SymbolTableClass::GetCount(){
    return sTable.size();
}

void SymbolTableClass::ScopeIn() {
	scope.push_back(sTable.size());
}

void SymbolTableClass::ScopeOut() {
	for (int i = 0; i < scope[scope.size() - 1]; i++) {
		scope.pop_back();
		sTable.pop_back();
	}
}


