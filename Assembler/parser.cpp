#include <vector>
#include <string>
#include "lexer.h"
#include <iostream>

// fuction declerations
void checkMnemonicsType(std::string &mnemonic);
void processLine(const std::string &mnemonic, const std::string &operand,
                 const std::string &label, const std::string &directive,
                 const std::string &separator, const std::string &comment);

void parseTokens(const std::vector<Token> &tokens)
{
    std::string mnemonic, operand, label, directive, separator, comment;

    for (const auto &token : tokens)
    {
        switch (token.type)
        {
        case TokenType::Mnemonic:
            mnemonic = token.text;
            // checkMnemonicsType(mnemonic);
            break;
        case TokenType::Operand:
            operand = token.text;
            break;
        case TokenType::Label:
            label = token.text;
            break;
        case TokenType::Directive:
            directive = token.text;
            break;
        case TokenType::Separator:
            separator = token.text;
            break;
        case TokenType::Comment:
            comment = token.text;
            break;
        case TokenType::EndOfLine:
            // Perform operations with collected data here
            processLine(mnemonic, operand, label, directive, separator, comment);

            // Reset variables for the next line
            mnemonic = operand = label = directive = separator = comment = "";
            break;
        }
    }

    if (!mnemonic.empty() || !operand.empty() || !label.empty() ||
        !directive.empty() || !separator.empty() || !comment.empty())
    {
        processLine(mnemonic, operand, label, directive, separator, comment);
    }
}

void processLine(const std::string &mnemonic, const std::string &operand,
                 const std::string &label, const std::string &directive,
                 const std::string &separator, const std::string &comment)
{
}

void checkMnemonicsType(std::string &mnemonic)
{
    // List of valid mnemonics for the Manchester Baby
    const std::string validMnemonics[] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP"};

    // Check if the mnemonic is in the list of valid mnemonics
    bool isValid = false;
    for (const auto &validMnemonic : validMnemonics)
    {
        if (mnemonic == validMnemonic)
        {
            isValid = true;
            break;
        }
    }

    // Handle the case where the mnemonic is not valid
    if (!isValid)
    {
        std::cerr << "Invalid mnemonic: " << mnemonic << std::endl;
    }
}
