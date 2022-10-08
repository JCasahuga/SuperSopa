#include "diccTrie.h"
#include "Trie.h"
#include <vector>

//Constructora
diccTrie::diccTrie(){}

/* Mira si una determinada posició quan es fa el backtrack al taulell es troba fora */
bool diccTrie::esFora(int i, int j, vector<vector<char>>& taulell) {
    return (i < 0 or i >= taulell.size() or j < 0 or j >= taulell[0].size());
}

void diccTrie::backtracking(Trie arbre, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules)
{
    backtrackingDeep(arbre.getArrel(), i, j, paraula, taulell, paraules);
}

/* Fem un DFS sobre el taulell per cercar les paraules */
void diccTrie::backtrackingDeep(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules) {
    if (esFora(i,j,taulell) or taulell[i][j] == ' ') return;

    if(arrel->node[taulell[i][j]-'a'] != nullptr) {
        paraula += taulell[i][j];
        arrel = arrel->node[taulell[i][j]-'a'];

        if (arrel->esFulla) {
            paraules.push_back(paraula);
        }

        char c = taulell[i][j];
        taulell[i][j] = ' ';

        backtracking(arrel,i+1,j, paraula, taulell, paraules);
        backtracking(arrel,i-1,j, paraula, taulell, paraules);
        backtracking(arrel,i,j+1, paraula, taulell, paraules);
        backtracking(arrel,i,j-1, paraula, taulell, paraules);
        backtracking(arrel,i+1,j+1, paraula, taulell, paraules);
        backtracking(arrel,i+1,j-1, paraula, taulell, paraules);
        backtracking(arrel,i-1,j+1, paraula, taulell, paraules);
        backtracking(arrel,i-1,j-1, paraula, taulell, paraules);

        taulell[i][j] = c;
    }
}

/* La funció ens ajuda a cercar les paraules del D que es troben a la SuperSopa */
vector<string> diccTrie::cercaParaules(vector<string>& P, vector<vector<char>>& taulell) {

    vector<string> paraules;
    for (int i = 0; i < taulell.size(); ++i) {
        for (int j = 0; j < taulell[0].size(); ++j) {
            backtracking(arbre, i, j, "", taulell, paraules);
        }
    }
    return paraules;
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
