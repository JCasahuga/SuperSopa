#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "hashingTable.h"
using namespace std;

#ifndef _DICCDHASHING_HH_
#define _DICCDHASHING_HH_

class diccDHashing
{
    public:
        //Constructores
        diccDHashing();

        // Sends a BFS dor each letter on the soup
        void exploreSoup();

        // Assigns Words to the Map, if they don't fit, multiply the size by 2
        void assignWords();

        void readInput();

        void readWords ();

        void readSoup ();

        // Hash Table & Parameters
        hashingTable hT;
        long int tableSize = INT64_C(1) << 2;

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

        int totalPrefixs = 3;
        vector<int> prefixValues = vector<int>(10, 0);
        vector<hashingTable> preHT = vector<hashingTable>(10);
        bool usePrefixPruning = true;

    private:
        // Hash the string as Int so Double Hashing is possible
        unsigned long int stringToInt(string s);

        // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total);

};

#endif
