/**
 * @file main.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Main implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/main.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        // menu();
    }
    else if (argc == 2)
    {
        startAnalysis(argv);
    }
    else if (argc == 3)
    {
        startCipherOrDecipher(argv);
    }
}

void startCipherOrDecipher(char **argv)
{
    std::string command = argv[1];
    std::string messageKey = argv[2];
    std::string inputMessage;
    std::string outputMessage;

    if (command == "cifrar")
    {
        std::cout << "cifrar " << messageKey << std::endl;

        inputMessage = readFromFile("cipher_message.txt");

        outputMessage = cipher(inputMessage, messageKey);
        std::cout << outputMessage << std::endl;
    }
    else if (command == "decifrar")
    {
        std::cout << "decifrar " << messageKey << std::endl;

        inputMessage = readFromFile("decipher_message.txt");

        outputMessage = decipher(inputMessage, messageKey);
        std::cout << outputMessage << std::endl;
    }
    else
    {
        std::cout << command << ": comando não encontrado.\n";
        std::cout << "Use `cifrar`, `decifrar` como comandos\n";
    }
}

void startAnalysis(char **argv)
{
    std::string command = argv[1];
    std::string inputMessage;
    std::string outputMessage;

    if (command == "analisar")
    {
    }
    else
    {
        std::cout << command << ": comando não encontrado.\n";
        std::cout << "Use `analisar` como comandos\n";
    }
}
