#include <iostream>
#include <array>
#include <fstream>

#include "conversion.hpp"

using namespace std;

string fetch(int ci, ifstream store){
    string instruction;
    for(int lineNumber = 0; getline(store,instruction) && lineNumber<= ci; lineNumber++){
        if(lineNumber == ci){
            return instruction;
        }
    }
}

array<string,2> decode(string instruction){
    //First five characters of binary are line of store to be operated on, next 8 are ignored, next 3 are instruction, rest are ignored

    string operand = binToDec(instruction.substr(0, 4));
    string mnemonic = binToMne(instruction.substr(13, 15));

    array<string,2> mneOperand = {mnemonic, operand};

    return mneOperand;

}

void execute(int accumulator, array<string,2> instruction){
    //000 - JMP S (Jump to instruction obtained from memory address S)
    //100 - JRP S (Jump to instruction at the program counter plus relative value from memory address S) 
    //010 - LDN S (Take number from S, negate it, load into accumulator)
    //110 - STO S (Store number in the accumulator to memory address S)
    //001 or 101 - SUB S (Subtract the number at memory address S from value in accumulator, store in accumulator)
    //011 - CMP (Skip next instruction if accumulator is negative)
    //111 - STP (Stop)

    
}

void printout(){

}