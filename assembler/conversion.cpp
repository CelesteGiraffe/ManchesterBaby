#include <cstdlib>
#include <iostream>

using namespace std;

string binToDec(string bin){
    int sum;
    int binaryMult = 1;
    int hold;


        for(int i = bin.length() - 1; i > 0; i--){
            hold = (int)bin[i];
            hold *= binaryMult;
            sum += hold;
            binaryMult *= 2;
        }
        return to_string(sum);
}

string binToMne(string bin){

    int binInt = stoi(bin);

    switch(binInt){
        case 0:
            return "JMP";

        case 100:
            return "JRP";
        
        case 10:
            return "LDN";
        
        case 110:

            return "STO";
        
        case 1:
        case 101:

            return "SUB";

        case 11:

            return "CMP";

        case 111:

            return "STP";
        
    }
    
}