#include "lexer.h"
#include "parser.h"
#include "codeGen.h"
#include "writer.h"

int main() {
    //get some text file to pass to the lexer
    std::vector<Token> tokenizedAssembly;
    tokenizedAssembly = lex("Source Code Here");
    //pass the tokenizedAssembly to the parcer
    parseTokens(tokenizedAssembly);
    //Then we take that List of instrctions that comes out of the parcer and pass it to gthe code gen to turn that into binary to be writen
    //std:string mCode = generateCode(ListOfInstructions)
    //then we take the file and print it using the writer.cpp function that will be included in the header "writer.h"
    //writeFile(mCode)
    return 0;
}