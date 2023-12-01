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
        return handleJRP(address);
        break;
    case Mnemonic::LDN:
        return handleLDN(address);
        break;
    case Mnemonic::STO:
        return handleSTO(address);
        break;
    case Mnemonic::SUB:
        return handleSUB(address);
        break;
    }
    return "";
}

std::string MnemonicHandler::handleJMP(int address)
{
    // mnemonic works this way
    std::cout << "Handling JMP instruction" << std::endl;             // loging for understanding in cmpt
    std::string opcode = "000";                                       // opcode for the JMP code
    std::string binaryAddress = std::bitset<13>(address).to_string(); // 13-bit binary
    std::reverse(binaryAddress.begin(), binaryAddress.end());         // left most importabt bit
    return binaryAddress + opcode + "0000000000000000";               // added the padding 0's for the 32 bit address
}
std::string MnemonicHandler::handleJRP(int address)
{
    std::cout << "Handling JRP instruction" << std::endl;
    std::string opcode = "100";
    std::string binaryAddress = std::bitset<13>(address).to_string();
    std::reverse(binaryAddress.begin(), binaryAddress.end());
    return binaryAddress + opcode + "0000000000000000";
}
std::string MnemonicHandler::handleLDN(int address)
{
    std::cout << "Handling LDN instruction" << std::endl;
    std::string opcode = "010";
    std::string binaryAddress = std::bitset<13>(address).to_string();
    std::reverse(binaryAddress.begin(), binaryAddress.end());
    return binaryAddress + opcode + "0000000000000000";
}
std::string MnemonicHandler::handleSTO(int address)
{
    std::cout << "Handling STO instruction" << std::endl;
    std::string opcode = "110";
    std::string binaryAddress = std::bitset<13>(address).to_string();
    std::reverse(binaryAddress.begin(), binaryAddress.end());
    return binaryAddress + opcode + "0000000000000000";
}
std::string MnemonicHandler::handleSUB(int address)
{
    std::cout << "Handling SUB instruction" << std::endl;
    std::string opcode = "001";
    std::string binaryAddress = std::bitset<13>(address).to_string();
    std::reverse(binaryAddress.begin(), binaryAddress.end());
    return binaryAddress + opcode + "0000000000000000";
}
std::string MnemonicHandler::handleCPM()
{
    std::cout << "Handling CPM instruction" << std::endl;
    std::string opcode = "011";
    return "0000000000000" + opcode + "0000000000000000"; // No address needed, filled with zeros
}
std::string MnemonicHandler::handleSTP()
{
    std::cout << "Handling STP instruction" << std::endl;
    std::string opcode = "111";
    return "0000000000000" + opcode + "0000000000000000"; // No address needed, filled with zeros
}