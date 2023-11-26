#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum class TokenType
{
    Mnemonic,  // Instruction example MOV
    Operand,   // Things passed to a Mnemonic
    Label,     // Marks positions in the code
    Directive, // Controls how the assimbly processes data (might not be needed for the project)
    Separator, // Separates operands
    Comment,   // After a ; it's a comment that dinotes what's being done in the code
    EndOfLine, // Executes a single command with a carrage return.
    Unknown
};

struct Token
{
    TokenType type;
    std::string text;
};

std::vector<std::string> mnemonics = {"JMP", "JRP", "LDN", "STO", "SUB", "CPM", "STP"};
std::vector<std::string> directives = {"VAR"};

// function declirations
bool handleLabel(char ch, std::string &tokenText, std::vector<Token> &tokens, bool &isLabelStart, TokenType &currentType);
bool handleSeparator(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment);
bool handleSpaceOrTab(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool isLabelStart, bool &inComment);
bool handleComment(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &inComment);
bool handleNewLine(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &isLabelStart, bool &inComment);
TokenType determineTokenType(const std::string &tokenText, bool isLabelStart);

std::vector<Token> lex(const std::string &input)
{
    std::vector<Token> tokens;
    std::string tokenText;
    TokenType currentType = TokenType::Unknown;
    bool isLabelStart = true;
    bool inComment = false;

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
                currentType = determineTokenType(tokenText, isLabelStart);
            }
        }
    }

    if (!tokenText.empty())
    {
        tokens.push_back({currentType, tokenText});
    }
    return tokens;
}
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
TokenType determineTokenType(const std::string &tokenText, bool isLabelStart)
{
    if (tokenText.empty())
        return TokenType::Unknown;

    if (tokenText[0] == ';')
        return TokenType::Comment;

    if (isLabelStart && tokenText.back() == ':')
        return TokenType::Label;

    if (tokenText.length() == 3)
    {
        for (const auto &mnemonic : mnemonics)
        {
            if (tokenText == mnemonic)
                return TokenType::Mnemonic;
        }

        for (const auto &directive : directives)
        {
            if (tokenText == directive)
                return TokenType::Directive;
        }
    }

    if (std::all_of(tokenText.begin(), tokenText.end(), ::isdigit))
        return TokenType::Operand; // Assuming all numbers are operands here

    // if(tokenText.lenght() <= 3) need to see if it's a variable and that normaly would be done if it has a space after once that was none of the other.
    return TokenType::Unknown; // Default to unkown
}
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