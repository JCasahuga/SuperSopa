#include "diccDHashing.h"
#include "diccBloomFilter.h"
#include "diccTrie.cc"
#include "generator.cc"
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

int main(int argc, char* argv[]) {

    if (argc != 2) {
        info();
        return -1;
    }

    int select = atoi(argv[1]);

    if (select == 1) {
        cerr << "Encara no esta implentat el vector ordenat" << endl;
    }

    else if (select == 2) {
        cerr << "Encara no esta implentat la trie" << endl;
        trie::main(dictionary,soup);
    }

    else if (select == 3) {
        cerr << "Has seleccionat filtre de bloom" << endl;
        diccBloomFilter dicc(0.1); // Probabilitat de fals positiu desitjada
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
}