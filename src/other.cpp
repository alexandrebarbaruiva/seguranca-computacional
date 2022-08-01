/**
 * @file other.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Other functions implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/other.hpp"

std::string readFromFile(std::string fileName)
{
    std::ifstream messageFile(fileName);
    std::stringstream messageContent;
    if (messageFile.is_open())
    {
        messageContent << messageFile.rdbuf();
        return messageContent.str();
    }
    return "";
}

std::string convertToUpper(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

std::string removeNonAlpha(std::string text)
{
    text.erase(
        std::remove_if(
            text.begin(), text.end(), [](char c)
            { return !std::isalpha(c); }),
        text.end());
    return text;
}
