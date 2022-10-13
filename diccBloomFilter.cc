#include "diccBloomFilter.h"
#include <iostream>
#include <iostream>
#include <unordered_set>
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
    prefixFilterSize = min(filterSize*totalWords, int(1e9));
    bloomFilterPrefix = vector<bool>(prefixFilterSize, false);
    
    hashFunctions.clear();
    for (int i = 0; i < k; ++i) {
        hashFunctions.push_back(randomNumber());
    }

    hashFunctionsPrefix.clear();
        for (int i = 0; i < k; ++i) {
        hashFunctionsPrefix.push_back(randomNumber());
    }
    // for (auto x : hashFunctions) cout << x << " ";
    // cout << endl;
    unordered_set<string> prefixs;
    for (string word : words) {
        int wordValue = stringToInt(word);
       // cerr << "word value for " << word << " is " << wordValue << endl;
        for (int hash : hashFunctions) {
            bloomFilter[abs(hash*wordValue)%filterSize] = true;
        }
        for (int hash : hashFunctionsPrefix) {
            bloomFilterPrefix[abs(hash*wordValue)%prefixFilterSize] = true;
        }
        string s;
        for (int i = 0; i < word.size(); ++i) {
            s.push_back(word[i]);
            prefixs.insert(s);
            //cerr << "word value for " << s << " is " << wordValue << endl;
        }
        if(word.size() > maxWordSize) maxWordSize = word.size();
        if(word.size() < minWordSize) minWordSize = word.size();
    }

    cerr << "prefix size: " << prefixs.size() << endl;
    for (string p : prefixs) addWordPrefix(p);


    //for (bool b : bloomFilterPrefix) cout << b;
    //cout << endl;
    // for (auto x : hashFunctions) cout << (stringToInt("word")*x)%filterSize << " ";
    // cout << endl;

    // for (auto x : bloomFilter) cout << x;
    // cout << endl;
}

void diccBloomFilter::addWordPrefix(string value) {
    //cerr << "here" << endl;
    string s;
    int wordValue = stringToInt(value);
    for (int hash : hashFunctionsPrefix) {
        bloomFilterPrefix[abs(hash*wordValue)%prefixFilterSize] = true;
    }
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
    vector<vector<bool>> used(soup.size(), vector<bool>(soup[0].size(), false));
    string s = "";
    //cerr << "here" << endl;
    cerr << "Result " << search(stringToInt("ninja")) << endl;
    cerr << "Result " << searchPrefix(stringToInt("ninja")) << endl;
    cerr << "Result " << searchPrefix(stringToInt("ninj")) << endl;
    cerr << "Result " << searchPrefix(stringToInt("nin")) << endl;
    cerr << "Result " << searchPrefix(stringToInt("ni")) << endl;
    cerr << "Result " << searchPrefix(stringToInt("n")) << endl;
    for (int i = 0; i < soupSize; ++i) {
        for (int j = 0; j < soupSize; ++j) {
            used[i][j] = true;
            exploreSoupDeep(s, i, j, used, 1);
            used[i][j] = false;
        }
    }

    
    cout << "We found " << foundWords.size() << " words." << endl;
    for (string s : foundWords) {
        cout << s << endl;
    }
}

// Explores All Combinations of the Soup
void diccBloomFilter::exploreSoupDeep(string& s, int x, int y, vector<vector<bool>>& used, const int total) {
    // Set
    s.push_back(soup[x][y]);

    int v = stringToInt(s);
    
    // cerr << "checking " << s << endl;
    // if (not searchPrefix(v)) 
    // {
    //     cerr << "not any word starting with that for " << s << endl;
    //     return ;
    // }

    // Is in the Hash Table?
    if (search(v)) {
        foundWords.insert(s);
        //cerr << "Found " << s << " Value " << v << endl;
    }

    // Over Maximum Size Word
    if (total >= maxWordSize) {
        // Unset
        used[x][y] = soup[x][y];
        s.pop_back();
        return;
    }

    // cout << "Inside explore for word!" << endl;
    // for (auto x : hashFunctions) cout << (stringToInt("word")*x)%filterSize << " ";
    //cout << endl;

    //Loops to All Directions
    for (int i = 0; i < 8; ++i) {
        x += offSetsX[i];
        y += offSetsY[i];
        //cerr << "Going to check " << x << " - " << y << endl;
        if (min(x, y) >= 0 && max(x, y) < soupSize) {
            if (not used[x][y]) {
                //cerr << "Exploring " << x << " - " << y << endl;
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
}


// Searches Value in the Table
bool diccBloomFilter::search(int value) {
    bool found = true;
    for (int hash : hashFunctions) {
        found = found and bloomFilter[abs(value*hash)%filterSize];
        //cerr << found << " found state ";
    }
    //cerr << endl;
    return found;
}

// Searches Value in the Table
bool diccBloomFilter::searchPrefix(int value) {
    bool found = true;
    for (int hash : hashFunctionsPrefix) {
        found = found and bloomFilterPrefix[abs(value*hash)%prefixFilterSize];
        //cerr << found << " found state ";
    }
    //cerr << endl;
    return found;
}