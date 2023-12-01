#include "lexer.h"
#include "parser.h"
#include "codeGen.h"
#include "writer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

// utililty functions
std::string readFileIntoString(const std::string &path);

// logging fuctions
void logLexerTokensToConsole(std::vector<Token> tokens, Lexer lexer);