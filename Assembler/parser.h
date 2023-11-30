#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <map>
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
    std::map<std::string, int> symbolTable;

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
    Mnemonic Parser::stringToMnemonic(const std::string &str);
    bool Parser::isLabel(const std::string &token);
    int Parser::resolveLabel(const std::string &label);

    void Parser::firstPass(const std::vector<Token> &tokens);
};
