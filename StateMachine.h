#pragma once


#include "Token.h"

enum MachineState {
    START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
    LCURLY_STATE,RCURLY_STATE,RPAREN_STATE, LPAREN_STATE, ASSIGNMENT_STATE, PLUS_STATE,
    SEMICOLON_STATE,ENDFILE_STATE, LESS_STATE,INSERTION_STATE,
    DIVIDE_STATE,TIMES_STATE, BLOCK1_STATE, BLOCK2_STATE,
    MINUS_STATE,EQUAL_STATE,GREATER_STATE, GREATEREQUAL_STATE,LESSEQUAL_STATE,NOTEQUAL_STATE,NOT_STATE,
    AND_STATE, OR_STATE,TEMP_STATE,PLUSEQUAL_STATE,EXPONENT_STATE,
    LAST_STATE
};

enum CharacterType {
    LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, BAD_CHAR,
    RCURLY_CHAR,LCURLY_CHAR,RPAREN_CHAR, LPAREN_CHAR, ASSIGNMENT_CHAR,UNDERSCORE_CHAR,
    SEMICOLON_CHAR, ENDFILE_CHAR, LESS_CHAR, INSERTION_CHAR,
    DIVIDE_CHAR, TIMES_CHAR, MINUS_CHAR,GREATER_CHAR,NOT_CHAR,AND_CHAR,OR_CHAR,
    LAST_CHAR
};

class StateMachineClass
{
public:
    StateMachineClass();
    MachineState UpdateState(char currentCharacter, TokenType &
    correspondingTokenType);


private:
    MachineState mCurrentState;

    // The matrix of legal moves:
    MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType mCorrespondingTokenTypes[LAST_STATE];
};
