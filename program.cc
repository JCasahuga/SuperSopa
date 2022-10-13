#include "diccDHashing.h"
#include "diccBloomFilter.h"
//#include "generator.cc"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <chrono>
#include "diccTrie.cc"
#include <iostream>
using namespace std;

//Note: Standard input format
// nW seguit de nW paraules
// n seguit d'una sopa de nxn

void info() {
    cerr << "Please add one of the flags when running it to select the dictionary:" << endl;
    cerr << "[1] Vector ordenat" << endl <<
            "[2] Trie" << endl <<
            "[3] Filtre de Bloom" << endl <<
            "[4] Double Hashing" << endl;
}


vector<vector<char>> readSoupTrie () {
    // Read Soup Size
    int soupSize;
    cin >> soupSize;
    vector<vector<char>> soup(soupSize, vector<char>(soupSize));

    // Read Soup Values
    char c;
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
    return soup;
}

vector<string> readWordsTrie () {
    int totalWords;
    cin >> totalWords;
    vector<string> words;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) 
        cin >> words[i];
    return words;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        info();
        return -1;
    }

    int select = atoi(argv[1]);

    //auto inici = chrono::steady_clock::now();
    if (select == 1) {
        cerr << "Encara no esta implentat el vector ordenat" << endl;
    }

    else if (select == 2) {
        vector<string> dictionary = readWordsTrie();
        vector<vector<char>> soup = readSoupTrie();
        trie::main(dictionary,soup);
    }

    else if (select == 3) {
        cerr << "Has seleccionat filtre de bloom" << endl;
        diccBloomFilter dicc(0.00000001); // Probabilitat de fals positiu desitjada
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
    else if (select == 4) {
        cerr << "Has seleccionat double hashing" << endl;
        diccDHashing dicc;
        // Read the innput
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
   // auto fi = chrono::steady_clock::now();
    //cout << "Temps de creació i cerca paraules : " <<  chrono::duration_cast<chrono::nanoseconds>(fi-inici).count() << " nanosegons." << endl;
}
