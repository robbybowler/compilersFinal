#include "Token.h"
#include "Node.h"
#include "Parser.h"
#include "Debug.h"
#include "stdlib.h"
#include "cstring"
#include <vector>


#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#endif //COMPILER_PARSER_H



ParserClass::ParserClass(ScannerClass * sc, SymbolTableClass * st){
    mScanner = sc;
    mSymbolTable = st;
}

//<Start> 	→ <Program> ENDFILE_TOKEN

StartNode * ParserClass::Start()
{
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode * sn = new StartNode(pn);
    return sn;
}


ProgramNode * ParserClass::Program(){
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode * bn = Block();
    ProgramNode * pn = new ProgramNode(bn);
    return pn;
}
BlockNode * ParserClass::Block(){
    Match(LCURLY_TOKEN);
	
    StatementGroupNode * sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode * bn = new BlockNode(sgn,mSymbolTable);
    return bn;
}
StatementGroupNode * ParserClass::StatementGroup(){
    StatementGroupNode * sgn = new StatementGroupNode();
    StatementNode * st = NULL;
    do{
        st = Statement();
        if (st != NULL){
            sgn->AddStatement(st);

        }
    }while(st != NULL);
    return sgn;
}

StatementNode * ParserClass::Statement(){
    StatementNode * sn = NULL;
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    switch(tt){
        case(INT_TOKEN):
            sn = DeclarationStatement();
            break;
        case(IDENTIFIER_TOKEN):
            sn = AssignmentStatememt();
            break;
        case(COUT_TOKEN):
            sn = CoutStatement();
            break;
        case(LCURLY_TOKEN):
            sn = Block();
            break;
        case(IF_TOKEN):
            sn = IfStatement();
            break;
//        case(ELSE_TOKEN):
//            sn = ElseStatement();
//            break;
        case(WHILE_TOKEN):
            sn = WhileStatement();
            break;
    }
    return sn;
}

IfStatementNode *  ParserClass::IfStatement(){
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * en = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * sg1 = Statement();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    StatementNode * sg2;

    if (tt == ELSE_TOKEN){
        Match(ELSE_TOKEN);
        sg2 = Statement();
    }
    else{
        sg2 = NULL;

    }
    IfStatementNode * ifn = new IfStatementNode(en,sg1,sg2);
    return ifn;
}

IfStatementNode *  ParserClass::ElseStatement(){
    Match(ELSE_TOKEN);
    ExpressionNode * en = Expression();
    StatementNode * sg1 = Statement();
    StatementNode * sg2 = Statement();
    IfStatementNode * ifn = new IfStatementNode(en,sg1,sg2);
    return ifn;
}

WhileStatementNode * ParserClass::WhileStatement(){
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * en = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * sn = Statement();
    WhileStatementNode * wsn = new WhileStatementNode(en,sn);
    return wsn;
}

// <CoutStatement> → COUT INSERTION <Expression> SEMICOLON
CoutStatementNode * ParserClass::CoutStatement(){
	std::vector<ExpressionNode*> ven;
    Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	while (mScanner->PeekNextToken().GetTokenType() != SEMICOLON_TOKEN) {
		if (mScanner->PeekNextToken().GetTokenType() == ENDL_TOKEN) {
			Match(ENDL_TOKEN);
			ven.push_back(NULL);
			if (mScanner->PeekNextToken().GetTokenType() == SEMICOLON_TOKEN) {
				break;
			}
			else {
				Match(INSERTION_TOKEN);
			}
		}
		else{
			ExpressionNode * e = Expression();
			ven.push_back(e);
			if (mScanner->PeekNextToken().GetTokenType() == SEMICOLON_TOKEN) {
				break;
			}
			else {
				Match(INSERTION_TOKEN);
			}
		}
	}
    Match(SEMICOLON_TOKEN);
	CoutStatementNode * csn = new CoutStatementNode(ven);
    return csn;
}
// <AssignmentStatement> → <Identifier> ASSIGNMENT <Expression> SEMICOLON
AssignmentStatementNode * ParserClass::AssignmentStatememt(){
    IdentifierNode * i = Identifier();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == PLUSEQUAL_TOKEN){
        Match(PLUSEQUAL_TOKEN);
        ExpressionNode * en = Expression();
        Match(SEMICOLON_TOKEN);
        PlusEqualNode * pen = new PlusEqualNode(i,en);
        return pen;

    }

    else{
        Match(ASSIGNMENT_TOKEN);
        ExpressionNode * en = Expression();
        Match(SEMICOLON_TOKEN);
        AssignmentStatementNode * asn = new AssignmentStatementNode(i, en);
        return asn;
    }
}

// <DeclarationStatement> → INT <Identifier> SEMICOLON
DeclarationStatementNode * ParserClass::DeclarationStatement(){
    Match(INT_TOKEN);
    IdentifierNode * i = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode * dsn = new DeclarationStatementNode(i);
    return dsn;


}


// Verify that the next token in the input file is of the same type
// that the parser expects.
TokenClass ParserClass::Match(TokenType expectedType)
{
    TokenClass currentToken = mScanner->GetNextToken();
    if(currentToken.GetTokenType() != expectedType)
    {
        std::cerr << "Error in ParserClass::Match. " << std::endl;
        std::cerr << "Expected token type " <<
             TokenClass:: GetTokenTypeName(expectedType) <<
             ", but got type " << currentToken.GetTokenTypeName() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" << currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}

// <Expression> -> <Relational>


ExpressionNode * ParserClass::Expression(){
    return LogicalOr();
}

ExpressionNode * ParserClass::LogicalOr(){
    ExpressionNode * current = LogicalAnd();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == OR_TOKEN) {
            Match(tt);
            current = new OrNode(current, LogicalAnd());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::LogicalAnd(){
    ExpressionNode * current = Relational();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == AND_TOKEN) {
            Match(tt);
            current = new AndNode(current, Relational());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Relational()
{
    ExpressionNode * current = PlusMinus();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == LESS_TOKEN)
    {

        Match(tt);
        current = new LessNode(current,PlusMinus());
        return current;
    }
    else if(tt == LESSEQUAL_TOKEN)
    {
        Match(tt);
        current = new LessEqualNode(current, PlusMinus());
        return current;
    }
    else if(tt == GREATER_TOKEN)
    {
        Match(tt);
        current = new GreaterNode(current, PlusMinus());
        return current;
    }
    else if(tt == GREATEREQUAL_TOKEN)
    {
        Match(tt);
        current = new GreaterEqualNode(current, PlusMinus());
        return current;
    }
    else if(tt == EQUAL_TOKEN)
    {
        Match(tt);
        current = new EqualNode(current, PlusMinus());
        return current;
    }
    else if(tt == NOTEQUAL_TOKEN) {
        Match(tt);
        current = new NotEqualNode(current, PlusMinus());
        return current;
    }

    else
    {
        return current;
    }
}


// <PlusMinus> -> <TimesDivide> <PlusMinusTail>
// <PlusMinusTail> -> PLUS_TOKEN <TimesDivide> <PlusMinusTail>
// <PlusMinusTail> -> MINUS_TOKEN <TimesDivide> <PlusMinusTail>
// <PlusMinusTail> -> {empty}


ExpressionNode * ParserClass::PlusMinus() {
    ExpressionNode *current = TimesDivide();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == PLUS_TOKEN) {
            Match(tt);
            current = new PlusNode(current, TimesDivide());
//            return current;
        } else if (tt == MINUS_TOKEN) {
            Match(tt);
            current = new MinusNode(current, TimesDivide());
//            return current;
        }

        else {
            return current;
        }
    }
}

// <TimesDivide> -> <Factor> <TimesDivideTail>
// <TimesDivideTail> -> TIMES_TOKEN <Factor> <TimesDivideTail>
// <TimesDivideTail> -> DIVIDE_TOKEN <Factor> <TimesDivideTail>
// <TimesDivideTail> -> {empty}

ExpressionNode * ParserClass::TimesDivide(){
    ExpressionNode * current = Exponent();
    while(true)
    {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN)
        {
            Match(tt);
            current = new TimesNode(current, Exponent());
        }
        else if(tt == DIVIDE_TOKEN)
        {
            Match(tt);
            current = new DivideNode(current, Exponent());
        }
        else
        {
            return current;
        }
    }

}
// <Factor> → <Identifier>
// <Factor> → <Integer>
// <Factor> → LPAREN_TOKEN <Expression> RPAREN_TOKEN

ExpressionNode * ParserClass::Exponent() {
    ExpressionNode *current = Factor();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == EXPONENT_TOKEN){
            Match(tt);
            current = new ExponentNode(current, Factor());
            return current;
        }
        else{
            return current;
        }


    }
}

ExpressionNode * ParserClass::Factor(){
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == IDENTIFIER_TOKEN){
        return Identifier();
    }
    else if(tt == INTEGER_TOKEN){
        return Integer();
    }
    else if(tt == LPAREN_TOKEN){
        Match(tt);
        ExpressionNode * e = Expression();
        Match(RPAREN_TOKEN);
        return e;

    }
    else{
        MSG(tt)
        MSG("Factor had an error!")
    }
}

// <Identifier> → IDENTIFIER_TOKEN
// <Integer> → INTEGER_TOKEN

IdentifierNode * ParserClass::Identifier(){
    TokenClass tc = Match(IDENTIFIER_TOKEN);
    IdentifierNode * idn = new IdentifierNode(tc.GetLexeme(), mSymbolTable);
    return idn;
}
IntegerNode *  ParserClass::Integer(){
    TokenClass tc = Match(INTEGER_TOKEN);
    IntegerNode * in = new IntegerNode(atoi(tc.GetLexeme().c_str()));
    return in;
}
