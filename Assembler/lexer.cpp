#include <string>
#include <vector>

enum class TokenType {
    Mnemonic, Operand, Label, Directive, Separator, Comment, EndOfLine
};

struct Token {
    TokenType type;
    std::string text;
};

//pass by refrence with &
std::vector<Token> lex(const std::string& input) {
    std::vector<Token> tokens;
    //Some lodgic to get tokens
    return tokens;
}