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
    std::string GetBuiltMachineCodeString();

private:
    std::vector<Token> tokens;
    unsigned int currentTokenIndex = 0;
    Token currentToken;
    MnemonicHandler mnemonicHandler;
    std::map<std::string, int> symbolTable;

    std::string returnString;

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
    bool isLabel(const std::string &token);
    int resolveLabel(const std::string &label);

    void firstPass(const std::vector<Token> &tokens);
    void buildString(std::string str);
};
