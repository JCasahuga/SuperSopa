#include "diccDHashing.h"
#include "diccBloomFilter.h"
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

    int selection = stoi(argv[1]);

    if (selection == 1) {
        cerr << "Encara no esta implentat el vector ordenat" << endl;
    }
    else if (selection == 2) {
        cerr << "Encara no esta implentat la trie" << endl;
    }
    else if (selection == 3) {
        diccBloomFilter dicc(0.05); // Probabilitat de fals positiu desitjada
        // Read the innput
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
    else if (selection == 4) {
        diccDHashing dicc(64768);
        // Read the innput
        dicc.readInput();
        cerr << "readed!" << endl;
        // Explore Soup
        dicc.exploreSoup();
    }
}