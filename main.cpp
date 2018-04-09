
#include <cstdlib>
#include <string>
#include "Token.h"
#include "StateMachine.h"
#include <iostream>
#include "Node.h"
#include "Parser.h"
#include "Scanner.h"
#include "Symbol.h"
#include <chrono>
#include <thread>

int main() {

//    TokenClass tc;
//    ScannerClass scanner("test.txt");
//
//    while(true){
//
//        tc = scanner.GetNextToken();
//        std::cout << tc << " " << scanner.GetLineNumber() << std::endl;
//        if (tc.GetTokenType() == ENDFILE_TOKEN){
//            break;
//        }
//    }



    ScannerClass sc("/Users/robbybowler/CLionProjects/compiler/test.txt");
    SymbolTableClass st;
    ParserClass pc(&sc, &st);
    StartNode * s = pc.Start();
    s->Interpret();








//    SymbolTableClass ST;
//    IdentifierNode * identifierOne = new IdentifierNode("sum", &ST);
//    DeclarationStatementNode * declarationOne = new DeclarationStatementNode(identifierOne);
//    IdentifierNode * identifierTwo = new IdentifierNode("sum", &ST);
//    IntegerNode * integer = new IntegerNode(10);
//    AssignmentStatementNode * assignmentStatementNode = new AssignmentStatementNode(identifierTwo, integer);
//    IdentifierNode * identifierThreee = new IdentifierNode("sum", &ST);
//    IntegerNode * integerTwo = new IntegerNode(20);
//    PlusNode * plus = new PlusNode(identifierThreee, integerTwo);
//    CoutStatementNode * cout = new CoutStatementNode(plus);
//    StatementGroupNode * stateGroup = new StatementGroupNode();
//    stateGroup->AddStatement(declarationOne);
//    stateGroup->AddStatement(assignmentStatementNode);
//    stateGroup->AddStatement(cout);
//    BlockNode * blockNode = new BlockNode(stateGroup);
//    ProgramNode * programNode = new ProgramNode(blockNode);
//    StartNode * start = new StartNode(programNode);
//    delete start;
//    return 0;

}