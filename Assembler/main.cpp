#include "main.h"

int main()
{
    std::string inputFilePath = "babytest.txt";
    std::string outputFilePath = "MCode.txt";
    std::string code = readFileIntoString(inputFilePath); // Read the asymbly text file
    std::vector<Token> tokenizedAssembly;

    Lexer lexer(code);
    tokenizedAssembly = lexer.tokenize();              // turn the text file into a vector of tokens with TokenType and TokenText
    logLexerTokensToConsole(tokenizedAssembly, lexer); // Log to show the process of creating these Tokens.
    Parser parser(tokenizedAssembly);
    parser.parse();                                  // build the machine code
    std::cout << parser.GetBuiltMachineCodeString(); // log the machine code to the console directly
    std::string writerCode;
    std::string mCode = parser.GetBuiltMachineCodeString();
    writeFile(mCode, outputFilePath); // write to the  outputFilePath
    return 0;
}

// utility functions
std::string readFileIntoString(const std::string &path)
{
    std::ifstream fileStream(path);

    if (!fileStream)
    {
        std::cerr << "Unable to open file: " << path << std::endl;
        return "";
    }

    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    return stringStream.str();
}

// logging functions
void logLexerTokensToConsole(std::vector<Token> tokens, Lexer lexer)
{
    for (const auto &element : tokens)
    {
        std::cout << lexer.tokenTypeToString(element.type) << ": ";
        std::cout << element.text << " ";
    }
    std::cout << std::endl;
}