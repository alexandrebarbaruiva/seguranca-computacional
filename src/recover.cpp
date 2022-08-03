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
std::vector<double> FREQUENCY;
std::vector<double> EN_FREQUENCY = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
    0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
    0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
    0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
    0.02758, 0.00978, 0.02360, 0.00150, 0.01974,
    0.00074};
std::vector<double> PT_FREQUENCY = {
    0.1463, 0.0104, 0.0388, 0.0499, 0.1257,
    0.0102, 0.0130, 0.0128, 0.0618, 0.0040,
    0.0002, 0.0278, 0.0474, 0.0505, 0.1073,
    0.0252, 0.0120, 0.0653, 0.0781, 0.0434,
    0.0463, 0.0167, 0.0001, 0.0021, 0.0001,
    0.0047};

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
    message = removeNonAlpha(message);
    std::vector<float> indexCoincidenceTable;

    // First loop to check all key sizes
    for (int probableSize = 0; probableSize < MAX_KEY_LENGTH; probableSize++)
    {
        float indexCoincidenceSum = 0.0;
        float averageIndexCoincidence = 0.0;

        for (int i = 0; i < probableSize; i++)
        {
            std::string currentSequence = "";

            for (int j = 0; j < ((int)message.size() - i + 1); j += probableSize)
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
    std::cout << "IdC:\n";
    for (int i = 0; i < (int)indexCoincidenceTable.size(); i++)
    {
        std::cout << i << ": " << indexCoincidenceTable[i] << std::endl;
    }

    // Get key length with highest index of coincidence
    int keyLength = std::max_element(indexCoincidenceTable.begin(), indexCoincidenceTable.end()) - indexCoincidenceTable.begin();
    return keyLength;
}

// Analyze frequency from subsets/sequences to get table of most likely combination
char analyzeFrequency(std::string sequence)
{
    std::vector<float> chiSquareds(26, 0.0f);
    float multiplier = (1.0 / (float)sequence.size());
    char offsetChar;

    // Check if word frequency has been properly set, else use english frequency
    if (FREQUENCY.size() != 26)
    {
        FREQUENCY = EN_FREQUENCY;
    }

    // Calculate chi squared for all letters
    for (int offsetValue = 0; offsetValue < (int)ALPHABET.size(); offsetValue++)
    {
        float chiSquaredSum = 0.0f;
        std::vector<float> observedValues(26, 0.0f);
        for (int pos = 0; pos < (int)sequence.size(); pos++)
        {
            offsetChar = (sequence[pos] - offsetValue + 65) % 26 + 'A';
            observedValues[((int)offsetChar) - 65] += (1.0 * multiplier);
        }

        for (int letter = 0; letter < (int)ALPHABET.size(); letter++)
        {
            // Calculate chi squared for all letters
            float squaredDifference = pow((observedValues[letter] - FREQUENCY[letter]), 2);
            chiSquaredSum += (squaredDifference / FREQUENCY[letter]);
        }
        chiSquareds[offsetValue] = chiSquaredSum;
    }
    int sequenceCharacter = std::min_element(chiSquareds.begin(), chiSquareds.end()) - chiSquareds.begin() + 65;

    return (char)sequenceCharacter;
}

std::string guessKeyByMessage(std::string message, std::string language)
{
    message = convertToUpper(message);
    int keyLength = findKeyLength(message);
    // Set word frequency based on language
    if (language == "pt")
    {
        FREQUENCY = PT_FREQUENCY;
    }
    else
    {
        FREQUENCY = EN_FREQUENCY;
    }

    return findKey(message, keyLength);
}

std::string findKey(std::string message, int keyLength)
{
    message = removeNonAlpha(message);
    std::string key = "";
    for (int i = 0; i < keyLength; i++)
    {
        std::string sequence = "";
        for (int j = 0; j < ((int)message.size() - i + 1); j += keyLength)
        {
            sequence.push_back(message[i + j]);
        }
        key.push_back(analyzeFrequency(sequence));
    }
    return checkDuplicatedSubsetOnKey(key);
}

std::string checkDuplicatedSubsetOnKey(std::string key)
{
    int keySize = (int)key.size();
    std::string substring;
    for (int substringSize = (keySize - 1); substringSize > 1; substringSize--)
    {
        if ((keySize % substringSize) != 0)
        {
            continue;
        }
        substring = key.substr(0, substringSize);

        int count = 0;

        for (size_t offset = key.find(substring);
             offset != std::string::npos;
             offset = key.find(substring, offset + substring.length()))
        {
            ++count;
        }
        if ((count > 1) && ((count * (int)substring.size()) == keySize))
        {
            return substring;
        }
    }
    return key;
}
