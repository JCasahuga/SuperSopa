#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <random>
#include <vector>
#include <unordered_set>

using namespace std;

/* Aquest enum conté totes  les possibles direccions a les quals podem tenir una lletra d'una paraula */
enum direccions {
    ESQUERRA,
    DRETA,
    AVALL,
    AMUNT,
    AVALL_ESQUERRA,
    AVALL_DRETA,
    AMUNT_ESQUERRA,
    AMUNT_DRETA,
};

/* Llargada màxima de totes les paraules que conté el fitxer que volem llegir. La màxima llargada
 * ens determinarà la mida del taulell n x n, ja que en el pitjor dels casos la paraula estaria disposada
 * en diagonal al taulell
 * I.e com a mínim la mida del tauler ha de poder encabir la paraula més gran del subconjunt P ⊆ D
 */

uint N = 4; /* assumirem inicialment que és 10 */
uint cont = N*N;

/* El nombre random calculat que ens permetrà escollir el nombre d'elements del subconjunt
 * P de paraules random del .txt */
int randomNumber(double linies) {
    random_device rd;
    mt19937 mt(rd());
    //com a mínim el nostre conjunt P inclourà una paraula del diccionari D que proporcionem
    uniform_real_distribution<double> dist(1.0, linies);
    return dist(mt);
}

/* Funció que ens ajuda a llegir el subconjunt P de paraules del fitxer que se'ns proporciona */
void llegirParaules(string& path, vector<string>& P, vector<string>& D) {
    ifstream fitxer("../"+path+".txt");

    vector<string> paraules;
    if (fitxer.is_open()) {
        string paraula;
        while (getline(fitxer, paraula)) {
            paraules.push_back(paraula);
            cout << paraula << endl;
        };
        fitxer.close();

        size_t nombreParaules = randomNumber(paraules.size());

        //vector<string> seleccioRandom(nombreParaules);

        /* Ens selecciona una mostra aleatòria de paraules en funció del nombre aleatòri que surt */
        //sample(paraules.begin(), paraules.end(), back_inserter(seleccioRandom),
        //       nombreParaules,mt19937{random_device{}()});

        /* Ens permet esborrar els elements buits que conté el vector seleccioRandom */
        auto esBuit = [](const string &s) {
            return s.find_first_not_of(" \t") == string::npos;
        };

        //seleccioRandom.erase(remove_if(seleccioRandom.begin(), seleccioRandom.end(),
         //                              esBuit), seleccioRandom.end());

        /* Guardem a P el subconjunt aleatòri de paraules */
        P = paraules;
        /* Guardem a D totes les paraules llegides a l'entrada */
        D = paraules;
    }
}

/* Si calculem la mida del taulell en funció de la paraula de màxima llargada de la llista D */
void canviarMidaTaulell(vector<string>& P) {
    for (auto i : P) {
        int suma = 0;
        for (auto j : i) {
            ++suma;
        }
        if (suma > N) N = suma;
    }
}

//Calculem el subconjunt P de paraules de D que plantarem a la Sopa i canviem la mida de la Sopa si és necessari
void calcularSubconjuntP(string& fitxer, vector<string>& P, vector<string>& D) {
    llegirParaules(fitxer, P, D);
    cout << "---------------\n" << "Subconjunt P: " << endl;
    for (auto i : P) cout << i << endl;
}

//Generem un caràcter random
char generarCaracterRandom() {
    return 'a' + rand()%26;
}

//Generem el taulell de mida n x n
void generarTaulellBuit(vector<vector<char>>& taulell) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // '-' ens representa el caràcter nul
            taulell[i][j] = '-';
        }
    }
}

//Emplenem les posicions buides amb un caràcter random
void emplenarPosicions(vector<vector<char>>& taulell) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // '-' ens representa el caràcter nul
            if (taulell[i][j] == '-') {
                taulell[i][j] = generarCaracterRandom();
            }
        }
    }
}

//Imprimim el taulell de mida n x n
void imprimirTaulell(vector<vector<char>>& taulell) {
    for (const auto& i : taulell) {
        for (auto j: i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

//L'struct posició representa un posició del taulell on hi ha hi guardem una lletra
struct posicioT {
    int i, j;
};

//Comprovem si donada una posició p and coordenades i "i" j aquesta es troba al taulell
bool esDins(posicioT& p) {
    return (p.i >= 0 and p.i < N and p.j >= 0 and p.j < N);
}

//Comprovem si donada una posició p del taulell aquesta es troba lliure i per tant hi podem plantar una paraula
bool esLliure(posicioT& p, vector<vector<char>>& taulell) {
    return (taulell[p.i][p.j] == '-');
}

//Ens movem una posició en el taulell per col·locar el següent caràcter.
posicioT mourePosicio(posicioT& p, direccions& d, vector<vector<char>>& taulell, bool& invalid, char c) {
    int i = p.i;
    int j = p.j;

    vector<bool> direccioProvada(8,false);

    posicioT novaPosicio = p;
    direccions direccioOrigen = d;

    repetim:
    int k = 0;
    bool totsProvats = false;
    while (k < 8) {
        if (!direccioProvada[k]) {
            break;
        }
        ++k;
    }
    if (k == 8) {
        invalid = true;
        return novaPosicio;
    }
    switch(direccioOrigen) {
        case ESQUERRA:
            novaPosicio.i = i-1;
            novaPosicio.j = j;
            break;
        case DRETA:
            novaPosicio.i = i+1;
            novaPosicio.j = j;
            break;
        case AVALL:
            novaPosicio.i = i;
            novaPosicio.j = j-1;
            break;
        case AMUNT:
            novaPosicio.i = i;
            novaPosicio.j = j+1;
            break;
        case AVALL_ESQUERRA:
            novaPosicio.i = i-1;
            novaPosicio.j = j-1;
            break;
        case AVALL_DRETA:
            novaPosicio.i = i-1;
            novaPosicio.j = j+1;
            break;
        case AMUNT_ESQUERRA:
            novaPosicio.i = i+1;
            novaPosicio.j = j-1;
            break;
        case AMUNT_DRETA:
            novaPosicio.i = i+1;
            novaPosicio.j = j+1;
            break;
        default:
            novaPosicio.i = i;
            novaPosicio.j = j;
            break;
    }
    if (!esDins(novaPosicio)) {
        novaPosicio = p;
        direccioProvada[direccioOrigen] = true;
        direccioOrigen = direccions(rand()%8);
        goto repetim;
    }
    if (!esLliure(novaPosicio,taulell) or taulell[novaPosicio.i][novaPosicio.j] == c) {
        novaPosicio = p;
        direccioProvada[direccioOrigen] = true;
        direccioOrigen = direccions(rand()%8);
        goto repetim;
    }
    return novaPosicio;
}

//Col·loquem una paraula en una posició random però vàlida i seguint una direcció random
void afegirParaula(const char *word, vector<vector<char>>& taulell) {
    int cinvalid = -1;
    posicioT inici;
    direccions d;

    inici.i = rand() % N;
    inici.j = rand() % N;
    d = direccions(rand() % 8);

    vector<vector<bool>> visitat(taulell.size(), vector<bool>(taulell.size(),false));

    repetim2:
    ++cinvalid;
    if (cinvalid >= cont) return;

    for (int i = 0; i < taulell.size(); ++i) {
        for (int j = 0; j < taulell[0].size(); ++j) {
            if (visitat[i][j]) {
                taulell[i][j] = '-';
                visitat[i][j] = false;
            }
        }
    }
    while ((!esLliure(inici,taulell) or word[0]) && !visitat[inici.i][inici.j] && !esDins(inici)) {
        inici.i = rand() % N;
        inici.j = rand() % N;
    }
    visitat[inici.i][inici.j] = true;

    int i = 0;
    while (i < (int) strlen(word)) {
        taulell[inici.i][inici.j] = word[i];
        --cont;
        bool invalid = false;
        inici = mourePosicio(inici, d, taulell, invalid, word[i+1]);
        if (invalid) {
            visitat[inici.i][inici.j] = true;
            goto repetim2;
        }
        ++i;
    }
}

void afegirParaulaSubconjuntP(vector<string>& P, vector<vector<char>>& taulell) {
    for (int i = 0; i < P.size(); ++i) {
        string paraula = P[i];
        cout << P[i] << endl;
        if (cont >= paraula.length()) {
            afegirParaula(paraula.c_str(),taulell);
        }
    }
}

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
        for (auto i : P) { //per cada paraula afegim els seus caràcters al Trie i per tant afegim la paraula al Trie
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
void backtracking(NodeTrie* arrel, int i, int j, string paraula, vector<vector<char>>& taulell, vector<string>& paraules) {
    if (esFora(i,j,taulell) or taulell[i][j] == ' ') return; //si anem fora de bounds o si tenim un caràcter que no és un fill d'un node a la trie

    if(arrel->node[taulell[i][j]-'a'] != nullptr) { //actualitzem el node i sabem que aquell node existeix i actualitzem la paraula
        paraula += taulell[i][j]; //per afegir el nou caracter que hem llegit
        arrel = arrel->node[taulell[i][j]-'a']; //ara partim del nou caracter on hem arribat

        if (arrel->esFulla) { //si arribem a un node que és fulla i per tant si hi hem arribat -> hi ha un camí del node arrel a la fulla,
            //inserim a les paraules resultants
            paraules.push_back(paraula);
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
vector<string> cercaParaules(vector<string>& P, vector<vector<char>>& taulell) {
    Trie t(P); //CREEEM EL TRIE AMB EL SUBCONJUNT P DE PARAULES
    NodeTrie* arrel = t.getArrel(); //OBTENIM EL NODE ARREL DEL TRIE

    vector<string> paraules; //CONJUNT RESULTANT DE PARAULES QUE SÓN RESULTAT I PER TANT QUE ES TROBEN AL
    for (int i = 0; i < taulell.size(); ++i) {
        for (int j = 0; j < taulell[0].size(); ++j) {
            string paraula = ""; //farem un DFS per cada casella del taulell, li passem l'arrel del Trie i la paraula buida
            backtracking(arrel, i, j, paraula, taulell, paraules);
        }
    }
    return paraules;
}

int main() {
    cout << "Benvingut a SuperSopa!" << endl;
    cout << "Escriu el nom del fitxer(sense l'extensió (.txt)) del qual \n"
            "t'agradaria llegir les paraules que vols cercar a la Super Sopa! \n"
            "Exemple: Si el fitxer es diu paraules.txt, escriu: paraules"
         << endl;

    string fitxer;
    cin >> fitxer;

    vector<string> P, D;
    calcularSubconjuntP(fitxer, P, D);
    //canviarMidaTaulell(P);

    cout << "---------------\n" << "SUPER SOPA!" << endl;
    vector<vector<char>> taulell(N, vector<char>(N));
    generarTaulellBuit(taulell);

    afegirParaulaSubconjuntP(P, taulell);

    emplenarPosicions(taulell);
    imprimirTaulell(taulell);

    //tenim duplicats ja que troba una mateixa paraula diverses vegades
    //potser seria millor tenir un set per evitar duplicats
    vector<string> paraulesTrobades = cercaParaules(D, taulell);

    //el convertim en un unordered set per evitar els duplicats
    unordered_set<string> s;
    for (auto i: paraulesTrobades) s.insert(i);

    //ens troba més paraules que les que plantem i que es troben a D
    paraulesTrobades.assign(s.begin(), s.end());
    sort(paraulesTrobades.begin(), paraulesTrobades.end());

    for (auto i: paraulesTrobades) cout << i << endl;
    cout << paraulesTrobades.size() << endl;
}