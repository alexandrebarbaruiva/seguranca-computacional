/**
 * @file cipher.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Cipher implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/cipher.hpp"

std::string cipher(std::string message, std::string messageKey)
{
    message = convertToUpper(message);
    messageKey = convertToUpper(messageKey);
    std::string cipheredMessage;
    char temp;
    int i = 0;
    for (int j = 0; j < (int) message.size(); j++)
    {
        if (message[j] < 'A' || message[j] > 'Z')
        {
            cipheredMessage.push_back(message[j]);
            continue;
        }
        temp = (message[j] - 'A' + messageKey[i] - 'A') % 26 + 'A';
        cipheredMessage.push_back(temp);
        i = (i + 1) % messageKey.size();
    }
    return cipheredMessage;
}

std::string decipher(std::string message, std::string messageKey)
{
    message = convertToUpper(message);
    messageKey = convertToUpper(messageKey);
    std::string decipheredMessage;
    char temp;
    int i = 0;
    for (int j = 0; j < (int) message.size(); j++)
    {
        if (message[j] < 'A' || message[j] > 'Z')
        {
            decipheredMessage.push_back(message[j]);
            continue;
        }
        else
        {
            temp = (message[j] - messageKey[i] + 26) % 26 + 'A';
            decipheredMessage.push_back(temp);
            i = (i + 1) % messageKey.size();
        }
    }
    return decipheredMessage;
}
