//Generador definitiu
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//////////////////////////// TRIE ///////////////////////////////
/*----------------ED NODETRIE----------------*/

struct NodeTrie {
    vector<NodeTrie*> node; //fill
    bool esFulla; //paraula
    NodeTrie() {
        node = vector<NodeTrie*>(26, nullptr); //un node Trie té un fill(que és NodeTrie) per cada caràcter(prefix:a-z)
        esFulla = false; //esFulla=Paraula que pertany a la llista de paraules
    }
};

/*------------------ED TRIE------------------*/

class Trie {
private:
    NodeTrie* arrel; //cada Trie té un node arrel que li pengen 26 fills(en el pitjor dels casos)
public:
    NodeTrie* getArrel() {
        return arrel; //retornem l'arrel del trie
    };

    Trie(vector<string> P) { //Fem el Trie i li passem el subconjunt de paraules P que hi volem posar
        arrel = new NodeTrie(); //fem l'arrel principal que tindrà 26 caràcters inicialitzats a null
        for (auto i : P) { //per cada i afegim els seus caràcters al Trie i per tant afegim la paraula al Trie
            afegirParaula(i);
        }
    }
    void afegirParaula(string paraula) { //afegirem una paraula del subconjunt P al nostre Trie
        NodeTrie* actual = arrel; //punter actual a l'arrel
        for (auto c : paraula) {
            int i = c - 'a';
            if (actual->node[i] == nullptr) { //si el caràcter no existeix al Trie, l'afegirem,
                actual->node[i] = new NodeTrie();
            }
            actual = actual->node[i]; //si ja hi és movem el punter a la posició on es troba el caràcter
        }
        actual->esFulla = true; //l'ultim caràcter que hem afegit l'hem de marcar com a fulla i és una paraula que tenim a P/D
    }
};

/* Mira si una determinada posició quan es fa el backtrack al taulell es troba fora */
bool esFora(int i, int j, vector<vector<char>>& taulell) {
    return (i < 0 or i >= taulell.size() or j < 0 or j >= taulell[0].size());
}

/* Fem un DFS sobre el taulell per cercar les paraules */
//LI PASSEM A QUIN NODE ESTEM EN EL TRIE PERQUÈ SAPIGA CAP A ON SEGUIR I
// QUINS CARÀCTERS HEM VIST I LI PASSEM LA PARAULA PER ANAR CONSTRUINT-LA
void backtracking(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, set<string>& paraules) {
    if (esFora(i,j,taulell) or taulell[i][j] == ' ') return; //si anem fora de bounds o si tenim un caràcter que no és un fill d'un node a la trie

    if(arrel->node[taulell[i][j]-'a'] != nullptr) { //actualitzem el node i sabem que aquell node existeix i actualitzem la paraula
        paraula += taulell[i][j]; //per afegir el nou caracter que hem llegit
        arrel = arrel->node[taulell[i][j]-'a']; //ara partim del nou caracter on hem arribat

        if (arrel->esFulla) { //si arribem a un node que és fulla i per tant si hi hem arribat -> hi ha un camí del node arrel a la fulla,
            //inserim a les paraules resultants
            paraules.insert(paraula);
        }

        char c = taulell[i][j];
        taulell[i][j] = ' ';

        //mirem per totes les posicions possibles
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
    Trie t(P); //CREEEM EL TRIE AMB EL SUBCONJUNT P DE PARAULES
    NodeTrie* arrel = t.getArrel(); //OBTENIM EL NODE ARREL DEL TRIE
    set<string> paraules; //CONJUNT RESULTANT DE PARAULES QUE SÓN RESULTAT I PER TANT QUE ES TROBEN AL
    for (int i = 0; i < taulell.size(); ++i) {
        for (int j = 0; j < taulell[0].size(); ++j) {
            string paraula = ""; //farem un DFS per cada casella del taulell, li passem l'arrel del Trie i la paraula buida
            backtracking(arrel, i, j, paraula, taulell, paraules);
        }
    }
    return paraules;
}

//////////////////////////// MAIN //////////////////////////////

namespace trie {
    int main(vector<string>& D, vector<vector<char>>& soup) {
        set<string> paraulesSenseRepetir = cercaParaules(D, soup);

        //for (auto i: paraulesSenseRepetir) cout << i << endl;
        cout << paraulesSenseRepetir.size() << endl;
        return 0;
    }
}