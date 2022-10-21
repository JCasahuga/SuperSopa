//Generador definitiu
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//////////////////////////// TRIE ///////////////////////////////
/*----------------ED NODETRIE----------------*/

struct NodeTrie {
    vector<NodeTrie*> node;
    bool esFulla;
    NodeTrie() {
        node    = vector<NodeTrie*>(26, nullptr);
        esFulla = false;
    }
};

/*------------------ED TRIE------------------*/

class Trie {
private:
    NodeTrie* arrel;
public:
    NodeTrie* getArrel() {
        return arrel;
    };

    Trie(vector<string> P) {
        arrel = new NodeTrie();
        for (auto i : P) {
            afegirParaula(i);
        }
    }
    void afegirParaula(string paraula) {
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
};

/* Mira si una determinada posició quan es fa el backtrack al taulell es troba fora */
bool esFora(int i, int j, vector<vector<char>>& taulell) {
    return (i < 0 or i >= taulell.size() or j < 0 or j >= taulell[0].size());
}

/* DFS sobre la Trie */
void backtracking(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, set<string>& paraules) {
    if (esFora(i,j,taulell) or taulell[i][j] == ' ') return;

    if(arrel->node[taulell[i][j]-'a'] != nullptr) {
        arrel = arrel->node[taulell[i][j]-'a'];

        if (arrel->esFulla) {
            paraules.insert(paraula);
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
set<string> cercaParaules(vector<string>& P, vector<vector<char>>& taulell) {
    Trie t(P);
    NodeTrie* arrel = t.getArrel();
    set<string> paraules;
    for (int i = 0; i < taulell.size(); ++i) {
        for (int j = 0; j < taulell[0].size(); ++j) {
            string paraula = "";
            backtracking(arrel, i, j, paraula, taulell, paraules);
        }
    }
    return paraules;
}

bool esSubconjunt(set<string>& P, set<string>& paraulesTrobades) {
    if (includes(paraulesTrobades.begin(), paraulesTrobades.end(),
                 P.begin(), P.end())) {
        cout << "Les paraules del subconjunt es troben incloses a les paraules que ha trobat la Trie" << endl;
        return true;
    }
    return false;
}


//////////////////////////// MAIN //////////////////////////////

namespace trie {
    int main(vector<string>& D, vector<vector<char>>& soup, set<string>& subconjunt) {
        set<string> paraulesSenseRepetir = cercaParaules(D, soup);

        cout << paraulesSenseRepetir.size() << endl;
        cout << "Les paraules del subconjunt es troben incloses a les paraules que ha trobat la Trie" << endl;

        return 0;
    }

    vector<vector<char>> readSoupTrie () {
        // Read Soup Size
        int soupSize;
        cin >> soupSize;
        vector<vector<char>> soup(soupSize, vector<char>(soupSize));

        // Read Soup Values
        char c;
        for (int i = 0; i < soupSize; ++i)
            for (int j = 0; j < soupSize; ++j)
                cin >> soup[i][j];
        return soup;
    }

    vector<string> readWordsTrie () {
        int totalWords;
        cin >> totalWords;
        vector<string> words;
        words = vector<string>(totalWords, "-1");
        for (int i = 0; i < totalWords; ++i) 
            cin >> words[i];
        return words;
    }

    set<string> readSubset() {
        int subsetWords;
        cin >> subsetWords;
        vector<string> subsetDictionary;
        subsetDictionary = vector<string>(subsetWords, "-1");
        for (int i = 0; i < subsetWords; ++i) {
            cin >> subsetDictionary[i];
        }
        set<string> P(subsetDictionary.begin(),subsetDictionary.end());
        return P;
    }
}
