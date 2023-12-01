#include <iostream>
#include <array>
#include <fstream>

using namespace std;

void fetch(int ci, ifstream store);

array<int,2> decode(string instruction);

int execute(int accumulator, array<int,2> instruction, int programCounter);

void printout();