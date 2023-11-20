#include <iostream>
#include <array>
#include <fstream>

using namespace std;

void fetch(int ci, ifstream store);

std::array<int,2> decode(string instruction);

void execute(int accumulator, array<int,2> instruction);

void printout();