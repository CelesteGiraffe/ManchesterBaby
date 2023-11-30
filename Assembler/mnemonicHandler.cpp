#include "mnemonicHandler.h"

MnemonicHandler::MnemonicHandler() {}

std::string MnemonicHandler::parse(Mnemonic mnemonic)
{
    switch (mnemonic)
    {
    case Mnemonic::CPM:
        return handleCPM();
        break;
    case Mnemonic::STP:
        return handleSTP();
        break;
    }
    return "Error no address or invalid";
}
std::string MnemonicHandler::parse(Mnemonic mnemonic, int address)
{
    switch (mnemonic)
    {
    case Mnemonic::JMP:
        return handleJMP(address);
        break;
    case Mnemonic::JRP:
        return handleJRP();
        break;
    case Mnemonic::LDN:
        return handleLDN();
        break;
    case Mnemonic::STO:
        return handleSTO();
        break;
    case Mnemonic::SUB:
        return handleSUB();
        break;
    case Mnemonic::CPM:
        return handleCPM();
        break;
    case Mnemonic::STP:
        return handleSTP();
        break;
    }
    return "";
}

std::string MnemonicHandler::handleJMP(int address)
{
    // do some conversion based on the type of passed variable
    std::string opcode = "000";
    std::string binaryAddress = std::bitset<13>(address).to_string(); // 13-bit binary
    std::cout << "Handling JMP instruction" << std::endl;
    std::string binary;
    return opcode + binary;
}
std::string MnemonicHandler::handleJRP()
{
    std::string opcode = "100";
    std::cout << "Handling JRP instruction" << std::endl;
    return opcode;
}
std::string MnemonicHandler::handleLDN()
{
    std::string opcode = "010";
    std::cout << "Handling LDN instruction" << std::endl;
    return opcode;
}
std::string MnemonicHandler::handleSTO()
{
    std::string opcode = "110";
    std::cout << "Handling STO instruction" << std::endl;
    return opcode;
}
std::string MnemonicHandler::handleSUB()
{
    std::string opcode = "001";
    std::cout << "Handling SUB instruction" << std::endl;
    return opcode;
}
std::string MnemonicHandler::handleCPM()
{
    std::string opcode = "011";
    std::cout << "Handling CPM instruction" << std::endl;
    return opcode;
}
std::string MnemonicHandler::handleSTP()
{
    std::string opcode = "111";
    std::cout << "Handling STP instruction" << std::endl;
    return opcode;
}