#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "hashingTable.h"
using namespace std;

// En Aquest Algoritme Treballarem Els Caracters Com Enters
// Per Tal de Indexar-los En La Taula

//Constructors
hashingTable::hashingTable(){}

// Check if value is Prime
bool hashingTable::isPrime(const int n)
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
void hashingTable::doubleHash(const int size) {
    tableSize = size;
    prime = size - 1;
    while (!isPrime(prime)) --prime;
    hashTable = vector<int>(prime, -1);
}

// Returns value of h1(s)
unsigned int hashingTable::hash1(const int  s) {
    return s%tableSize;
}

// Returns value of h2(s)
unsigned int hashingTable::hash2(const int  s) {
    return prime - (s%prime);
}

// Inserts Value Into Table If Possible
bool hashingTable::insert(const unsigned int value) {
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

void hashingTable::printHash() {
    for (int i = 0; i < tableSize; ++i) cout << hashTable[i] << endl;
}

// Searches Value in the Table
bool hashingTable::search(const unsigned int value) {
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
            hashed = ((hashed + offset) % tableSize);  // f none of the above cases occur then update the index and check at it.

        firstItr = false;
    }
    return false;
}

// Erases Value of the Table
void hashingTable::erase(const unsigned int value) {
    if(!search(value))
        return;    
        
    int  hashed = hash1(value);
    int  offset = hash2(value);

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
bool hashingTable::isFull() {
    return keysPresent == tableSize;
}

