#include <cstdlib>
#include <iostream>

using namespace std;

int binToDec(string bin){
    int sum;
    int binaryMult = 1;
    int hold;


        for(int i = bin.length() - 1; i > 0; i--){
            hold = (int)bin[i];
            hold *= binaryMult;
            sum += hold;
            binaryMult *= 2;
        }
        return sum;
}