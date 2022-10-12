#include <string>
#include <vector>
#include <set>
using namespace std;

#ifndef _DICCDHASHING_HH_
#define _DICCDHASHING_HH_

class diccDHashing
{
    public:
        //Constructores
        diccDHashing();

        // Check if value is Prime
        bool isPrime(const long int n);

        // Initialize Hash Table
        void doubleHash(long int size);

        // Returns value of h1(s)
        unsigned long int  hash1(long int  s);

        // Returns value of h2(s)
        unsigned long int  hash2(long int  s);

        // Inserts Value Into Table If Possible
        bool insert(long int  value);

        // Inserts Prefix Value Into Table If Possible
        bool insertPrefix(long int  value);

        // Inserts Prefix Value Into Table If Possible
        bool insertPrefix2(long int  value);

        // Searches Value in the Table
        bool search(long int  value);

        bool searchPrefix(long int  value);

        bool searchPrefix2(long int  value);

        // Erases Value of the Table
        void erase(long int  value);

        // Returns true if the Table is Full
        bool isFull();

        // Hash the string as Int so Double Hashing is possible
        unsigned long int stringToInt(string s);

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
        vector<int> prefixHashTable;
        vector<int> prefixHashTable2;
        long int keysPresent = 0;
        long int tableSize = INT64_C(1) << 2;
        long int prime;

        // Soup
        int soupSize;
        vector<vector<char>> soup;

        // Possible Directions to Move in the Soup
        const vector<int> offSetsX = {1, -1, 0, 0, 1, 1, -1, -1};
        const vector<int> offSetsY = {0, 0, 1, -1, 1, -1, -1, 1};

        // Words
        int maxWordSize = 0;
        int totalWords;
        int totalFound = 0;
        vector<string> words;
        set<string> wordsTrobades;

        bool usePrefixPruning = true;
};

#endif
