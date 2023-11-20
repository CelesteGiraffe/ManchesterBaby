#include <string>

enum class TokenType {
    Mnemonic, Operand, Label, Directive, Separator, Comment, EndOfLine
};

struct Token {
    TokenType type;
    std::string text;
};