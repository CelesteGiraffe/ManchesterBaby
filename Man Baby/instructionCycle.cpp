#include <iostream>
#include <array>
#include <fstream>

#include "conversion.hpp"

using namespace std;

string fetch(int ci, string filename){

    ifstream store(filename);
    string instruction;
    for(int lineNumber = 0; getline(store,instruction) && lineNumber<= ci; lineNumber++){
        if(lineNumber == ci){
            store.close();
            return instruction;
        }
    }
}

array<string,2> decode(string instruction){
    //First five characters of binary are line of store to be operated on, next 8 are ignored, next 3 are instruction, rest are ignored

    string operand = binToDec(instruction.substr(0, 4));
    string binMne = instruction.substr(13, 15);
    string mnemonic = binToMne(binMne);

    array<string,2> mneOperand = {binMne, operand};

    return mneOperand;

}

array<int, 2> execute(int accumulator, array<string,2> instruction, int programCounter, string filename){ //returns the value of the program counter

    array<int, 2> externalValues; //accumulator,  program counter
    int holdInt;

    switch (stoi(instruction[0])){
        case 0:
            externalValues = {accumulator, stoi(instruction[1])};
        case 100:
            externalValues = {accumulator, (stoi(instruction[1]) + programCounter)};
        case 10:
            holdInt = -(getVarFromFile(filename, stoi(instruction[1])));

            accumulator = holdInt;
            externalValues = {accumulator, programCounter};
        case 110:
            //TODO


    }
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

int getVarFromFile(string filename, int address){

    ifstream store(filename);
    string binValue;
    string decValue;

    for(int lineNumber = 0; getline(store,binValue) && lineNumber<= address; lineNumber++){
        if(lineNumber == address){
           decValue = binToDec(binValue);
        }
    }
    store.close();
    return stoi(decValue);
}

void storeValue(string filename, int address){//UNFINISHED

    ifstream store(filename);
    string binValue;
    string decValue;

    for(int lineNumber = 0; getline(store,binValue) && lineNumber<= address; lineNumber++){
        if(lineNumber == address){
           decValue = binToDec(binValue);
        }
    }
    store.close();
    
}