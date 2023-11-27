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
    case TokenType::Label:
        parseLabel();
        break;
    case TokenType::EndOfLine:
        advance();
        break;
    default:
        std::cout << "Invalid Token Type" << std::endl;
        break;
    }
}

void Parser::parseInstruction()
{
    std::cout << "Instruction: " << currentToken.text << std::endl;
    advance();
    parseOperand();
}

void Parser::parseOperand()
{
    if (currentToken.type == TokenType::Operand)
    {
        std::cout << "Operand: " << currentToken.text << std::endl;
        advance();
    }
}

void Parser::parseLabel()
{
    std::cout << "Label: " << currentToken.text << std::endl;
    advance();
}
