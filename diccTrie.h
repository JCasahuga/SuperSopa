#include "Trie.h"
#include "NodeTrie.h"
#include <string>
#include <vector>

#ifndef PROJECTE_SUPERSOPA_DICCTRIE_H
#define PROJECTE_SUPERSOPA_DICCTRIE_H

class diccTrie {
    public:

        diccTrie();

        bool esFora(int i, int j, vector<vector<char>>& taulell);

        vector<string> cercaParaules(vector<string>& P, vector<vector<char>>& taulell);

        void backtracking(Trie arbre, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules);

        void backtrackingDeep(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules);    
        
        void readInput();

        void readWords ();

        void readSoup ();

        struct NodeTrie {
        vector<NodeTrie*> node;
        bool esFulla;

        NodeTrie() {
            node = vector<NodeTrie*>(26, nullptr);
            esFulla = false;
        }
        };
        
        // // TRIE
        // class Trie {
        // private:
        //     NodeTrie* arrel;
        // public:
        //     NodeTrie* getArrel() {
        //         return arrel;
        //     };
        //     Trie(vector<string> P) {
        //         arrel = new NodeTrie();
        //         for (auto i : P) {
        //             afegirParaula(i);
        //         }
        //     }
        //     void afegirParaula(string paraula) {
        //         NodeTrie* actual = arrel;
        //         for (auto c : paraula) {
        //             int i = c - 'a';
        //             if (actual->node[i] == nullptr) {
        //                 actual->node[i] = new NodeTrie();
        //             }
        //             actual = actual->node[i];
        //         }
        //         actual->esFulla = true;
        //     }
        // };


        Trie arbre;

        int totalWords;
        vector<vector<char>> soup;
        vector<string> words;

};

#endif //PROJECTE_SUPERSOPA_DICCTRIE_H
