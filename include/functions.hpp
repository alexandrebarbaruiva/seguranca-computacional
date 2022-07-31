#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

#define TAM_MAX_CHAVE 20


std::string normText(std::string);

std::string juntText(std::string);

double indCoincid(std::string);

int tamChave(std::string);

char frequencia(std::string, int);

std::string quebraChave(int, int);

void descChave(std::string, int);