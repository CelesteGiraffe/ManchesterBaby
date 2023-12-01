#include "writer.h"

void writeFile(std::string code)
{
    std::string output = parseCodeString(code);
    std::ofstream file("MCode.txt");
    if (file.is_open())
    {
        file << output;

        file.close();
    }
    else
    {
        // Handle the error if the file couldn't be opened
        std::cerr << "Unable to open file";
    }
}
std::string parseCodeString(std::string input)
{
    int lineLength = 32;
    for (size_t i = lineLength; i < input.length(); i += lineLength + 1)
    { // +1 to account for the newline character itself
        input.insert(i, "\n");
    }
    return input;
}