//Generador definitiu
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef vector<char> Files;
typedef vector<Files> Sopa;

bool DEBUG = false;
vector<string> dictionary;
set<string> selectedWords;
Sopa soup;
int N = 20;

// x    y              // ESQUERRA   DRETA    AMUNT    AVALL   ESQ-AMU  ESQ-AVALL  DRE-AMU   DRE-AVALL
vector<pair<int, int>> directions = {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}, {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

///////////////////////// FUNCIONS AUXILIARS //////////////////////////

void selectWordSet(int numberOfWords) {
    if (numberOfWords >= dictionary.size()) {
        if (DEBUG) cerr << "There are not enough words in the dictionary (" << numberOfWords << " - desired, " << dictionary.size() << " - size)" << endl;
        if (DEBUG) cerr << "Iserting all of them directly to the selection set" << endl;
        for (string word : dictionary) selectedWords.insert(word);
        return;
    }

    int selection = rand()%dictionary.size();
    int reduceRepeatedWord = rand()%dictionary.size();

    while (selectedWords.size() < numberOfWords) {

        if(not selectedWords.insert(dictionary[selection]).second) {
            if (DEBUG) cerr << "Didnt insert" << endl;
            if (reduceRepeatedWord < 1) reduceRepeatedWord = rand()%10;
        }
        else reduceRepeatedWord = rand()%dictionary.size();

        selection += rand()%reduceRepeatedWord;
        selection %= dictionary.size();
        if (DEBUG) cerr << "Inserting " << selection << " " << dictionary[selection] << endl;
    }
}

void printSoup() {
    for (int i = 0; i < soup.size(); ++i) {
        for (int j = 0; j < soup[i].size(); ++j) cout << soup[i][j];
        cout << endl;
    }
}

void printDictionary() {
    cout << dictionary.size() << endl;
    for (string word : dictionary) cout << word << endl;
}

void printSelectedWords() {
    cout << selectedWords.size() << endl;
    for (string word : selectedWords) cout << word << endl;
}

vector<pair<int, int>> getRandomDirections() {
    vector<pair<int, int>> copyOfDirections = directions;
    random_shuffle(copyOfDirections.begin(), copyOfDirections.end());
    return copyOfDirections;
}

bool isInside(int i, int j) {
    return i >= 0 and i < N and j < N and j >= 0;
}

bool isInside(pair<int, int> pos) {
    return isInside(pos.first, pos.second);
}

////////////////////// CREACIÓ DE LA SOPA ///////////////////////

bool placeToSoup(string word, int currentLetter, int i, int j, vector<pair<int, int>>& traceback, vector<vector<bool>>& visitat) { // falta implentar un visitat x q no es colapsi amb si mateixa
    if (word.size() == currentLetter) {
        if (DEBUG) cerr << "The word " << word << " was placed succesfuly" << endl;
        for (int k = 0; k < currentLetter; ++k) {
            soup[traceback[k].first][traceback[k].second] = word[k];
        }
        if (DEBUG) printSoup();
        return true;
    }

    bool foundSpot = false;

    if (soup[i][j] == '.' or soup[i][j] == word[currentLetter]) {

        for (pair<int, int> dir : getRandomDirections()) {
            pair<int, int> next_pos = make_pair(i+dir.first, j+dir.second);

            if (isInside(next_pos) and not visitat[next_pos.first][next_pos.second]) {
                traceback.push_back(next_pos);
                visitat[next_pos.first][next_pos.second] = true;

                foundSpot = foundSpot or placeToSoup(word, currentLetter+1, i+dir.first, j+dir.second, traceback, visitat);

                visitat[next_pos.first][next_pos.second] = false;
                traceback.pop_back();
            }
            if (foundSpot) break;
        }
    }
    return foundSpot;
}

bool addWordToSoup(string word)
{
    vector<pair<int, int>> traceback;
    vector<vector<bool>> visitat(N, vector<bool>(N, false));
    vector<pair<int, int>> positions;

    for (int i = 0; i < soup.size(); ++i) {
        for (int j = 0; j < soup[i].size(); ++j) positions.push_back(make_pair(i, j));
    }
    random_shuffle(positions.begin(), positions.end());

    int i, j;
    for (pair<int, int> pos : positions)
    {
        i = pos.first, j = pos.second;
        if (DEBUG) cerr << "Starting search for " << word << " on " << i << " " << j << endl;
        traceback.push_back(make_pair(i, j));
        visitat[i][j] = true;

        if(placeToSoup(word, 0, i, j, traceback, visitat)) return true;

        visitat[i][j] = false;
        traceback.pop_back();
    }
    return false;
}

void fillSoupEmptySpaces() {
    for (int i = 0; i < soup.size(); ++i) {
        for (int j = 0; j < soup[i].size(); ++j) {
            if (soup[i][j] == '.') {
                soup[i][j] = rand() % 26 + 'a';
            }
        }
    }
}
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

int main()
{
    srand(time(NULL));

    string word;
    while (cin >> word) dictionary.push_back(word);

    selectWordSet(20);        // Result is saved in selectedWords var
    N = 20;                   // Deafult value = 20
    DEBUG = false;            // DEBUG mode

    //printSelectedWords();

    soup = Sopa(N, Files(N, '.'));

    int placedWords = 0;
    for (auto word : selectedWords) if(addWordToSoup(word)) ++placedWords;
    if (DEBUG) cerr << "The placed words are " << placedWords << " out of " << selectedWords.size() << endl;
    fillSoupEmptySpaces();

    // cout << dictionary.size() << endl;
    //printDictionary();

    printSelectedWords();
    cout << "------" << endl;

    set<string> paraulesSenseRepetir = cercaParaules(dictionary, soup);

    for (auto i : paraulesSenseRepetir) cout << i << endl;
    cout << paraulesSenseRepetir.size() << endl;

    cout << N << endl;
    printSoup();
}