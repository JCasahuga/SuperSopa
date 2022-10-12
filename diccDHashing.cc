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

// Check if value is Prime
bool diccDHashing::isPrime(const long int  n)
{
    if (n == 1 || n == 0)
        return false;

    long int s = sqrt(n);
    for (int i = 2; i < s; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Initialize Hash Table
void diccDHashing::doubleHash(long int size) {
    tableSize = size;
    
    prime = size - 1;
    while (!isPrime(prime)) --prime;
    hashTable = vector<int>(prime, -1);
    prefixHashTable = vector<int>(prime, -1);
    prefixHashTable2 = vector<int>(prime, -1);
}

// Returns value of h1(s)
unsigned long int diccDHashing::hash1(long int  s) {
    return s%tableSize;
}

// Returns value of h2(s)
unsigned long int diccDHashing::hash2(long int  s) {
    return prime - (s%prime);
}

// Inserts Value Into Table If Possible
bool diccDHashing::insert(long int value) {
    if (value == -1 || value == -2)
        cerr << "Can't be Inserted" << endl;

    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;

    while (hashTable[hashed] != -1) {
        if (initialPos == hashed && !firstItr) return false;
        if (hashTable[hashed] == -2) break;
        hashed = (hashed+offset) % tableSize;
        firstItr = false;
    }

    hashTable[hashed] = value;
    ++keysPresent;
    return true;
}

bool diccDHashing::insertPrefix(long int value) {
    if (value == -1 || value == -2)
        cerr << "Can't be Inserted" << endl;

    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;

    while (prefixHashTable[hashed] != -1) {
        if (initialPos == hashed && !firstItr) return false;
        if (prefixHashTable[hashed] == -2) break;
        hashed = (hashed+offset) % tableSize;
        firstItr = false;
    }

    prefixHashTable[hashed] = value;
    ++keysPresent;
    return true;
}

bool diccDHashing::insertPrefix2(long int value) {
    if (value == -1 || value == -2)
        cerr << "Can't be Inserted" << endl;

    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;

    while (prefixHashTable2[hashed] != -1) {
        if (initialPos == hashed && !firstItr) return false;
        if (prefixHashTable2[hashed] == -2) break;
        hashed = (hashed+offset) % tableSize;
        firstItr = false;
    }

    prefixHashTable2[hashed] = value;
    ++keysPresent;
    return true;
}

// Searches Value in the Table
bool diccDHashing::search(long int value) {
    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;
    while(true) {
        if(hashTable[hashed] == -1)                  
            break;
        else if(hashTable[hashed] == value)      
            return true;
        else if(hashed == initialPos && !firstItr)    // Stop search if one complete traversal of hash table is completed.
            return false;
        else
            hashed = ((hashed + offset) % tableSize);  // if none of the above cases occur then update the index and check at it.

        firstItr = false;
    }
    return false;
}

bool diccDHashing::searchPrefix(long int value) {
    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;
    while(true) {
        if(prefixHashTable[hashed] == -1)                  
            break;
        else if(prefixHashTable[hashed] == value)      
            return true;
        else if(hashed == initialPos && !firstItr)    // Stop search if one complete traversal of hash table is completed.
            return false;
        else
            hashed = ((hashed + offset) % tableSize);  // if none of the above cases occur then update the index and check at it.

        firstItr = false;
    }
    return false;
}

bool diccDHashing::searchPrefix2(long int value) {
    long int hashed = hash1(value);
    long int offset = hash2(value);
    long int initialPos = hashed;
    bool firstItr = true;
    while(true) {
        if(prefixHashTable2[hashed] == -1)                  
            break;
        else if(prefixHashTable2[hashed] == value)      
            return true;
        else if(hashed == initialPos && !firstItr)    // Stop search if one complete traversal of hash table is completed.
            return false;
        else
            hashed = ((hashed + offset) % tableSize);  // if none of the above cases occur then update the index and check at it.

        firstItr = false;
    }
    return false;
}

// Erases Value of the Table
/*
void diccDHashing::erase(long int value) {
    if(!search(value))
        return;    
        
    long int  hashed = hash1(value);
    long int  offset = hash2(value);

    while(hashTable[hashed] != -1) {
        if(hashTable[hashed] == value){
            hashTable[hashed] = -2;
            keysPresent--;
            return;
        }
        else hashed = (hashed + offset) % tableSize;
    }
}
*/

// Returns true if the Table is Full
bool diccDHashing::isFull() {
    return keysPresent == tableSize;
}

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
    if (search(v)) {
        //cerr << "Found " << s << " Value " << v << endl;
        wordsTrobades.insert(s);
    }

    if (usePrefixPruning) {
        if (total == 6) {
            if (!searchPrefix(v)) {
                used[x][y] = soup[x][y];
                s.pop_back();
                return;
            }
        }

        if (total == 12) {
            if (!searchPrefix(v)) {
                used[x][y] = soup[x][y];
                s.pop_back();
                return;
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
    doubleHash(tableSize);
    for (int i = 0; i < totalWords; ++i) {
        //if (words[i].size() == 21) cerr << "biggest word "<< words[i] << endl;
        if (!insert(stringToInt(words[i]))) {
            keysPresent = 0;
            tableSize <<= 1;
            assignWords();
        }
        if (usePrefixPruning) {
            if (words[i].size() >= 7) insertPrefix(stringToInt(words[i].substr(0,6)));
            if (words[i].size() >= 13) insertPrefix(stringToInt(words[i].substr(0,12)));
        }
        //if (words[i].size() >= 13) insertPrefix2(stringToInt(words[i].substr(0,12)));
    }
    //cerr << "table size " <<tableSize << endl << " max word size " << maxWordSize << endl; 
}

void diccDHashing::readInput() {
    readWords();
    readSoup();
}

void diccDHashing::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) {
        cin >> words[i];
        maxWordSize = max(maxWordSize, int(words[i].size()));
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