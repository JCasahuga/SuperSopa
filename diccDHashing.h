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

        void readSubset();

        void readSoup ();

        void checkSubset();

        void printLoadingBar(float val);

        // Hash Table & Parameters
        hashingTable hT;
        int tableSize = INT64_C(1) << 2;
        vector<int> totalWordsLenght = vector<int>(20,0);
        
        // Soup
        int soupSize;
        vector<vector<char>> soup;

        // Possible Directions to Move in the Soup
        const vector<int8_t> offSetsX = {1, -1, 0, 0, 1, 1, -1, -1};
        const vector<int8_t> offSetsY = {0, 0, 1, -1, 1, -1, -1, 1};

        // Words
        int maxWordSize = 0;
        int totalWords;
        int totalFound = 0;
        vector<string> words;
        set<string> wordsTrobades = set<string>();
        set<string> subset = set<string>();

        int totalPrefixs;
        vector<int> tSPrefix = vector<int>(20,0);
        vector<int8_t> prefixValues = vector<int8_t>(20, 0);
        vector<hashingTable> preHT = vector<hashingTable>(20);

        // Settings
        bool usePrefixPruning = true;
        bool printProgress = false;

    private:
        // Hash the string as Int so Double Hashing is possible
        unsigned int stringToInt(const string& s);

        // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int16_t x, int16_t y, vector<vector<bool>>& used, const int total);
};

#endif
