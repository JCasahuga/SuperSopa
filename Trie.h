#include "NodeTrie.h"

#ifndef PROJECTE_SUPERSOPA_TRIE_H
#define PROJECTE_SUPERSOPA_TRIE_H

class Trie {
    public:
        Trie(vector<string> P);

        NodeTrie* getArrel();

        void afegirParaula(string paraula);
        
    private:
        NodeTrie* arrel;
};

#endif //PROJECTE_SUPERSOPA_TRIE_H
