#include "StateMachine.h"

StateMachineClass::StateMachineClass()
        : mCurrentState(START_STATE)
{
    for(int i=0; i<LAST_STATE; i++)
    {
        for(int j=0; j<LAST_CHAR; j++)
        {
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }

    mLegalMoves[START_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR]= LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR]= RCURLY_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR]= RPAREN_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR]= LPAREN_STATE;
    mLegalMoves[START_STATE][ASSIGNMENT_CHAR]= ASSIGNMENT_STATE;
    mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;

    mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;

    mLegalMoves[START_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][UNDERSCORE_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][UNDERSCORE_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR]= PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;

    //&& and ||
    mLegalMoves[START_STATE][AND_CHAR] = TEMP_STATE;
    mLegalMoves[TEMP_STATE][AND_CHAR] = AND_STATE;
    mLegalMoves[START_STATE][OR_CHAR] = TEMP_STATE;
    mLegalMoves[TEMP_STATE][OR_CHAR] = OR_STATE;

    //+=,-=,*=,/=
    mLegalMoves[PLUS_STATE][ASSIGNMENT_CHAR] = PLUSEQUAL_STATE;

    // >=,<=,!=
    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR] = GREATEREQUAL_STATE;
    mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR] = LESSEQUAL_STATE;
    mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
    mLegalMoves[NOT_STATE][ASSIGNMENT_CHAR] = NOTEQUAL_STATE;

    mLegalMoves[START_STATE][SEMICOLON_CHAR]= SEMICOLON_STATE;
    mLegalMoves[START_STATE][ENDFILE_CHAR]= ENDFILE_STATE;
    mLegalMoves[START_STATE][LESS_CHAR]= LESS_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR]= INSERTION_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR]= START_STATE;
    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;

    mLegalMoves[START_STATE][DIVIDE_CHAR]= DIVIDE_STATE;
    mLegalMoves[DIVIDE_STATE][TIMES_CHAR]= BLOCK1_STATE;

    // BLOCK1_STATE self loop
    mLegalMoves[BLOCK1_STATE][DIGIT_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][LCURLY_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][RCURLY_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][RPAREN_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][LPAREN_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][ASSIGNMENT_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][UNDERSCORE_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][LETTER_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][PLUS_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][SEMICOLON_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][LESS_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][INSERTION_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][WHITESPACE_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK1_STATE][DIVIDE_CHAR]= BLOCK1_STATE;


    //BLOCK1_STATE transition to BLOCK2_STATE
    mLegalMoves[BLOCK1_STATE][TIMES_CHAR]= BLOCK2_STATE;

    //BLOCK2_STATE self loop
    mLegalMoves[BLOCK2_STATE][TIMES_CHAR]= BLOCK2_STATE;

    // BLOCK2_STATE transition to BLOCK1_STATE
    mLegalMoves[BLOCK2_STATE][DIGIT_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][LCURLY_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][RCURLY_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][RPAREN_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][LPAREN_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][ASSIGNMENT_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][UNDERSCORE_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][LETTER_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][PLUS_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][SEMICOLON_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][LESS_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][INSERTION_CHAR]= BLOCK1_STATE;
    mLegalMoves[BLOCK2_STATE][WHITESPACE_CHAR]= BLOCK1_STATE;


    mLegalMoves[BLOCK2_STATE][DIVIDE_CHAR]= START_STATE;

    mLegalMoves[BLOCK2_STATE][DIVIDE_CHAR]= START_STATE;



    for(int i=0; i<LAST_STATE; i++)
    {
        mCorrespondingTokenTypes[i]=BAD_TOKEN;
    }
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
    mCorrespondingTokenTypes[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;
    mCorrespondingTokenTypes[EXPONENT_STATE] = EXPONENT_TOKEN;


}

MachineState StateMachineClass::UpdateState(char currentCharacter,
                                            TokenType & correspondingTokenType)
{
    // convert the input character into an input character type
    CharacterType charType = BAD_CHAR;

    if(isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    if(isalpha(currentCharacter))
        charType = LETTER_CHAR;
    if(isspace(currentCharacter))
        charType = WHITESPACE_CHAR;
    if(currentCharacter=='+')
        charType = PLUS_CHAR;
    if(currentCharacter =='-')
        charType = MINUS_CHAR;
    if(currentCharacter=='}')
        charType = RCURLY_CHAR;
    if(currentCharacter=='{')
        charType = LCURLY_CHAR;
    if(currentCharacter==')')
        charType = RPAREN_CHAR;
    if(currentCharacter=='(')
        charType = LPAREN_CHAR;
    if(currentCharacter=='=')
        charType = ASSIGNMENT_CHAR;
    if(currentCharacter==';')
        charType = SEMICOLON_CHAR;
    if(currentCharacter=='<')
        charType = LESS_CHAR;
    if(currentCharacter=='/')
        charType = DIVIDE_CHAR;
    if(currentCharacter=='*')
        charType = TIMES_CHAR;
    if(currentCharacter=='>')
        charType = GREATER_CHAR;
    if(currentCharacter=='!')
        charType = NOT_CHAR;
    if(currentCharacter == '&')
        charType = AND_CHAR;
    if(currentCharacter == '|')
        charType = OR_CHAR;
    if(currentCharacter==EOF)
        charType = ENDFILE_CHAR;


    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][charType];
    return mCurrentState;

}
