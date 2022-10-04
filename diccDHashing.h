#include <string>
#include <vector>
using namespace std;

#ifndef _DICCDHASHING_HH_
#define _DICCDHASHING_HH_

class diccDHashing
{
    public:
        //Constructores
        diccDHashing();

        diccDHashing(const int& p);

        // Check if value is Prime
        bool isPrime(const int n);

        // Initialize Hash Table
        void doubleHash(int size);

        // Returns value of h1(s)
        unsigned int hash1(int s);

        // Returns value of h2(s)
        unsigned int hash2(int s);

        // Inserts Value Into Table If Possible
        bool insert(int value);

        // Searches Value in the Table
        bool search(int value);

        // Erases Value of the Table
        void erase(int value);

        // Returns true if the Table is Full
        bool isFull();

        // Hash the string as Int so Double Hashing is possible
        unsigned int stringToInt(string s);

        // Sends a BFS dor each letter on the soup
        void exploreSoup();

        // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total);

        // Assigns Words to the Map, if they don't fit, multiply the size by 2
        void assignWords();

        void readInput();

        void readWords ();

        void readSoup ();

        // Hash Table & Parameters
        vector<int> hashTable;
        int keysPresent = 0;
        int tableSize = INT64_C(1) << 1;
        int prime;

        // Soup
        int soupSize;
        vector<vector<char>> soup;

        // Possible Directions to Move in the Soup
        const vector<int> offSetsX = {1, -1, 0, 0, 1, 1, -1, -1};
        const vector<int> offSetsY = {0, 0, 1, -1, 1, -1, -1, 1};

        // Words
        int maxWordSize = 0;
        int totalWords;
        vector<string> words;
};

#endif
