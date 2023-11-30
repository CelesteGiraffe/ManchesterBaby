#include "Parser.h"

#include <iostream>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

void Parser::parse()
{
    firstPass(tokens);

    currentTokenIndex = 0;
    while (!isAtEnd())
    {
        parseLine(); // here would be the second pass that would ahve the tokens full
    }
}

void Parser::advance()
{
    if (!isAtEnd())
        currentToken = tokens[currentTokenIndex++];
}

bool Parser::isAtEnd()
{
    return currentTokenIndex >= tokens.size();
}

void Parser::parseLine()
{
    advance();
    switch (currentToken.type)
    {
    case TokenType::Mnemonic:
        parseInstruction();
        break;
    case TokenType::Operand:
        parseOperand();
        break;
    case TokenType::Label:
        break;
    case TokenType::Directive:
        break;
    case TokenType::Separator:
        parseSeparator();
        break;
    case TokenType::Comment:
        parseComment();
        break;
    case TokenType::EndOfLine:
        break;
    default:
        std::cout << "Invalid Token Type" << std::endl;
        break;
    }
}

// parsing functions
void Parser::parseInstruction()
{
    Mnemonic mnemonic = stringToMnemonic(currentToken.text);
    if (mnemonic == Mnemonic::CPM || mnemonic == Mnemonic::STP)
    {
        std::string result = mnemonicHandler.parse(mnemonic);
        std::cout << "result of parsing: " << result << std::endl;
    }
    else if (mnemonic == Mnemonic::JMP)
    {
        if (isLabel(currentToken.text))
        {
            int address = resolveLabel(currentToken.text) + 2;
            std::string result = mnemonicHandler.parse(mnemonic, address); // remember that if there is a directive VAR then the label is a value and would need address + 2
            std::cout << "result of parsing JMP with label: " << result << std::endl;
        }
        else
        {
            int address = std::stoi(currentToken.text); // Convert the address to an integer directly, may be HEX and that does not work yet.
            std::string result = mnemonicHandler.parse(mnemonic, address);
            std::cout << "result of parsing JMP with address: " << result << std::endl;
        }
    }
}
void Parser::parseOperand()
{
    std::cout << "Operand: " << currentToken.text << std::endl;
}
void Parser::parseLabel()
{
    std::cout << "Label: " << currentToken.text << std::endl;
}
void Parser::parseDirective()
{
    std::cout << "Directive: " << currentToken.text << std::endl;
}
void Parser::parseSeparator()
{
    std::cout << "Separator: " << currentToken.text << std::endl;
}
void Parser::parseComment()
{
    std::cout << "Comment: " << currentToken.text << std::endl;
}

Mnemonic Parser::stringToMnemonic(const std::string &str)
{
    if (str == "JMP")
        return Mnemonic::JMP;
    if (str == "JRP")
        return Mnemonic::JRP;
    if (str == "LDN")
        return Mnemonic::LDN;
    if (str == "STO")
        return Mnemonic::STO;
    if (str == "SUB")
        return Mnemonic::SUB;
    if (str == "CPM")
        return Mnemonic::CPM;
    if (str == "STP")
        return Mnemonic::STP;
    else
        return Mnemonic::Unknown;
}

bool Parser::isLabel(const std::string &token)
{
    // Check if the first character is a letter
    if (!std::isalpha(token[0]))
        return false;

    // Check if the rest of the characters are alphanumeric or underscore
    return std::all_of(token.begin(), token.end(), [](char c)
                       { return std::isalnum(c) || c == '_'; });
}

int Parser::resolveLabel(const std::string &label)
{
    auto it = symbolTable.find(label);
    if (it != symbolTable.end())
        return it->second; // Return the address associated with the label
    else
        throw std::runtime_error("Label not found: " + label);
}

void Parser::firstPass(const std::vector<Token> &tokens)
{
    int currentAddress = 0;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        const Token &token = tokens[i];
        if (token.type == TokenType::Label)
        {
            symbolTable[token.text] = currentAddress;
        }
        currentAddress++;
    }
}