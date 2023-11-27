#pragma once

#include <vector>
#include <string>
#include "token.h"

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);
    void parse();

private:
    std::vector<Token> tokens;
    unsigned int currentTokenIndex = 0;
    Token currentToken;

    void advance();
    bool isAtEnd();
    void parseLine();
    void parseInstruction();
    void parseOperand();
    void parseLabel();
};
