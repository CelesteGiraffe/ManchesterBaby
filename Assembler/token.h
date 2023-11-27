#pragma once
#include <string>
enum class TokenType
{
    Mnemonic,  // Instruction example MOV
    Operand,   // Things passed to a Mnemonic
    Label,     // Marks positions in the code
    Directive, // Controls how the assimbly processes data (might not be needed for the project)
    Separator, // Separates operands
    Comment,   // After a ; it's a comment that dinotes what's being done in the code
    EndOfLine, // Executes a single command with a carrage return.
    Unknown
};

struct Token
{
    TokenType type;
    std::string text;
};