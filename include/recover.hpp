/**
 * @file recover.hpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Recover header file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef RECOVER_HEADER
#define RECOVER_HEADER
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include "other.hpp"

std::unordered_map<char, int> getAllLettersFrequency(std::string section);

float getIndexCoincidence(std::string section);

int findKeyLength(std::string message);

std::string checkDuplicatedSubsetOnKey(std::string key);

std::string findKey(std::string message, int keyLength);

char analyzeFrequency(std::string sequence);

std::string guessKeyByMessage(std::string message, std::string language="en");

#endif
