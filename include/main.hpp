/**
 * @file main.hpp
 * @author Alexandre Augusto de Sá dos Santos (150056940)
 * @author Andrey Galvao Mendes (180097911)
 * @brief Main header file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MAIN_HEADER
#define MAIN_HEADER
#include <iostream>
#include "menu.hpp"
#include "cipher.hpp"
#include "other.hpp"

int main(int argc, char **argv);
void startCipherOrDecipher(char **argv);
void startAnalysis(char **argv);

#endif
