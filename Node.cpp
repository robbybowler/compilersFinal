#include "Node.h"
#include "Debug.h"
#include <math.h>

using namespace std;

Node::~Node() {
}

StartNode::StartNode(ProgramNode *pn)
{
    MSG("make StartNode");

    mPN = pn;
}

void StartNode::Interpret()
{
    mPN->Interpret();
}


StartNode::~StartNode()
{
    MSG("Delete StartNode");

    delete mPN;
}

ProgramNode::ProgramNode(BlockNode *bn)
{
    MSG("make ProgramNode");

    mBN = bn;
}

void ProgramNode::Interpret()
{
    mBN->Interpret();
}


ProgramNode::~ProgramNode()
{
    MSG("Delete ProgramNode");

    delete mBN;

}

BlockNode::BlockNode(StatementGroupNode *sgm)
{
    MSG("make BlockNode");

    mSGN = sgm;
}
void BlockNode::Interpret()
{
    mSGN->Interpret();
}

BlockNode::~BlockNode()
{
    MSG("Delete BlockNode");

    delete mSGN;
}

void StatementGroupNode::Interpret(){
    for(size_t i = 0; i < statements.size();i++){
        statements[i]->Interpret();
    }
}

void StatementGroupNode::AddStatement(StatementNode * sn)
{
    statements.push_back(sn);
}

StatementGroupNode::~StatementGroupNode()
{
    MSG("Delete StatementGroupNode");

    for (int i = 0; i < statements.size(); i++)
    {
        delete statements[i];
    }
}

StatementNode::StatementNode()
{
    MSG("make StatementNode");

}
ElseStatementNode::ElseStatementNode(ExpressionNode * en, StatementNode * sg)
{
    MSG("make IfStatementNode")
    mSN = sg;
    mEN = en;

}

void ElseStatementNode::Interpret() {
    mSN->Interpret();

}

ElseStatementNode::~ElseStatementNode(){
    MSG("Delete IfStatementNode")
    delete mEN;
    delete mSN;
}

IfStatementNode::IfStatementNode(ExpressionNode * en, StatementNode * sg)
{
    MSG("make IfStatementNode")
    mSN = sg;
    mSN2 = NULL;
    mEN = en;

}

IfStatementNode::IfStatementNode(ExpressionNode * en, StatementNode * sg,StatementNode * sg2)
{
    MSG("make IfStatementNode")
    mSN = sg;
    mSN2 = sg2;
    mEN = en;

}

void IfStatementNode::Interpret() {
    if(mEN->Evaluate() != 0){
        mSN->Interpret();
    }else if(mSN2 != NULL){
        mSN2->Interpret();
    }
}

IfStatementNode::~IfStatementNode(){
    MSG("Delete IfStatementNode")
    delete mEN;
    delete mSN;
    delete mSN2;

}

WhileStatementNode::WhileStatementNode(ExpressionNode *en, StatementNode *sn){
    MSG("Make WhileStatementNode")
    mSN = sn;
    mEN = en;
}

void WhileStatementNode::Interpret() {
    while(mEN->Evaluate()){
        mSN->Interpret();
    }
}

WhileStatementNode::~WhileStatementNode(){
    MSG("Delete WhileStatement")

    delete mEN;
    delete mSN;
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *in)
{
    MSG("make DeclarationStatementNode");
    mIN = in;
}

void DeclarationStatementNode::Interpret() {
    mIN->DeclareVariable();
}

DeclarationStatementNode::~DeclarationStatementNode()
{
    MSG("Delete DeclarationStatementNode");
    delete mIN;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en)
{
    MSG("make AssignmentStatementNode");

    mIdentifierNode = in;
    mExpressionNode = en;
}
void AssignmentStatementNode::Interpret() {
    mIdentifierNode->SetValue(mExpressionNode->Evaluate());
}

AssignmentStatementNode::~AssignmentStatementNode()
{
    MSG("Delete AssignmentStatementNode");

    delete mIdentifierNode;
    delete mExpressionNode;
}

PlusEqualNode::PlusEqualNode(IdentifierNode *in, ExpressionNode *en) : AssignmentStatementNode(in, en)
{
    mIN = in;
    mEN = en;
}

void PlusEqualNode::Interpret(){
    mIN->SetValue(mIN->Evaluate() + mEN->Evaluate());
}

PlusEqualNode::~PlusEqualNode(){
    delete mIN;
    delete mEN;
}

CoutStatementNode::CoutStatementNode(ExpressionNode *en)
{
    MSG("make CoutStatementNode");
    mEN = en;
}
void CoutStatementNode::Interpret() {
    std::cout << mEN->Evaluate() << std::endl;
}

CoutStatementNode::~CoutStatementNode()
{
    MSG("Delete CoutStatementNode");
    delete mEN;
}

ExpressionNode::~ExpressionNode()
{
    MSG("Delete ExpressionNode");
}

IntegerNode::IntegerNode(int value)
{
    MSG("make IntegerNode");

    mInt = value;
}

int IntegerNode::Evaluate()
{
    return mInt;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass *ST)
{
    MSG("make IdentifierNode");

    mLabel = label;
    mST = ST;
}

void IdentifierNode::DeclareVariable()
{
    mST->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v)
{
    mST->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex()
{
    return mST->GetIndex(mLabel);
}

int IdentifierNode::Evaluate()
{
    return mST->GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo)
{
    MSG("make BinaryOperatorNode");

    mEN1 = expressionOne;
    mEN2 = expressionTwo;
}

BinaryOperatorNode::~BinaryOperatorNode()
{
    MSG("Delete BinaryOperatorNode");


    delete mEN1;
    delete mEN2;
}

PlusNode::PlusNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
    MSG("make PlusNode");

}

int PlusNode::Evaluate()
{
    return mEN1->Evaluate() + mEN2->Evaluate();
}

ExponentNode::ExponentNode(ExpressionNode *expressionOne, ExpressionNode *expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
    MSG("make PlusNode");
}

int ExponentNode::Evaluate()
{
    return int(pow(mEN1->Evaluate(), mEN2->Evaluate()));
}

MinusNode::MinusNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int MinusNode::Evaluate()
{
    return mEN1->Evaluate() - mEN2->Evaluate();
}

TimesNode::TimesNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int TimesNode::Evaluate()
{
    return mEN1->Evaluate() * mEN2->Evaluate();
}

DivideNode::DivideNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int DivideNode::Evaluate()
{
    return mEN1->Evaluate() / mEN2->Evaluate();
}

LessNode::LessNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int LessNode::Evaluate() {
    if (mEN1->Evaluate() < mEN2->Evaluate()) {
        return 1;
    } else {
        return 0;
    }
}

LessEqualNode::LessEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int LessEqualNode::Evaluate()
{
    return mEN1->Evaluate() <= mEN2->Evaluate();
}

GreaterNode::GreaterNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int GreaterNode::Evaluate()
{
    if(mEN1->Evaluate() > mEN2->Evaluate()){
        return 1;
    }
    else{
        return 0;
    }
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int GreaterEqualNode::Evaluate()
{
    return mEN1->Evaluate() >= mEN2->Evaluate();
}

EqualNode::EqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int EqualNode::Evaluate()
{
    return mEN1->Evaluate() == mEN2->Evaluate();
}

NotEqualNode::NotEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}
int NotEqualNode::Evaluate()
{
    return mEN1->Evaluate() != mEN2->Evaluate();
}

OrNode::OrNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}
int OrNode::Evaluate(){
    return mEN1->Evaluate() || mEN2->Evaluate();
}

AndNode::AndNode(ExpressionNode *expressionOne, ExpressionNode *expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int AndNode::Evaluate() {
    return mEN1->Evaluate() && mEN2->Evaluate();
}


