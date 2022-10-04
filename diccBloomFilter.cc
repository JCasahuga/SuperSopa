#include "diccBloomFilter.h"
#include <iostream>
#include <iostream>
#include <vector>
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

// Assigns Words to the Map, if they don't fit, multiply the size by 2
void diccBloomFilter::buildFilter() {
    c = totalWords;
    filterSize = -(c*log(probability))/(pow(log(2), 2));
    k = -log2(probability);
    cout << "Filter size: " << filterSize << endl
         << "nº of hash functions: " << k << endl
         << "nº of words " << c << endl << endl;

    bloomFilter = vector<bool>(filterSize, false);
    
    hashFunctions.clear();
    for (int i = 0; i < k; ++i) {
        hashFunctions.push_back(randomNumber());
    }
    // for (auto x : hashFunctions) cout << x << " ";
    // cout << endl;

    for (string word : words) {
        for (int hash : hashFunctions) {
            bloomFilter[(stringToInt(word)*hash)%filterSize] = true;
        }
        if(word.size() > maxWordSize) maxWordSize = word.size();
    }

    // for (auto x : bloomFilter) cout << x;
    // cout << endl;
}

void diccBloomFilter::readInput() {
    readWords();
    readSoup();
}

void diccBloomFilter::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) 
        cin >> words[i];
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
    vector<vector<char>> used = soup;
    string s = "";
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            exploreSoupDeep(s, i, j, used, 1);
}


// Explores All Combinations of the Soup
void diccBloomFilter::exploreSoupDeep(string& s, int8_t x, int8_t y, vector<vector<char>>& used, const int total) {
    // Set
    used[x][y] = -1;
    s.push_back(soup[x][y]);

    const int v = stringToInt(s);

    //cout << maxWordSize << endl;
    //cout << "Checking for " << s << " with value " << v << endl;
    // Is in the Hash Table?
    if (search(v)) cout << "Found " << s << " Value " << v << endl;

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


// Searches Value in the Table
bool diccBloomFilter::search(int value) {
    bool found = true;
    for (int hash : hashFunctions) {
        found = found and bloomFilter[(value*hash)%filterSize];
        if (not found) break;
    }
    return found;
}
