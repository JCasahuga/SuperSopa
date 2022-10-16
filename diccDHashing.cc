#include "diccDHashing.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// En Aquest Algoritme Treballarem Els Caracters Com Enters
// Per Tal de Indexar-los En La Taula

//Constructor
diccDHashing::diccDHashing(){}

// Hash the string as Int so Double Hashing if possible
unsigned int diccDHashing::stringToInt(const string& s) {
    const int8_t p = 31; // Aprop  del numero de caracters
    const uint32_t m = INT64_C(1) << (sizeof(int)*8 - 1);
    int hash_value = 0;
    int32_t p_pow = 1;
    for (uint8_t i = 0; i < s.size(); ++i) {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Explores All Combinations of the Soup
void diccDHashing::exploreSoup() {
    vector<vector<bool>> used = vector<vector<bool>>(soupSize, vector<bool>(soupSize, false));
    string s = "";
    for (uint16_t i = 0; i < soupSize; ++i) {
        for (uint16_t j = 0; j < soupSize; ++j) {
            exploreSoupDeep(s, i, j, used, 1);
            if (printProgress) {
                float val = 100*((i*soupSize)+j) / (soupSize*soupSize);
                printLoadingBar(val);
            }
        }
    }
    if(printProgress) printLoadingBar(100);
    cout << "Total Words Found " << wordsTrobades.size() << endl;
}

// Reads Words
void diccDHashing::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords);
    totalWordsLenght = vector<int>(25, 0);

    for (int32_t i = 0; i < totalWords; ++i) {
        cin >> words[i];
        for (int8_t j = 0; j <= words[i].size(); j++)
            ++totalWordsLenght[j];
        maxWordSize = max(maxWordSize, int(words[i].size()));
        minWordSize = min(minWordSize, int(words[i].size()));
    }

    tableSize = totalWords << 4;

    totalPrefixs = maxWordSize - 2;
    preHT = vector<hashingTable>(totalPrefixs);
    tSPrefix = vector<int>(totalPrefixs);
    prefixSizes = vector<int8_t>(totalPrefixs);

    for (int8_t i = 0; i < totalPrefixs; ++i) {
        const uint8_t val = i + 2;
        prefixSizes[i] = val;
        tSPrefix[i] = totalWordsLenght[val] << 4;
    }
    assignWords();
}

// Reads Subset
void diccDHashing::readSubset() {
    int subsetWords;
    cin >> subsetWords;
    for (int32_t i = 0; i < subsetWords; ++i) {
        string w;
        cin >> w;
        subset.insert(w);
    }
}

// Read Soup
void diccDHashing::readSoup () {
    // Read Soup Size
    cin >> soupSize;
    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (uint16_t i = 0; i < soupSize; ++i)
        for (uint16_t j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
}

// Prints a Loading Bar -> val = [0..100]
void diccDHashing::printLoadingBar(const float val) {
    int valAux = val / 10;
    cout << "[";
    for (int i = 0; i < valAux & i < 5; ++i) cout << "=";
    for (int i = 0; i < 5 - valAux & i < 5; ++i) cout << " ";
    cout << val << "%";
    for (int i = 0; i < valAux - 5 & i < 5; ++i) cout << "=";
    for (int i = 0; i < (10 - valAux) & i < 5; ++i) cout << " ";
    cout << "]";
    cout << endl;
}

// Explores All Combinations of the Soup
void diccDHashing::exploreSoupDeep(string& s, int16_t x, int16_t y, vector<vector<bool>>& used, const uint8_t total) {
    // Set
    used[x][y] = true;
    s.push_back(soup[x][y]);

    // Over Maximum Size Word
    if (total >= maxWordSize) {
        // Unset
        used[x][y] = false;
        s.pop_back();
        return;
    }
    
    // Is in the Hash Table?
    const int v = stringToInt(s);
    
    if (total >= minWordSize && hT.search(v))
        wordsTrobades.insert(s);
    
    if (usePrefixPruning) {
        for (uint8_t i = 0; i < totalPrefixs; ++i) {
            if (total == prefixSizes[i]) {
                if (!preHT[i].search(v)) {
                    used[x][y] = false;
                    s.pop_back();
                    return;
                }
            }
        }
    }
        
    // Loops to All Directions
    for (uint8_t i = 0; i < 8; ++i) {
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
    for (int32_t i = 0; i < totalPrefixs; ++i)
        preHT[i].doubleHash(tSPrefix[i]);
        
    for (int32_t i = 0; i < totalWords; ++i) {
        if (!hT.insert(stringToInt(words[i]))) {
            tableSize <<= 1;
            assignWords();
        }

        if (usePrefixPruning) {
            for (int8_t j = 0; j < totalPrefixs; ++j) {
                if (words[i].size() > prefixSizes[j]) {
                    if(!preHT[j].insert(stringToInt(words[i].substr(0, prefixSizes[j])))) {
                        tSPrefix[j] <<= 1;
                        assignWords();
                    }
                }
            }
        }
    }
}

// Reads Input (Words & Soup)
void diccDHashing::readInput() {
    readWords();
    readSubset();
    readSoup();
}

// Checks if the subset has been found
void diccDHashing::checkSubset() {
    if (includes(wordsTrobades.begin(), wordsTrobades.end(), subset.begin(), subset.end()))
        cout << "Les paraules del subconjunt es troben incloses a les paraules que ha trobat la DHashing" << endl;
}