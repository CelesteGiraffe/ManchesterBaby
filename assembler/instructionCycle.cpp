#include <iostream>
#include <array>
#include <fstream>

using namespace std;

void fetch(int ci, ifstream store){
    string instruction;
    for(int lineNumber = 0; getline(store,instruction) && lineNumber<= ci; lineNumber++){
        if(lineNumber == ci){
            decode(instruction);
        }
    }
}

array<int,2> decode(string instruction){
    //First five characters of binary are line of store to be operated on, next 8 are ignored, next 3 are instruction, rest are ignored
    //000 - JMP S (Jump to instruction obtained from memory address S)
    //100 - JRP S (Jump to instruction at the program counter plus relative value from memory address S) 
    //010 - LDN S (Take number from S, negate it, load into accumulator)
    //110 - STO S (Store number in the accumulator to memory address S)
    //001 or 101 - SUB S (Subtract the number at memory address S from value in accumulator, store in accumulator)
    //011 - CMP (Skip if accumulator is negative)
    //111 - STP (Stop)
}

void execute(int accumulator, array<int,2> instruction){

}

void printout(){

}