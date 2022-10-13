#include "diccDHashing.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// En Aquest Algoritme Treballarem Els Caracters Com Enters
// Per Tal de Indexar-los En La Taula

//Constructors

diccDHashing::diccDHashing(){}

// Hash the string as Int so Double Hashing is possible
unsigned int diccDHashing::stringToInt(string s) {
    const int p = 31; // Aprop  del numero de caracters
    const unsigned int m = INT64_C(1) << (sizeof(int)*8 - 1);
    unsigned int hash_value = 0;
    int p_pow = 1;
    for (int i = 0; i < s.size(); ++i) {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Sends a BFS dor each letter on the soup
void diccDHashing::exploreSoup() {
    vector<vector<bool>> used = vector<vector<bool>>(soupSize, vector<bool>(soupSize, false));
    string s = "";
    for (int i = 0; i < soupSize; ++i) {
        for (int j = 0; j < soupSize; ++j) {
            exploreSoupDeep(s, i, j, used, 1);
            //float val = 100*((i*soupSize)+j) / (soupSize*soupSize);
            //printLoadingBar(val);
        }
    }
    //printLoadingBar(100);
    cout << "Total Words Found " << wordsTrobades.size() << endl;
}

void diccDHashing::printLoadingBar(float val) {
    int valAux = val / 10;
    cout << endl;
    cout << "[";
    for (int i = 0; i < valAux & i < 5; ++i) cout << "=";
    for (int i = 0; i < 5 - valAux & i < 5; ++i) cout << " ";
    cout << val << "%";
    for (int i = 0; i < valAux - 5 & i < 5; ++i) cout << "=";
    for (int i = 0; i < (10 - valAux) & i < 5; ++i) cout << " ";
    cout << "]";
}

// Explores All Combinations of the Soup
void diccDHashing::exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<bool>>& used, const int total) {
    // Set
    used[x][y] = true;
    s.push_back(soup[x][y]);

    // Is in the Hash Table?
    const int v = stringToInt(s);
    //search(v);
    if (hT.search(v))
        wordsTrobades.insert(s);
    if (usePrefixPruning) {
        for (int i = 0; i < totalPrefixs - 1; ++i) {
            if (total == prefixValues[i]) {
                if (!preHT[i].search(v)) {
                    used[x][y] = false;
                    s.pop_back();
                    return;
                }
            }
        }
    }
    // Over Maximum Size Word
    if (total > maxWordSize) {
        // Unset
        used[x][y] = false;
        s.pop_back();
        return;
    }
    // Loops to All Directions
    for (int8_t i = 0; i < 8; ++i) {
        x += offSetsX[i];
        y += offSetsY[i];
        if (min(x, y) >= 0 && max(x, y) < soupSize) {
            if (!used[x][y]) {
                used[x][y] = true;
                exploreSoupDeep(s, x, y, used, total+1);
                used[x][y] = false;
            }
        }
        x -= offSetsX[i];
        y -= offSetsY[i];
    }
    // Unset
    used[x][y] = false;
    s.pop_back();
}

// Assigns Words to the Map, if they don't fit, multiply the size by 2
void diccDHashing::assignWords() {
    hT.doubleHash(tableSize);
    for (int i = 0; i < totalPrefixs - 1; ++i) preHT[i].doubleHash(tableSize);

    for (int i = 0; i < totalWords; ++i) {
        if (!hT.insert(stringToInt(words[i]))) {
            tableSize <<= 1;
            assignWords();
        }

        if (usePrefixPruning) {
            for (int j = 0; j < totalPrefixs - 1; ++j) {
                if (words[i].size() > prefixValues[j]) {
                    if(!preHT[j].insert(stringToInt(words[i].substr(0,prefixValues[j])))) {
                        tableSize <<= 1;
                        assignWords();
                    }
                }
            }
        }
    }
}

void diccDHashing::readInput() {
    readWords();
    readSubset();
    readSoup();
}

void diccDHashing::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) {
        cin >> words[i];
        maxWordSize = max(maxWordSize, int(words[i].size()));
    }

    tableSize = INT64_C(1) << int(log(totalWords));
    totalPrefixs = maxWordSize / 2;
    for (int i = 1; i < totalPrefixs; ++i) {
        int val = (maxWordSize/totalPrefixs) * i;
        prefixValues[i-1] = val;
    }
    assignWords();
}

void diccDHashing::readSubset() {
    int subsetWords;
    cin >> subsetWords;
    for (int i = 0; i < subsetWords; ++i) {
        string w;
        cin >> w;
        subset.insert(w);
    }
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

void diccDHashing::checkSubset() {
    if (includes(wordsTrobades.begin(), wordsTrobades.end(), subset.begin(), subset.end()))
        cout << "Les paraules del subconjunt es troben incloses a les paraules que ha trobat la DHashing" << endl;
}