#include <string>
#include <vector>
using namespace std;

#ifndef _DICCBLOOMFILTER_HH_
#define _DICCBLOOMFILTER_HH_

class diccBloomFilter
{
    public:
        //Constructores
        diccBloomFilter();

        diccBloomFilter(const int& probability);

        // Sends a BFS dor each letter on the soup
        void exploreSoup();

        void readInput();


private:

        // Check if value is Prime
        bool isPrime(const int n);

        // Hash the string as Int so Double Hashing is possible
        unsigned int stringToInt(string s);

       // Explores All Combinations of the Soup
        void exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total);

        // Assigns Words to the Map, if they don't fit, multiply the size by 2
        void buildFilter();

        void readWords ();

        void readSoup ();

        bool search(int value);

        // Parameters
        int filterSize;         //nº of elements in the filter
        int k;                  //nº of hash funcctions to apply to any element
        int c;                  //nº of elements stored in the bloom filter
        int p = 0.05;           //probablity of false positive

        vector<bool> bloomFilter;
        vector<int> hashFunctions;

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
