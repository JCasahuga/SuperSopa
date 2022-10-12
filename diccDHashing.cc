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

diccDHashing::diccDHashing(const int& p){
    prime = p; 
}

// Check if value is Prime
bool diccDHashing::isPrime(const int n)
{
    if (n == 1 || n == 0)
        return false;

    int s = sqrt(n);
    for (int i = 2; i < s; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Initialize Hash Table
void diccDHashing::doubleHash(int size) {
    tableSize = size;
    
    prime = size - 1;
    while (!isPrime(prime)) ++prime;
    hashTable = vector<int>(prime, -1);
}

// Returns value of h1(s)
unsigned int diccDHashing::hash1(int s) {
    return s%tableSize;
}

// Returns value of h2(s)
unsigned int diccDHashing::hash2(int s) {
    return prime - (s%prime);
}

// Inserts Value Into Table If Possible
bool diccDHashing::insert(int value) {
    if (value == -1 || value == -2)
        cerr << "Can't be Inserted" << endl;

    int hashed = hash1(value);
    int offset = hash2(value);
    int initialPos = hashed;
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

// Searches Value in the Table
bool diccDHashing::search(int value) {
    int hashed = hash1(value);
    int offset = hash2(value);
    int initialPos = hashed;
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

// Erases Value of the Table
void diccDHashing::erase(int value) {
    if(!search(value))
        return;    
        
    int hashed = hash1(value);
    int offset = hash2(value);

    while(hashTable[hashed] != -1) {
        if(hashTable[hashed] == value){
            hashTable[hashed] = -2;
            keysPresent--;
            return;
        }
        else hashed = (hashed + offset) % tableSize;
    }
}

// Returns true if the Table is Full
bool diccDHashing::isFull() {
    return keysPresent == tableSize;
}

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
    vector<vector<char>> used = soup;
    string s = "";
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            exploreSoupDeep(s, i, j, used, 1);
}

// Explores All Combinations of the Soup
void diccDHashing::exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total) {
    // Set
    used[x][y] = -1;
    s.push_back(soup[x][y]);

    // Is in the Hash Table?
    const int v = stringToInt(s);
    if (search(v)) cerr << "Found " << s << " Value " << v << endl;

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
        if (insert(stringToInt(words[i]))) {
            int size = words[i].size();
            maxWordSize = max(size, maxWordSize);
        } else {
            keysPresent = 0;
            tableSize <<= 1;
            assignWords();
        }
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
    for (int i = 0; i < totalWords; ++i) 
        cin >> words[i];
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
