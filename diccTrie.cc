#include "diccTrie.h"
#include "Trie.h"
#include "NodeTrie.h"
#include <vector>
#include <unordered_set>

//Constructora
diccTrie::diccTrie(){}

/* Mira si una determinada posició quan es fa el backtrack al taulell es troba fora */
bool diccTrie::esFora(int i, int j) {
    return (i < 0 or i >= soup.size() or j < 0 or j >= soup[0].size());
}

void diccTrie::backtracking(Trie arbre, int i, int j, string paraula)
{
    backtrackingDeep(reinterpret_cast<NodeTrie *>(arbre.getArrel()), i, j, paraula);
}

/* Fem un DFS sobre el taulell per cercar les paraules */
void diccTrie::backtrackingDeep(NodeTrie* arrel, int i, int j, string paraula) {
    if (esFora(i,j) or soup[i][j] == ' ') return;

    if(arrel->node[soup[i][j]-'a'] != nullptr) {
        paraula += soup[i][j];
        arrel = arrel->node[soup[i][j]-'a'];

        if (arrel->esFulla) {
            words.push_back(paraula);
        }

        char c = soup[i][j];
        soup[i][j] = ' ';

        backtrackingDeep(arrel, i+1, j, paraula);
        backtrackingDeep(arrel, i-1, j, paraula);
        backtrackingDeep(arrel, i, j+1, paraula);
        backtrackingDeep(arrel, i, j-1, paraula);
        backtrackingDeep(arrel, i+1, j+1, paraula);
        backtrackingDeep(arrel, i+1, j-1, paraula);
        backtrackingDeep(arrel, i-1, j+1, paraula);
        backtrackingDeep(arrel, i-1, j-1, paraula);

        soup[i][j] = c;
    }
}

/* La funció ens ajuda a cercar les paraules del D que es troben a la SuperSopa */
vector<string> diccTrie::cercaParaules() {
    for (int i = 0; i < soup.size(); ++i) {
        for (int j = 0; j < soup[0].size(); ++j) {
            backtracking(arbre, i, j, "");
        }
    }
    unordered_set<string> s;
    for (auto i : words) s.insert(i);
    words = vector<string>(s.begin(),s.end());

    return words;
}


void diccTrie::readInput() {
    readWords();
    readSoup();
}

void diccTrie::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) 
        cin >> words[i];
    //assignWords();
}

void diccTrie::readSoup () {
    // Read Soup Size
    int soupSize;
    cin >> soupSize;

    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
}
