#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "token.h"

class Lexer
{
public:
    std::string input;
    explicit Lexer(const std::string &input);
    std::vector<Token> tokenize();
    // Utility functions
    std::string tokenTypeToString(TokenType type);

private:
    std::vector<Token> tokens;
    std::string tokenText;
    TokenType currentType = TokenType::Unknown;
    bool isLabelStart = true;
    bool isAfterCommandWord = false;
    bool inComment = false;

    // Token handlers
    bool handleLabel(char ch, std::string &tokenText, std::vector<Token> &tokens, bool &isLabelStart, TokenType &currentType);
    bool handleSeparator(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment);
    bool handleSpaceOrTab(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool isLabelStart, bool &inComment);
    bool handleComment(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment);
    bool handleNewLine(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &isLabelStart, bool &inComment);
    TokenType determineTokenType(const std::string &tokenText, bool isLabelStart, bool &isAfterCommandWord);
};