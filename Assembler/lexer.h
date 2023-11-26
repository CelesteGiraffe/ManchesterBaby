#pragma once
#include <vector>
#include <string>

enum class TokenType
{
    Mnemonic,
    Operand,
    Label,
    Directive,
    Separator,
    Comment,
    EndOfLine
};

struct Token
{
    TokenType type;
    std::string text;
};

std::vector<Token> lex(const std::string &input);
std::string tokenTypeToString(TokenType type);