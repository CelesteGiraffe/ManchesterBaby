#include "lexer.h"

Lexer::Lexer(const std::string &input) : input(input) {}

std::vector<Token> Lexer::tokenize()
{
    for (char ch : input)
    {
        if (handleLabel(ch, tokenText, tokens, isLabelStart, currentType) ||
            handleSeparator(ch, tokenText, tokens, currentType, inComment) ||
            handleSpaceOrTab(ch, tokenText, tokens, currentType, isLabelStart, inComment) ||
            handleComment(ch, tokenText, tokens, currentType, inComment) ||
            handleNewLine(ch, tokenText, tokens, currentType, isLabelStart, inComment))
        {
            continue;
        }
        else
        {
            tokenText += ch;
            if (currentType == TokenType::Unknown)
            {
                currentType = determineTokenType(tokenText, isLabelStart, isAfterCommandWord);
            }
        }
    }

    if (!tokenText.empty())
    {
        tokens.push_back({currentType, tokenText});
    }
    return tokens;
}

// token handlers
bool handleLabel(char ch, std::string &tokenText, std::vector<Token> &tokens, bool &isLabelStart, TokenType &currentType)
{
    if (isLabelStart && ch != ' ' && ch != '\t')
    {
        if (ch == ':')
        {
            if (!tokenText.empty())
            {
                tokens.push_back({TokenType::Label, tokenText});
                tokenText.clear();
                currentType = TokenType::Unknown;
            }
            isLabelStart = false;
            return true;
        }
    }
    return false;
}
bool handleSeparator(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment)
{
    if (ch == ',' && !inComment)
    {
        if (!tokenText.empty())
        {
            tokens.push_back({currentType, tokenText});
            tokenText.clear();
        }
        tokens.push_back({TokenType::Separator, ","});
        currentType = TokenType::Unknown;
        return true;
    }
    return false;
}
bool handleSpaceOrTab(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool isLabelStart, bool &inComment)
{
    if (ch == ' ' || ch == '\t')
    {
        if (!inComment)
        {
            if (!tokenText.empty())
            {
                tokens.push_back({currentType, tokenText});
                tokenText.clear();
                currentType = TokenType::Unknown;
            }
        }
        else
        {
            // Add spaces/tabs to the comment token
            tokenText += ch;
        }
        return true; // Handle the space or tab
    }
    return false; // Not a space or tab
}
bool handleComment(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment)
{
    if (ch == ';')
    {
        inComment = true;
        if (!tokenText.empty())
        {
            tokens.push_back({currentType, tokenText});
            tokenText.clear();
        }
        currentType = TokenType::Comment;
        return true;
    }
    return false;
}
bool handleNewLine(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &isLabelStart, bool &inComment)
{
    if (ch == '\n')
    {
        if (inComment)
        {
            // Add the comment token to the list
            tokens.push_back({TokenType::Comment, tokenText});
            tokenText.clear();
        }
        isLabelStart = true;
        inComment = false;
        tokens.push_back({TokenType::EndOfLine, "\n"});
        currentType = TokenType::Unknown;
        return true;
    }
    return false;
}
TokenType determineTokenType(const std::string &tokenText, bool isLabelStart, bool &isAfterCommandWord)
{
    if (tokenText.empty())
        return TokenType::Unknown;

    // Check for comments
    if (tokenText[0] == ';')
        return TokenType::Comment;

    // Check for labels
    if (isLabelStart && tokenText.back() == ':')
        return TokenType::Label;

    // Check for number tokens, assuming they are always operands
    if (std::all_of(tokenText.begin(), tokenText.end(), ::isdigit))
        return TokenType::Operand;

    // Any token immediately after a command word is an operand
    if (isAfterCommandWord)
    {
        isAfterCommandWord = false; // Reset the flag
        return TokenType::Operand;
    }

    // Check for mnemonics and directives
    if (tokenText.length() == 3)
    {
        for (const auto &mnemonic : mnemonics)
        {
            if (tokenText == mnemonic)
            {
                isAfterCommandWord = true;
                return TokenType::Mnemonic;
            }
        }

        for (const auto &directive : directives)
        {
            if (tokenText == directive)
            {
                isAfterCommandWord = true;
                return TokenType::Directive;
            }
        }
    }

    // Fallback case for unknown token types
    return TokenType::Unknown;
}

// utility functions
std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::Mnemonic:
        return "Mnemonic";
    case TokenType::Operand:
        return "Operand";
    case TokenType::Label:
        return "Label";
    case TokenType::Directive:
        return "Directive";
    case TokenType::Separator:
        return "Separator";
    case TokenType::Comment:
        return "Comment";
    case TokenType::EndOfLine:
        return "EndOfLine";
    default:
        return "Unknown";
    }
}