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
#include "../include/recover.hpp"

int MAX_KEY_LENGTH = 20;
std::string ALPHABET = "ABCDEFGHIJLKMNOPQRSTUVWXYZ";

std::unordered_map<char, int> getAllLettersFrequency(std::string section)
{
    std::unordered_map<char, int> letterFrequency;
    for (const char &c : ALPHABET)
    {
        letterFrequency[c] = 0;
    }

    for (const char &c : section)
    {
        letterFrequency[c]++;
    }

    return letterFrequency;
}

// Get index of coincidence from ciphered section.
float getIndexCoincidence(std::string section)
{
    float N = section.length();
    float frequencySum = 0.0;
    std::unordered_map<char, int> lettersFrequency = getAllLettersFrequency(section);

    for (const char &letter : ALPHABET)
    {
        std::unordered_map<char, int>::const_iterator letterFreq = lettersFrequency.find(letter);
        float temp = letterFreq->second * (letterFreq->second - 1);
        frequencySum += temp;
    }
    // Formula for index of coincidence
    return frequencySum / (N * (N - 1));
}

int findKeyLength(std::string message)
{
    std::vector<float> indexCoincidenceTable;
    for (int probableSize = 0; probableSize < MAX_KEY_LENGTH; probableSize++)
    {
        float indexCoincidenceSum = 0.0;
        float averageIndexCoincidence = 0.0;
        for (int i = 0; i < probableSize; i++)
        {
            std::string currentSequence = "";
            for (int j = 0; j < (message.size() - i); j++)
            {
                currentSequence.push_back(message[(i + j)]);
            }
            indexCoincidenceSum += getIndexCoincidence(currentSequence);
        }
        if (probableSize != 0)
        {
            averageIndexCoincidence = indexCoincidenceSum / probableSize;
        }
        indexCoincidenceTable.push_back(averageIndexCoincidence);
    }

    return 0;
}
