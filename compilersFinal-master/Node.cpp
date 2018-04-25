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

void StartNode::Code(InstructionsClass &code)
{
	mPN->Code(code);
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

void ProgramNode::Code(InstructionsClass &code) {
	mBN->Code(code);
}

ProgramNode::~ProgramNode()
{
    MSG("Delete ProgramNode");

    delete mBN;

}

BlockNode::BlockNode(StatementGroupNode *sgm, SymbolTableClass *st)
{
    MSG("make BlockNode");

    mSGN = sgm;
	mST = st;
}
void BlockNode::Interpret()
{
	mST->ScopeIn();
    mSGN->Interpret();
	mST->ScopeOut();

}

void BlockNode::Code(InstructionsClass &code) {
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

void StatementGroupNode::Code(InstructionsClass &code) {
	for (size_t i = 0; i < statements.size(); i++) {
		statements[i]->Code(code);
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

void IfStatementNode::Code(InstructionsClass &code)
{
	mEN->CodeEvaluate(code);
	unsigned char * memory1 = code.SkipIfZeroStack();
	mSN->Code(code);
	unsigned char * A1 = code.GetAddress();
	unsigned char * A2 = code.GetAddress();
	code.SetOffset(memory1, int(A2 - A1));

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

void WhileStatementNode::Code(InstructionsClass &code){
	unsigned char * memoryEvaluate = code.GetAddress();
	mEN->CodeEvaluate(code);
	unsigned char * memoryPointer = code.SkipIfZeroStack();
	unsigned char * A1 = code.GetAddress();
	mSN->Code(code);
	unsigned char * A2 = code.GetAddress();
	unsigned char * jump = code.Jump();
	code.SetOffset(jump, (int)(memoryEvaluate - A2));
	unsigned char * jumpMemory = code.GetAddress();
	code.SetOffset(memoryPointer, int(jumpMemory - A1));
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

void DeclarationStatementNode::Code(InstructionsClass &code)
{
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

void AssignmentStatementNode::Code(InstructionsClass &code) {
	mExpressionNode->CodeEvaluate(code);
	int Index = mIdentifierNode->GetIndex();
	code.PopAndStore(Index);
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

void PlusEqualNode::Code(InstructionsClass &code) {
	mIN->CodeEvaluate(code);
	mEN->CodeEvaluate(code);
	int index = mIN->GetIndex();
	code.PopPopAddPush();
	code.PopAndStore(index);
}


PlusEqualNode::~PlusEqualNode(){
    delete mIN;
    delete mEN;
}

CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode *> ven)
{	
    MSG("make CoutStatementNode");
    vEN = ven;
}

void CoutStatementNode::Interpret() {
	for (int i = 0; i < vEN.size(); i++) {
		if (vEN[i] == NULL) {
			std::cout << std::endl;
		}
		else {
			std::cout << vEN[i]->Evaluate();
		}
	}
}


void CoutStatementNode::Code(InstructionsClass &code) {
	for (int i = 0; i < vEN.size(); i++) {
		if (vEN[i] == NULL) {
			code.WriteEndl();
		}
		else {
			vEN[i]->CodeEvaluate(code);
			code.PopAndWrite();
		}
	}
}

CoutStatementNode::~CoutStatementNode()
{
    MSG("Delete CoutStatementNode");
	for (int i = 0; i < vEN.size(); i++) {
		delete vEN[i];
	}
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

void IntegerNode::CodeEvaluate(InstructionsClass &code)
{
    code.PushValue(mInt);
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

void IdentifierNode::CodeEvaluate(InstructionsClass &code)
{
	unsigned int p = mST->GetValue(mLabel);
	code.PushVariable(p);
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

void PlusNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopAddPush();
}

ExponentNode::ExponentNode(ExpressionNode *expressionOne, ExpressionNode *expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
    MSG("make PlusNode");
}

int ExponentNode::Evaluate()
{
    return int(pow(mEN1->Evaluate(), mEN2->Evaluate()));
}

void ExponentNode::CodeEvaluate(InstructionsClass &code)
{
	//not working code just passes the value
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopMulPush();
}

MinusNode::MinusNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int MinusNode::Evaluate()
{
    return mEN1->Evaluate() - mEN2->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int TimesNode::Evaluate()
{
    return mEN1->Evaluate() * mEN2->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int DivideNode::Evaluate()
{
    return mEN1->Evaluate() / mEN2->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopDivPush();
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

void LessNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int LessEqualNode::Evaluate()
{
    return mEN1->Evaluate() <= mEN2->Evaluate();
}

void LessEqualNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopLessEqualPush();
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

void GreaterNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int GreaterEqualNode::Evaluate()
{
    return mEN1->Evaluate() >= mEN2->Evaluate();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int EqualNode::Evaluate()
{
    return mEN1->Evaluate() == mEN2->Evaluate();
}

void EqualNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopEqualPush();
}


NotEqualNode::NotEqualNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}
int NotEqualNode::Evaluate()
{
    return mEN1->Evaluate() != mEN2->Evaluate();
}

void NotEqualNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopNotEqualPush();
}

OrNode::OrNode(ExpressionNode * expressionOne, ExpressionNode * expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}
int OrNode::Evaluate(){
    return mEN1->Evaluate() || mEN2->Evaluate();
}

void OrNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopOrPush();
}

AndNode::AndNode(ExpressionNode *expressionOne, ExpressionNode *expressionTwo) : BinaryOperatorNode(expressionOne, expressionTwo)
{
}

int AndNode::Evaluate() {
    return mEN1->Evaluate() && mEN2->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass &code)
{
	mEN1->CodeEvaluate(code);
	mEN2->CodeEvaluate(code);
	code.PopPopAndPush();
}

