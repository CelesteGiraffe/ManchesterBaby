#pragma once

#include <vector>
#include <string>
#include "token.h"
#include "mnemonic.h"
#include "mnemonicHandler.h"

class MnemonicHandler;

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);
    void parse();

private:
    std::vector<Token> tokens;
    unsigned int currentTokenIndex = 0;
    Token currentToken;
    MnemonicHandler mnemonicHandler;

    void advance();
    bool isAtEnd();
    void parseLine();
    void parseInstruction();
    void parseOperand();
    void parseLabel();
    void parseDirective();
    void parseSeparator();
    void parseComment();

    // utility functions
    Mnemonic stringToMnemonic(const std::string &str);
};
