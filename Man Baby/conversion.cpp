#include <cstdlib>
#include <iostream>

using namespace std;

string binToDec(string bin)
{
    int sum;
    int binaryMult = 1;
    int hold;
    int sign = 1;

    if (bin[0] == 1)
    {
        sign = -1;
        bin = getNegative(bin);
    }
    for (int i = bin.length() - 1; i > 0; i--)
    {
        hold = (int)bin[i];
        hold *= binaryMult;
        sum += hold;
        binaryMult *= 2;
    }

    sum *= sign;
    return to_string(sum);
}

string binToMne(string bin)
{

    int binInt = stoi(bin);

    switch (binInt)
    {
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

string getNegative(string twosComp)
{

    string hold;

    for (int i = 0; i < twosComp.length() - 1; i++)
    {
        if (twosComp[i] == '0')
        {
            hold.append("1");
        }
        else
        {
            hold.append("0");
        }
    }

    if (twosComp[twosComp.length()] == '0')
    {
        hold.append("0");
    }
    else
    {
        hold.append("1");
    }

    return hold;
}