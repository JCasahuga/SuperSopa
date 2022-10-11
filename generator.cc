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
        for (int j = 0; j < soup[i].size(); ++j) if (soup[i][j] == '.') soup[i][j] = rand()%24 + 'a';
    }
}

//////////////////////////// MAIN //////////////////////////////

int main()
{
    srand(time(NULL));

    string word;
    while (cin >> word) dictionary.push_back(word);
    
    selectWordSet(20);     // Result is saved in selectedWords var 
    N = 20;                   // Deafult value = 20
    DEBUG = false;            // DEBUG mode

    //printSelectedWords();

    soup = Sopa(N, Files(N, '.'));

    int placedWords = 0;
    for (auto word : selectedWords) if(addWordToSoup(word)) ++placedWords;
    cerr << "The placed words are " << placedWords << " out of " << selectedWords.size() << endl;
    fillSoupEmptySpaces();

    cout << dictionary.size() << endl;
    printDictionary();

    // cout << selectedWords.size();
    // printSelectedWords();

    cout << N << endl;
    printSoup();
}