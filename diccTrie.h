#include "Trie.h"

#ifndef PROJECTE_SUPERSOPA_DICCTRIE_H
#define PROJECTE_SUPERSOPA_DICCTRIE_H

class diccTrie {
public:
    diccTrie();
    bool esFora(int i, int j, vector<vector<char>>& taulell);
    vector<string> cercaParaules(vector<string>& P, vector<vector<char>>& taulell);
    void backtracking(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules);
};

#endif //PROJECTE_SUPERSOPA_DICCTRIE_H
