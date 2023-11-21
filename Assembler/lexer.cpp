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
    // Some lodgic to get tokens
    for (char ch : input)
    {
        if (ch == ' ' || ch == '\t')
        {
            if (!tokenText.empty())
            {
                tokens.push_back({currentType, tokenText});
                tokenText.clear();
            }
        }
        else if (ch == ';')
        {
            // After this is a comment
        }
        else if (ch == '\n')
        {
            // After this is End of line
        }
    }
    // Get's the last token if it was not an empty line
    if (!tokenText.empty())
    {
        tokens.push_back({currentType, tokenText});
    }
    return tokens;
}