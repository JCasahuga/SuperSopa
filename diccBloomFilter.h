#include <string>
#include <vector>
#include <set>
using namespace std;

#ifndef _DICCBLOOMFILTER_HH_
#define _DICCBLOOMFILTER_HH_

class diccBloomFilter
{
    public:
        //Constructores
        diccBloomFilter();

        diccBloomFilter(const double& p);

        // Sends a BFS dor each letter on the soup
        void exploreSoup();

        void readInput();


private:

        // Check if value is Prime
        bool isPrime(const int n);

        // Hash the string as Int so Double Hashing is possible
        unsigned int stringToInt(string s);

       // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int x, int y, vector<vector<bool>>& used, const int total);

        // Assigns Words to the Map, if they don't fit, multiply the size by 2
        void buildFilter();

        void readWords ();

        set<string> readSubset();

        bool esSubconjunt();

        void readSoup ();

        bool search(int value);

        bool searchPrefix(int value);

        void addWordPrefix(string value);

        // Parameters
        int filterSize;                      //nº of elements in the filter
        int k;                               //nº of hash funcctions to apply to any element
        int c;                               //nº of elements stored in the bloom filter
        double probability = 0.05;           //probablity of false positive

        int prefixFilterSize;

        vector<bool> bloomFilter;
        vector<bool> bloomFilterPrefix;
        vector<int> hashFunctions;
        vector<int> hashFunctionsPrefix;

        // Soup
        int soupSize;
        vector<vector<char>> soup;

        // Possible Directions to Move in the Soup
        const vector<int> offSetsX = {1, -1, 0, 0, 1, 1, -1, -1};
        const vector<int> offSetsY = {0, 0, 1, -1, 1, -1, -1, 1};

        // Words
        int maxWordSize = 0;
        int minWordSize = 999;
        int totalWords;
        vector<string> words;
        set<string> foundWords;
        set<string> subsetDictionary;

        bool withPrefix = false;
};

#endif
