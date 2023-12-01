#pragma once
#include "mnemonic.h"
#include <string>
#include <iostream>
#include <bitset>
#include <algorithm>

class MnemonicHandler
{
public:
    MnemonicHandler();
    std::string parse(Mnemonic);
    std::string parse(Mnemonic, int);

private:
    std::string handleJMP(int);
    std::string handleJRP(int);
    std::string handleLDN(int);
    std::string handleSTO(int);
    std::string handleSUB(int);
    std::string handleCPM();
    std::string handleSTP();
    std::string handleUnknown();
};