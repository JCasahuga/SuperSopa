#include "diccBloomFilter.h"
#include <iostream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

diccBloomFilter::diccBloomFilter(){}

diccBloomFilter::diccBloomFilter(const double& p){
    probability = p; 
}

int modulo(int base, int e, int mod) {
   int a = 1;
   int b = base;
   while (e > 0) {
      if (e % 2 == 1)
         a = (a * b) % mod;
         b = (b * b) % mod;
         e = e / 2;
   }
   return a % mod;
}

bool Fermat(int m, int iterations) {
   if (m == 1) {
      return false;
   }
   for (int i = 0; i < iterations; i++) {
      int x = rand() % (m - 1) + 1;
      if (modulo(x, m - 1, m) != 1) {
         return false;
      }
   }
   return true;
}

int randomNumber() {
    int r = 10000 + rand()%10000;
    while (!Fermat(r,100)) {
        r += rand()%1000;
    }
    return r;
}

// Hash the string as Int so Double Hashing is possible
unsigned int diccBloomFilter::stringToInt(string s) {
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

// Builds the Bloom filter */
void diccBloomFilter::buildFilter() {
    c = totalWords;
    filterSize = -(c*log(probability))/(pow(log(2), 2));
    k = -log2(probability);
    
    cout << "Filter size: " << filterSize << endl
         << "nº of hash functions: " << k << endl
         << "nº of words " << c << endl << endl;

    bloomFilter = vector<bool>(filterSize, false);
    prefixFilterSize = -(c*10*log(probability))/(pow(log(2), 2));
    bloomFilterPrefix = vector<bool>(prefixFilterSize, false);

    hashFunctions.clear();
    for (int i = 0; i < k; ++i) {
        hashFunctions.push_back(randomNumber());
    }
    if (withPrefix) {
        hashFunctionsPrefix.clear();
            for (int i = 0; i < k; ++i) {
            hashFunctionsPrefix.push_back(randomNumber());
        }
    }
    
    unordered_set<string> prefixs;
    for (string word : words) {
        int wordValue = stringToInt(word);

        for (int hash : hashFunctions) {
            bloomFilter[abs(hash*wordValue)%filterSize] = true;
        }
        if (withPrefix) {
            addWordPrefix(word);
            string s;
            for (int i = 0; i < word.size(); ++i) {
               s.push_back(word[i]);
               prefixs.insert(s);
            }
        }
        
        if(word.size() > maxWordSize) maxWordSize = word.size();
        if(word.size() < minWordSize) minWordSize = word.size();
    }

    //cerr << "prefix size: " << prefixs.size() << endl;
    if (withPrefix) for (string p : prefixs) addWordPrefix(p);
}

void diccBloomFilter::addWordPrefix(string value) {
    string s;
    int wordValue = stringToInt(value);
    for (int hash : hashFunctionsPrefix) {
        bloomFilterPrefix[abs(hash*wordValue)%prefixFilterSize] = true;
    }
}

bool diccBloomFilter::esSubconjunt() {
    if (includes(foundWords.begin(), foundWords.end(),
                 subsetDictionary.begin(), subsetDictionary.end())) {
        cout << "Les paraules del subconjunt es troben incloses a les paraules que ha trobat el filtre de Bloom" << endl;
        return true;
    }
    return false;
}

void diccBloomFilter::readInput() {
    readWords();
    subsetDictionary = readSubset();
    readSoup();
}


set<string> diccBloomFilter::readSubset() {
    int subsetWords;
    cin >> subsetWords;
    vector<string> subsetDictionary;
    subsetDictionary = vector<string>(subsetWords, "-1");
    for (int i = 0; i < subsetWords; ++i) {
        cin >> subsetDictionary[i];
    }
    set<string> P(subsetDictionary.begin(),subsetDictionary.end());
    return P;
}

void diccBloomFilter::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) {
        cin >> words[i];
    }
    buildFilter();
}

void diccBloomFilter::readSoup () {
    // Read Soup Size
    cin >> soupSize;
    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
}

// Sends a BFS dor each letter on the soup
void diccBloomFilter::exploreSoup() {
    vector<vector<bool>> used;
    string s = "";

    used = vector<vector<bool>>(soupSize, vector<bool>(soupSize, false));

    for (int i = 0; i < soupSize; ++i) {
        //cerr << "In i = " << i << " from " << soupSize << endl;
        for (int j = 0; j < soupSize; ++j) {
           // cerr << "In j = " << j << " from " << soupSize << endl;
            exploreSoupDeep(s, i, j, used, 1);
        }
    }

    
    cout << "The bloom filter found " << foundWords.size() << " words." << endl;
    esSubconjunt();
}

// Explores All Combinations of the Soup
void diccBloomFilter::exploreSoupDeep(string& s, int x, int y, vector<vector<bool>>& used, const int total) {
    // Set
    used[x][y] = true;
    s.push_back(soup[x][y]);

    int v = stringToInt(s);

    // Over Maximum Size Word
    if (s.size() > maxWordSize) {
        // Unset
        used[x][y] = false;
        s.pop_back();
        return;
    }

    if (withPrefix and (not searchPrefix(v)))
    {
        used[x][y] = false;
        s.pop_back();
        return ;
    }

    // Is in the Hash Table?
    if (search(v)) {
        foundWords.insert(s);
    }

    //Loops to All Directions
    for (int i = 0; i < 8; ++i) {
        x += offSetsX[i];
        y += offSetsY[i];
        if (min(x, y) >= 0 && max(x, y) < soupSize) {
            if (not used[x][y]) {
                used[x][y] = true;
                exploreSoupDeep(s, x, y, used, total+1);
                used[x][y] = false;
            }
        }
        x -= offSetsX[i];
        y -= offSetsY[i];
    }
    
    // Unset
    s.pop_back();
    used[x][y] = false;
}


// Searches Value in the Table
bool diccBloomFilter::search(int value) {
    bool found = true;
    for (int hash : hashFunctions) {
        found = found and bloomFilter[abs(value*hash)%filterSize];
    }
    return found;
}

// Searches Value in the Table
bool diccBloomFilter::searchPrefix(int value) {
    bool found = true;
    for (int hash : hashFunctionsPrefix) {
        found = found and bloomFilterPrefix[abs(value*hash)%prefixFilterSize];
    }
    return found;
}