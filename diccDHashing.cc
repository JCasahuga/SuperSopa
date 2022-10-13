#include "diccDHashing.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// En Aquest Algoritme Treballarem Els Caracters Com Enters
// Per Tal de Indexar-los En La Taula

//Constructors

diccDHashing::diccDHashing(){}

// Hash the string as Int so Double Hashing is possible
unsigned long int diccDHashing::stringToInt(string s) {
    const int p = 31; // Aprop  del numero de caracters
    const unsigned long int m = INT64_C(1) << (sizeof(long int)*8 - 1);
    unsigned long int hash_value = 0;
    long int p_pow = 1;
    for (int i = 0; i < s.size(); ++i) {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Sends a BFS dor each letter on the soup
void diccDHashing::exploreSoup() {
    vector<vector<char>> used = soup;
    string s = "";
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            exploreSoupDeep(s, i, j, used, 1);

    cout << "Total Words Found " << wordsTrobades.size() << endl;
}

// Explores All Combinations of the Soup
void diccDHashing::exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total) {
    // Set
    used[x][y] = -1;
    s.push_back(soup[x][y]);

    // Is in the Hash Table?
    const long int v = stringToInt(s);
    //search(v);
    if (hT.search(v)) {
        wordsTrobades.insert(s);
    }

    if (usePrefixPruning) {
        for (int i = 0; i < totalPrefixs; ++i) {
            if (total == prefixValues[i]) {
                if (!preHT[i].search(v)) {
                    used[x][y] = soup[x][y];
                    s.pop_back();
                    return;
                }
            }
        }
    }

    // Over Maximum Size Word
    if (total >= maxWordSize) {
        // Unset
        used[x][y] = soup[x][y];
        s.pop_back();
        return;
    }

    // Loops to All Directions
    for (int8_t i = 0; i < 8; ++i) {
        x += offSetsX[i];
        y += offSetsY[i];
        if (min(x, y) >= 0 && max(x, y) < soupSize) {
            char aux = used[x][y];
            if (aux != -1) {
                used[x][y] = -1;
                exploreSoupDeep(s, x, y, used, total+1);
                used[x][y] = aux;
            }
        }
        x -= offSetsX[i];
        y -= offSetsY[i];
    }
    
    // Unset
    s.pop_back();
    used[x][y] = soup[x][y];
}

// Assigns Words to the Map, if they don't fit, multiply the size by 2
void diccDHashing::assignWords() {
    hT.doubleHash(tableSize);
    for (int i = 0; i < totalPrefixs; ++i) preHT[i].doubleHash(tableSize);

    for (int i = 0; i < totalWords; ++i) {
        if (!hT.insert(stringToInt(words[i]))) {
            tableSize <<= 1;
            assignWords();
        }
        if (usePrefixPruning) {
            for (int i = 0; i < totalPrefixs; ++i) {
                if (words[i].size() >= prefixValues[i]) {
                    cout << words[i].substr(0,prefixValues[i]) << endl;
                    if(!preHT[i].insert(stringToInt(words[i].substr(0,prefixValues[i])))) {
                        cout << "exited "<< prefixValues[i] << endl;
                        tableSize <<= 1;
                        assignWords();
                    }
                }
            }
        }
    }
    /*for (int i = 0; i < totalPrefixs; ++i)
        cout << prefixValues[i] << endl;
    cout << tableSize << endl;*/
}

void diccDHashing::readInput() {    
    readWords();
    readSoup();
    cerr << "Hashed Values!" << endl;
}

void diccDHashing::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) {
        cin >> words[i];
        maxWordSize = max(maxWordSize, int(words[i].size()));
    }

    for (int i = 1; i <= totalPrefixs; ++i) {
        int val = ((maxWordSize-5)/(totalPrefixs)) * (i-1) + 6;
        prefixValues[i-1] = val - 1;
        cout << prefixValues[i-1] << endl;
    }
    assignWords();
}

void diccDHashing::readSoup () {
    // Read Soup Size
    cin >> soupSize;
    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
}