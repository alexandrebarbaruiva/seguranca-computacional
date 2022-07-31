/**
 * @file cipher.hpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Cipher header file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CIPHER_HEADER
#define CIPHER_HEADER
#include "other.hpp"
#include <string>
#include <string>


std::string cipher(std::string message, std::string messageKey);

std::string decipher(std::string message, std::string messageKey);

#endif
