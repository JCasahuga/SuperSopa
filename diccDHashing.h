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
    private:
        // Hash the string as Int so Double Hashing if possible
        unsigned int stringToInt(const string& s);

        // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int16_t x, int16_t y, vector<vector<bool>>& used, const uint8_t total);

        // Reads Words
        void readWords ();

        // Reads Subset
        void readSubset();

        // Reads Soup
        void readSoup ();

        // Prints a Loading Bar -> val = [0..100]
        void printLoadingBar(float val);

        // Hash Table & Parameters
        hashingTable hT;
        int tableSize;
        
        // Soup
        int soupSize;
        vector<vector<char>> soup;

        // Possible Directions to Move in the Soup
        const vector<int8_t> offSetsX = {1, -1, 0, 0, 1, 1, -1, -1};
        const vector<int8_t> offSetsY = {0, 0, 1, -1, 1, -1, -1, 1};

        // Words
        int maxWordSize = 0;
        int minWordSize = 64;
        int16_t totalWords;
        vector<int> totalWordsLenght;
        vector<string> words;
        set<string> wordsTrobades = set<string>();
        set<string> subset = set<string>();

        // Control Prefixs
        int8_t totalPrefixs;
        vector<int> tSPrefix;
        vector<int8_t> prefixSizes;
        vector<hashingTable> preHT;

        // Settings
        bool usePrefixPruning = true;
        bool printProgress = false;

    public:
        //Constructors
        diccDHashing();

        // Explores All Combinations of the Soup
        void exploreSoup();

        // Assigns Words to the Map, if they don't fit, multiply the size by 2
        void assignWords();

        // Reads Input (Words & Soup)
        void readInput();

        // Checks if the subset has been found
        void checkSubset();
};
#endif