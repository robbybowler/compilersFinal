#pragma once

#include "Scanner.h"
#include "Symbol.h"



class ParserClass{
public:
    ParserClass(ScannerClass * sc, SymbolTableClass * st);
    StartNode * Start();
    ProgramNode * Program();
    BlockNode * Block();
    StatementGroupNode * StatementGroup();
    StatementNode *  Statement();
    DeclarationStatementNode * DeclarationStatement();
    AssignmentStatementNode * AssignmentStatememt();
    IfStatementNode *  IfStatement();
    IfStatementNode *  ElseStatement();
    WhileStatementNode * WhileStatement();
    CoutStatementNode * CoutStatement();
    TokenClass Match(TokenType expectedType);
    ExpressionNode * Expression();
    ExpressionNode * LogicalOr();
    ExpressionNode * LogicalAnd();
    ExpressionNode * Relational();
    ExpressionNode * Exponent();
    ExpressionNode * PlusMinus();
    ExpressionNode * TimesDivide();
    ExpressionNode *  Factor();
    IdentifierNode * Identifier();
    IntegerNode * Integer();



private:
    ScannerClass * mScanner;
    SymbolTableClass * mSymbolTable;
};