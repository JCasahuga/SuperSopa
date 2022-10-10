#include "Trie.h"
#include "NodeTrie.h"
#include <string>
#include <vector>

class diccTrie {
    public:

        diccTrie();

        bool esFora(int i, int j);

        vector<string> cercaParaules();

        void backtracking(Trie arbre, int i, int j, string paraula);

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
        Trie arbre;

        int totalWords;
        vector<vector<char>> soup;
        vector<string> words;

    void backtrackingDeep(NodeTrie *arrel, int i, int j, string paraula);
};
