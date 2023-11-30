#include "Parser.h"

#include <iostream>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

void Parser::parse()
{
    while (!isAtEnd())
    {
        parseLine();
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
        parseLabel();
        break;
    case TokenType::Directive:
        parseDirective();
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
        // call Mnemonic with the variable
    }
}
void Parser::parseOperand()
{
    // std::cout << "Operand: " << currentToken.text << std::endl;
}
void Parser::parseLabel()
{
    // std::cout << "Label: " << currentToken.text << std::endl;
}
void Parser::parseDirective()
{
    // std::cout << "Directive: " << currentToken.text << std::endl;
}
void Parser::parseSeparator()
{
    // std::cout << "Separator: " << currentToken.text << std::endl;
}
void Parser::parseComment()
{
    // std::cout << "Comment: " << currentToken.text << std::endl;
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