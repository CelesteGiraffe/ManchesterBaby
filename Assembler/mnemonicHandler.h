#pragma once
#include "mnemonic.h"
#include <string>
#include <iostream>

class MnemonicHandler
{
public:
    MnemonicHandler();
    std::string parse(Mnemonic);
    std::string parse(Mnemonic, int);

private:
    std::string handleJMP(int address);
    std::string handleJRP();
    std::string handleLDN();
    std::string handleSTO();
    std::string handleSUB();
    std::string handleCPM();
    std::string handleSTP();
    std::string handleUnknown();
};