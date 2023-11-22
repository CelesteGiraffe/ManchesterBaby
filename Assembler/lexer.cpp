#include <string>
#include <vector>

enum class TokenType
{
    Mnemonic,  // Instruction example MOV
    Operand,   // Things passed to a Mnemonic
    Label,     // Marks positions in the code
    Directive, // Controls how the assimbly processes data (might not be needed for the project)
    Separator, // Separates operands
    Comment,   // After a ; it's a comment that dinotes what's being done in the code
    EndOfLine  // Executes a single command with a carrage return.
};

struct Token
{
    TokenType type;
    std::string text;
};

// pass by refrence with &
std::vector<Token> lex(const std::string &input)
{
    // Example Command: START:    LDN NUM01   ; Copy variable to accumulator (negated)

    std::vector<Token> tokens;
    std::string tokenText;
    // Set's the default type to mnemonic
    TokenType currentType = TokenType::Mnemonic;
    bool isLabelStart = true;

    for (char ch : input)
    {
        if (handleLabel(ch, tokenText, tokens, isLabelStart) ||
            handleSeparator(ch, tokenText, tokens, currentType) ||
            handleSpaceOrTab(ch, tokenText, tokens, currentType, isLabelStart) ||
            handleComment(ch, tokenText, tokens, currentType) ||
            handleNewLine(ch, tokenText, tokens, currentType, isLabelStart))
        {
            continue; // Skip the rest of the loop if any condition was handled
        }
        else
        {
            tokenText += ch;
        }
    }
    // Get's the last token if it was not an empty line
    if (!tokenText.empty())
    {
        tokens.push_back({currentType, tokenText});
    }
    return tokens;
}

bool handleLabel(char ch, std::string &tokenText, std::vector<Token> &tokens, bool &isLabelStart)
{
    if (isLabelStart && ch != ' ' && ch != '\t')
    {
        if (ch == ':')
        {
            if (!tokenText.empty())
            {
                tokens.push_back({TokenType::Label, tokenText});
                tokenText.clear();
            }
            isLabelStart = false;
            return true; // Label was handled
        }
    }
    return false; // No label to handle
}

bool handleSeparator(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType)
{
    if (ch == ',')
    {
        if (!tokenText.empty())
        {
            tokens.push_back({currentType, tokenText});
            tokenText.clear();
        }
        tokens.push_back({TokenType::Separator, ","});
        currentType = TokenType::Operand;
        return true;
    }
    return false;
}

bool handleSpaceOrTab(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool isLabelStart)
{
    if (ch == ' ' || ch == '\t')
    {
        // Ignore spaces or tabs at the start of a line
        if (isLabelStart && tokenText.empty())
        {
            return false;
        }

        if (!tokenText.empty())
        {
            tokens.push_back({currentType, tokenText});
            tokenText.clear();
        }
        // Set to Operand only if it's not the start of a line
        if (!isLabelStart)
        {
            currentType = TokenType::Operand;
        }
        return true;
    }
    return false;
}

bool handleComment(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType)
{
    if (ch == ';')
    {
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

bool handleNewLine(char ch, std::string &tokenText, std::vector<Token> &tokens, TokenType &currentType, bool &isLabelStart)
{
    if (ch == '\n')
    {
        isLabelStart = true;
        if (!tokenText.empty())
        {
            tokens.push_back({currentType, tokenText});
            tokenText.clear();
        }
        tokens.push_back({TokenType::EndOfLine, "\n"});
        currentType = TokenType::Mnemonic;
        return true;
    }
    return false;
}