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
    if (argc == 3)
    {
        startCipherOrDecipher(argv);
    }
    else
    {
        showInfoMessage();
    }
    return 0;
}

void startCipherOrDecipher(char **argv)
{
    std::string command = argv[1];
    std::string secondArgument = argv[2];
    std::string inputMessage;
    std::string outputMessage;

    if (command == "cifrar")
    {
        inputMessage = readFromFile("cipher_message.txt");

        outputMessage = cipher(inputMessage, secondArgument);
        std::cout << outputMessage << std::endl;
    }
    else if (command == "decifrar")
    {
        inputMessage = readFromFile("decipher_message.txt");

        outputMessage = decipher(inputMessage, secondArgument);
        std::cout << outputMessage << std::endl;
    }
    else if (command == "analisar")
    {
        inputMessage = readFromFile("analyze_message.txt");
        outputMessage = guessKeyByMessage(inputMessage, secondArgument);
        std::cout << outputMessage << std::endl;
    }
    else
    {
        std::cout << "Comando não encontrado.\n\n";
        showInfoMessage();
    }
}

void showInfoMessage()
{
    std::cout << "Comandos disponíveis:\n";
    std::cout << "\t`cifrar $senha` sendo $senha a palavra a ser usada para cifrar\n";
    std::cout << "\t`decifrar $senha` sendo $senha a palavra a ser usada para decifrar\n";
    std::cout << "\t`analisar $lingua` sendo $lingua igual a `pt` ou `en`\n";
    std::cout << "\nExemplos:\n";
    std::cout << "./vigenere cifrar DINOSSAURO\n";
    std::cout << "./vigenere analisar pt\n";
}
