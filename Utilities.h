﻿#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>


using namespace std;

bool checkletters (const char str[]);
bool checkletters (const string str);

void cleanWord (char str[]);
void cleanWord (string str);

bool checkResId(string identification);
#endif // UTILITIES_H
