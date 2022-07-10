#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define TAM_MAX_CHAVE 20

using namespace std;

string normText(string);

string juntText(string);

string cifrador(string, string);

string decifrador(string, string);

double indCoincid(string);

int tamChave(string);

char frequencia(string, int);

string quebraChave(int, int);

void descChave(string, int);