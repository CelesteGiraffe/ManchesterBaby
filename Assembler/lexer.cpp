#include <string>
#include <vector>

enum class TokenType
{
    Mnemonic,
    Operand,
    Label,
    Directive,
    Separator,
    Comment,
    EndOfLine
};

struct Token
{
    TokenType type;
    std::string text;
};

// pass by refrence with &
std::vector<Token> lex(const std::string &input)
{
    std::vector<Token> tokens;
    std::string tokenText;
    // Set's the default type to mnemonic
    TokenType currentType = TokenType::Mnemonic;
    bool isLabelStart = true;

    for (char ch : input)
    {
        // Checks for if there is a Label which is preceded by the : only once.
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
                continue;
            }
        }
        // Checks for a tab or space to set the operands
        else if (ch == ' ' || ch == '\t')
        {
            if (!tokenText.empty())
            {
                tokens.push_back({currentType, tokenText});
                tokenText.clear();
            }
            currentType = TokenType::Operand;
        }
        // Ignores the characters after the ; to denote comments.
        else if (ch == ';')
        {
            if (!tokenText.empty())
            {
                tokens.push_back({currentType, tokenText});
                tokenText.clear();
            }
            currentType = TokenType::Comment;
        }
        // Set's the EndOfLine token type
        else if (ch == '\n')
        {
            isLabelStart = true;
            if (!tokenText.empty())
            {
                tokens.push_back({currentType, tokenText});
                tokenText.clear();
            }
            tokens.push_back({TokenType::EndOfLine, "\n"});
            currentType = TokenType::Mnemonic;
        }
        // Adds the token text after each type to determine what to do.
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