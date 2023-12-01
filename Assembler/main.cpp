#include "main.h"
#include "writer.h"

int main()
{
    std::string filePath = "babytest.txt";
    std::string code = readFileIntoString(filePath);
    std::vector<Token> tokenizedAssembly;

    Lexer lexer(code);
    tokenizedAssembly = lexer.tokenize();

    // logLexerTokensToConsole(tokenizedAssembly, lexer); // Used for testing and understanding of code.

    Parser parser(tokenizedAssembly);
    parser.parse();
    std::cout << parser.GetBuiltMachineCodeString();
    std::string writerCode;
    // Then we take that List of instrctions that comes out of the parcer and pass it to gthe code gen to turn that into binary to be writen
    std::string mCode = parser.GetBuiltMachineCodeString();
    // then we take the file and print it using the writer.cpp function that will be included in the header "writer.h"
    writeFile(mCode);
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