#include "Trie.h"

Trie::Trie(vector<string> P) {
    arrel = new NodeTrie();
    for (auto i : P) {
        afegirParaula(i);
    }
}

void Trie::afegirParaula(string paraula) {
    NodeTrie* actual = arrel;
    for (auto c : paraula) {
        int i = c - 'a';
        if (actual->node[i] == nullptr) {
            actual->node[i] = new NodeTrie();
        }
        actual = actual->node[i];
    }
    actual->esFulla = true;
}

