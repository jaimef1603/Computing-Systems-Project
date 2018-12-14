#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <vector>
#include "ArrayList.h"

using namespace std;

bool checkletters (const char str[]);
bool checkletters (const string str);

void cleanWord (char str[]);
void cleanWord (string str);
bool checkStuId(string id);
bool checkResId(string identification);

void UCaseWord(string& word);

template <typename A> void ListshowAll(vector<A>);
template <typename A> void ListshowAll(ArrayList<A>);
template <typename A> void ListshowAllDetails(vector<A>);
template <typename A> void ListshowAllDetails(ArrayList<A>);




#endif // UTILITIES_H
