#include "diccDHashing.h"
#include "diccBloomFilter.h"
#include "diccSortedVector.h"
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
// nS seguit de nS selectedWords (s'utilitzaran per comprovar que el programa les troba com a mínim)
// n seguit d'una sopa de nxn

void info() {
    cerr << "Please add one of the flags when running it to select the dictionary:" << endl;
    cerr << "[1] Vector ordenat" << endl <<
            "[2] Trie" << endl <<
            "[3] Filtre de Bloom" << endl <<
            "[4] Double Hashing" << endl;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        info();
        return -1;
    }

    int select = atoi(argv[1]);

    auto inici = chrono::steady_clock::now();
    if (select == 1) {
        diccSortedVector dicc;
        //Read the input
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
    else if (select == 2) {
        //Read the input
        vector<string> dictionary = trie::readWordsTrie();
        set<string> subset = trie::readSubset();
        vector<vector<char>> soup = trie::readSoupTrie();
        // Explore Soup
        trie::main(dictionary,soup,subset);
    }
    else if (select == 3) {
        diccBloomFilter dicc(0.01); // Probabilitat de fals positiu desitjada
        //Read the input
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
    else if (select == 4) {
        diccDHashing dicc;
        // Read the input
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
        // Checks if Subset has been Found
        dicc.checkSubset();
    }

    auto fi = chrono::steady_clock::now();
    cout << "Temps de creació i cerca paraules : " <<  chrono::duration_cast<chrono::milliseconds>(fi-inici).count() << " miliseconds." << endl;
}
