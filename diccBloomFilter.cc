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

// Assigns Words to the Map, if they don't fit, multiply the size by 2
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
    // for (auto x : hashFunctions) cout << x << " ";
    // cout << endl;
    unordered_set<string> prefixs;
    for (string word : words) {
        int wordValue = stringToInt(word);
       // cerr << "word value for " << word << " is " << wordValue << endl;
        for (int hash : hashFunctions) {
            bloomFilter[abs(hash*wordValue)%filterSize] = true;
        }
        if (withPrefix) {
            addWordPrefix(word);
            string s;
            for (int i = 0; i < word.size(); ++i) {
               s.push_back(word[i]);
               prefixs.insert(s);
               //cerr << "word value for " << s << " is " << wordValue << endl;
            }
        }
        
        if(word.size() > maxWordSize) maxWordSize = word.size();
        if(word.size() < minWordSize) minWordSize = word.size();
    }



    //cerr << "prefix size: " << prefixs.size() << endl;
    if (withPrefix) for (string p : prefixs) addWordPrefix(p);

    //for (auto i : bloomFilterPrefix) cerr << i << " ";
    //cerr << endl;


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
    //cerr << "updating prefix " << s << endl;
    int wordValue = stringToInt(value);
    for (int hash : hashFunctionsPrefix) {
        //cerr << "pos: "<< abs(hash*wordValue)%prefixFilterSize << endl;
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
    //cerr << "encarbassot" << endl;
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
        //cerr << words[i] << endl;
    }
    buildFilter();
}

void diccBloomFilter::readSoup () {
    // Read Soup Size
    cin >> soupSize;
    //cerr << "soup size (just received): " << soupSize << endl;
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
   // cerr << "enrering" << endl;
    string s = "";
    //cout << "heeeere" << endl;
    used = vector<vector<bool>>(soupSize, vector<bool>(soupSize, false));
    //cerr << "soup size " << soupSize << endl;
    // for (auto i : used) {
    //     for(auto j : i) cerr << j;
    //     cout << endl;
    // }
    // cerr << "here" << endl;
    // cerr << "Result " << search(stringToInt("cis")) << endl;
    // cerr << "Result " << searchPrefix(stringToInt("cfis")) << endl;
    // cerr << "Result " << searchPrefix(stringToInt("fis")) << endl;
    // cerr << "Result " << searchPrefix(stringToInt("cfi")) << endl;
    // cerr << "Result " << searchPrefix(stringToInt("fi")) << endl;
    // cerr << "Result " << searchPrefix(stringToInt("f")) << endl;
    int n_paraules = 0;
    for (int i = 0; i < 1; ++i) {
        cerr << "In " << i << " from " << soupSize << endl;
        for (int j = 0; j < soupSize; ++j) {
            cerr << "In " << j << " from " << soupSize << endl;
            exploreSoupDeep(s, i, j, used, 1, n_paraules);
        }
    }
    cerr << "paraules = " << n_paraules << endl;

    
    cout << "We found " << foundWords.size() << " words." << endl;
    // for (string s : foundWords) {
    //     cout << s << endl;
    // }
    esSubconjunt();
}

// Explores All Combinations of the Soup
void diccBloomFilter::exploreSoupDeep(string& s, int x, int y, vector<vector<bool>>& used, const int total, int& n_paraules) {
    // Set
    used[x][y] = true;
    s.push_back(soup[x][y]);

    int v = stringToInt(s);

    //cerr << "checking " << s << endl;

    // Over Maximum Size Word
    if (s.size() > maxWordSize) {
        // Unset
        used[x][y] = false;
        s.pop_back();
        return;
    }

    if (withPrefix and (not searchPrefix(v)))
    {
        //cerr << "not any word starting with that for " << s << endl;
        used[x][y] = false;
        s.pop_back();
        return ;
    }

    // Is in the Hash Table?
    if (search(v)) {
        ++n_paraules;
        //foundWords.insert(s);
        //cerr << "Found " << s << " Value " << v << endl;
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
                exploreSoupDeep(s, x, y, used, total+1, n_paraules);
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