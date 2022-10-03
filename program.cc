#include "diccDHashing.h"
#include <iostream>
using namespace std;

//Note: Standard input format
// nW seguit de nW paraules
// n seguit d'una sopa de nxn

int main() {
    cout << "[1] Vector ordenat" << endl <<
            "[2] Trie" << endl <<
            "[3] Filtre de Bloom" << endl <<
            "[4] Double Hashing" << endl <<
    "Select which dictionary you want to use: " << endl;
    int selection;
    cin >> selection;
    if (selection == 1) {

    }
    else if (selection == 2) {

    }
    else if (selection == 3) {

    }
    else if (selection == 4) {
        diccDHashing dicc(64768);
        // Read the innput
        dicc.readInput();
        // Explore Soup
        dicc.exploreSoup();
    }
}