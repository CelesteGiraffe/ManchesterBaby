#include "lexer.h"
#include "parser.h"
#include "codeGen.h"
#include "writer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

// function decliration
std::string readFileIntoString(const std::string &path);

int main()
{
    std::string filePath = "babytest.txt";
    std::string code = readFileIntoString(filePath);
    // get some text file to pass to the lexer
    std::vector<Token> tokenizedAssembly;
    tokenizedAssembly = lex(code);
    for (const auto &element : tokenizedAssembly)
    {
        std::cout << element.text << " ";
    }
    std::cout << std::endl;
    // pass the tokenizedAssembly to the parcer
    parseTokens(tokenizedAssembly);
    // Then we take that List of instrctions that comes out of the parcer and pass it to gthe code gen to turn that into binary to be writen
    // std:string mCode = generateCode(ListOfInstructions)
    // then we take the file and print it using the writer.cpp function that will be included in the header "writer.h"
    // writeFile(mCode)
    return 0;
}

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