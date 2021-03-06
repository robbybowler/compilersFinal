#pragma once

#include <vector>
#include <string>
#include "Symbol.h"


class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class IdentifierNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;


class Node
{
public:
    virtual ~Node();
    virtual void Interpret() = 0;

};

class StartNode : public Node
{
public:
    StartNode(ProgramNode *pn);	//mPn = pn
    virtual void Interpret();
    virtual ~StartNode();
private:
    ProgramNode * mPN;
};

class ProgramNode : public Node
{
public:
    ProgramNode(BlockNode *bn);
    virtual void Interpret();
    virtual ~ProgramNode();
private:
    BlockNode * mBN;
};

class StatementNode : public Node
{
public:
    StatementNode();
private:
};

class ElseStatementNode : public StatementNode
{
public:
    ElseStatementNode(ExpressionNode * en, StatementNode * sn);
    virtual void Interpret();
    virtual ~ElseStatementNode();

private:
    ExpressionNode * mEN;
    StatementNode * mSN;
};

class IfStatementNode : public StatementNode
{
public:
    IfStatementNode(ExpressionNode * en, StatementNode * sn,StatementNode * sn2);
    IfStatementNode(ExpressionNode * en, StatementNode * sg);
    virtual void Interpret();
    virtual ~IfStatementNode();

private:
    ExpressionNode * mEN;
    StatementNode * mSN;
    StatementNode * mSN2;

};

class WhileStatementNode : public StatementNode
{
public:
    WhileStatementNode(ExpressionNode * en, StatementNode * sn);
    virtual void Interpret();
    virtual ~WhileStatementNode();

private:
    ExpressionNode * mEN;
    StatementNode * mSN;
};

class  BlockNode : public StatementNode
{
public:
    BlockNode(StatementGroupNode *sgm);
    virtual void Interpret();
    virtual ~BlockNode();
private:
    StatementGroupNode * mSGN;
};

class StatementGroupNode : public Node
{
public:
    void AddStatement(StatementNode * sn);
    virtual void Interpret();
    virtual ~StatementGroupNode();
private:
    std::vector<StatementNode *> statements;
};


class DeclarationStatementNode : public StatementNode
{
public:
    DeclarationStatementNode(IdentifierNode *in);
    virtual void Interpret();
    virtual ~DeclarationStatementNode();
private:
    IdentifierNode * mIN;
};

class AssignmentStatementNode : public StatementNode
{
public:
    AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    virtual void Interpret();
    virtual ~AssignmentStatementNode();
private:
    IdentifierNode * mIdentifierNode;
    ExpressionNode * mExpressionNode;
};

class PlusEqualNode : public AssignmentStatementNode
{
public:
    PlusEqualNode(IdentifierNode *in, ExpressionNode *en);
    virtual void Interpret();
    virtual ~PlusEqualNode();

private:
    IdentifierNode * mIN;
    ExpressionNode * mEN;
};

class CoutStatementNode : public StatementNode
{
public:
    CoutStatementNode(ExpressionNode *en);
    virtual void Interpret();
    ~CoutStatementNode();
private:
    ExpressionNode * mEN;
};

class ExpressionNode
{
public:
    virtual int Evaluate() = 0;
    virtual ~ExpressionNode();
};

class IntegerNode : public ExpressionNode
{
public:
    IntegerNode(int value);
    int Evaluate();
private:
    int mInt;
};

class IdentifierNode : public ExpressionNode
{
public:
    IdentifierNode(std::string label, SymbolTableClass *ST);
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();
private:
    std::string mLabel;
    SymbolTableClass *mST;
};

class BinaryOperatorNode : public ExpressionNode
{
public:
    BinaryOperatorNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual ~BinaryOperatorNode();
protected:
    ExpressionNode *mEN1;
    ExpressionNode *mEN2;
};

class PlusNode : public BinaryOperatorNode
{
public:
    PlusNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};

class ExponentNode : public BinaryOperatorNode
{
public:
    ExponentNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();

};

class MinusNode : public BinaryOperatorNode
{
public:
    MinusNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};

class TimesNode : public BinaryOperatorNode
{
public:
    TimesNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class DivideNode : public BinaryOperatorNode
{
public:
    DivideNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class LessNode : public BinaryOperatorNode
{
public:
    LessNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class LessEqualNode : public BinaryOperatorNode
{
public:
    LessEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class GreaterNode : public BinaryOperatorNode
{
public:
    GreaterNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class GreaterEqualNode : public BinaryOperatorNode
{
public:
    GreaterEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class EqualNode : public BinaryOperatorNode
{
public:
    EqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};
class NotEqualNode : public BinaryOperatorNode
{
public:
    NotEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};

class OrNode : public  BinaryOperatorNode
{
public:
    OrNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};

class AndNode : public BinaryOperatorNode
{
public:
    AndNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo);
    virtual int Evaluate();
};

