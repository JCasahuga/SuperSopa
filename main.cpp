#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

/* Aquest enum donté totes les possibles direccions a les quals podem tenir una lletra d'una paraula */
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
uint N = 10; /* assumirem inicialment que és 10 */

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
void llegirParaules(string& path, vector<string>& P) {
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

        vector<string> seleccioRandom(nombreParaules);

        /* Ens selecciona una mostra aleatòria de paraules en funció del nombre aleatòri que surt */
        sample(paraules.begin(), paraules.end(), back_inserter(seleccioRandom),
               nombreParaules,mt19937{random_device{}()});

        /* Ens permet esborrar els elements buits que conté el vector seleccioRandom */
        auto esBuit = [](const string &s) {
            return s.find_first_not_of(" \t") == string::npos;
        };

        seleccioRandom.erase(remove_if(seleccioRandom.begin(), seleccioRandom.end(),
                                            esBuit), seleccioRandom.end());
        P = seleccioRandom;
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
void calcularSubconjuntP(string& fitxer, vector<string>& P) {
    llegirParaules(fitxer, P);
    canviarMidaTaulell(P);
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
            // 'x' ens representa el caràcter nul
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
posicioT mourePosicio(posicioT& p, direccions& d, vector<vector<char>>& taulell) {
    int i = p.i;
    int j = p.j;

    posicioT novaPosicio = p;
    direccions direccioOrigen = d;

    repetim:
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
        direccioOrigen = direccions(rand()%8);
        goto repetim;
    }
    if (!esLliure(novaPosicio,taulell)) {
        novaPosicio = p;
        direccioOrigen = direccions(rand()%8);
        goto repetim;
    }
    return novaPosicio;
}

//Col·loquem una paraula en una posició random però vàlida i seguint una direcció random
void afegirParaula(const char *word, vector<vector<char>>& taulell) {
    posicioT inici;
    direccions d;

    inici.i = rand() % N;
    inici.j = rand() % N;
    d = direccions(rand() % 8);
    while (!esLliure(inici,taulell)) {
        inici.i = rand() % N;
        inici.j = rand() % N;
    }
    assert(esDins(inici) && esLliure(inici,taulell));

    int i = 0;
    while (i < (int) strlen(word)) {
        if (esDins(inici) && esLliure(inici,taulell)) {
            taulell[inici.i][inici.j] = word[i];
            inici = mourePosicio(inici, d, taulell);
        }
        ++i;
        /*if (potInserir(word,inici,d,taulell)) {
            taulell[inici.i][inici.j] = word[i];
        }*/
    }
    imprimirTaulell(taulell);
}

void afegirParaulaSubconjuntP(vector<string>& P, vector<vector<char>>& taulell) {
    for (int i = 0; i < P.size(); ++i) {
        string paraula = P[i];
        cout << P[i] << endl;
        afegirParaula(paraula.c_str(),taulell);
    }
}

int main() {
    cout << "Benvingut a SuperSopa!" << endl;
    cout << "Escriu el nom del fitxer(sense l'extensió (.txt)) del qual \n"
            "t'agradaria llegir les paraules que vols cercar a la Super Sopa! \n"
            "Exemple: Si el fitxer es diu paraules.txt, escriu: paraules"
            << endl;

    string fitxer;
    cin >> fitxer;

    vector<string> P;
    calcularSubconjuntP(fitxer,P);

    cout << "---------------\n" << "SUPER SOPA!" << endl;

    vector<vector<char>> taulell(N,vector<char>(N));
    generarTaulellBuit(taulell);

    afegirParaulaSubconjuntP(P, taulell);

    emplenarPosicions(taulell);
    imprimirTaulell(taulell);
}