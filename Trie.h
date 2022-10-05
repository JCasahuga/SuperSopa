#include "NodeTrie.h"

#ifndef PROJECTE_SUPERSOPA_TRIE_H
#define PROJECTE_SUPERSOPA_TRIE_H

class Trie {
private:
    NodeTrie* arrel;
public:
    Trie();
    NodeTrie* getArrel();
    Trie(vector<string> P);
    void afegirParaula(string paraula);
};

#endif //PROJECTE_SUPERSOPA_TRIE_H
