#include "diccSortedVector.h"


const Pos u = {0, -1};
const Pos r = {1,0}; 
const Pos d = {0, 1};
const Pos l = {-1,0};
const Pos dl = {-1,1};
const Pos dr = {1,1};
const Pos ul = {-1,-1}; 
const Pos ur = {1,-1}; 

const vector<Pos> directions = {l,ul,u,ur, r, dr, d, dl };

//Funcions auxiliars

bool isPrefix(string search, string diccEntry){
    if(search < diccEntry && diccEntry.compare(0, search.size(), search) == 0 ) return true;
    return false;
}

bool diccSortedVector::isInPrefix(string word) {
    return binary_search(prefixs.begin(), prefixs.end(), word);
}

//Constructore
diccSortedVector::diccSortedVector(){}


diccSortedVector::diccSortedVector(vector<string> words){ 
    sort(words.begin(),words.end());
    this->words = words;
}

// Getters setters & such

char diccSortedVector::getSoup(Pos pos){
    return soup[pos.x][pos.y];
}

string diccSortedVector::getDicc(int i){
    return words[i];
}

bool diccSortedVector::exists(string &word){
    //vector<string> words = this->words;
    //bool maybe = false;
    //return binarySearch( word, 0, words.size() - 1, maybe);
    return binary_search(words.begin(), words.end(), word);
}

bool diccSortedVector::deleteWord(int i ){
    if( i >= 0 || i < words.size()){
        words.erase(words.begin()+i);
        return true;
    }
    return false; 
}

//Actual Implementation of functions

//Checking if position is in vector
bool inPath(Pos pos, vector<Pos> path){
    for(int i = 0; i < path.size(); i++){
        if(path[i].x == pos.x && path[i].y == pos.y) return true;
    }
    return false;
}


//Build a Word from a vector of positions
string diccSortedVector::buildWord(vector<Pos> word){
    string result = "";
    for ( int i = 0; i< word.size(); i++){
        result=result+getSoup(word[i]);
    }
    return result;       
}


//Sum of two Positions
Pos diccSortedVector::move(Pos pos, Pos next){
    return {pos.x+next.x, pos.y+next.y};
}

//Utility function to check if a position is valid
bool diccSortedVector::allowedMove(Pos final){
    if(final.x < 0 || final.y < 0 || final.x >= soupSize || final.y > soupSize) return false;
    return true;
}


// Explore soup
// Worst case there are no words in the soup, so we have to check every position
// Every position n² times the Backtracking algorithm.
void diccSortedVector::exploreSoup () {

    set<string> paraulesTrobades; 
    //For each position, if there's still words left to look for
    // And it has not been used by another word, start a DFS
    set<string> wordsFound;
    int total = 0;
    vector<vector<bool>> used(soupSize, vector<bool>(soupSize, false));
    for (int i = 0; i < soupSize; i++ ){
      //  cerr << "HERE---" << i <<  endl;
        for (int j= 0; j < soupSize; j++ ){
            string stringInicial = "";
            Pos inicial = {i,j};

            used[inicial.x][inicial.y] = true;
            search(inicial, stringInicial, used, wordsFound, total);
            used[inicial.x][inicial.y] = false;

            for(string w : wordsFound){
                paraulesTrobades.insert(w);
            }
        }    
    }
    
    //Printing of the soup words found
    cout << "Number of words found:  " << paraulesTrobades.size() << endl;
    // cout << "Out of the subset, words not found: "<<endl; 
    // for(int i = 0 ; i < subset.size(); i++){
    //     if(paraulesTrobades.find(subset[i]) == paraulesTrobades.end()){
    //         cout << subset[i] << endl;
    //     }
    // }
}

// Function to perform backtracking
// The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node. 
void diccSortedVector::search(Pos pos, string& builtWord, vector<vector<bool>>& used, set<string>& foundWords, int& total)
{

    // Set
    used[pos.x][pos.y] = true;
    builtWord.push_back(soup[pos.x][pos.y]);


   // cerr << "checking " << builtWord << endl;
    // Over Maximum Size Word
    if (builtWord.size() > maxWordSize) {
        // Unset
        used[pos.x][pos.y] = false;
        builtWord.pop_back();
        return;
    }

    if (usePrefix and (not isInPrefix(builtWord)))
    {
        used[pos.x][pos.y] = false;
        builtWord.pop_back();
        return ;
    }

    // Is in the Hash Table?
    if (exists(builtWord)) {
        ++total;
        foundWords.insert(builtWord);
    }

    //Loops to All Directions
    for (int i = 0; i < 8; ++i) {
        pos.x += directions[i].x;
        pos.y += directions[i].y;

        if (min(pos.x, pos.y) >= 0 && max(pos.x, pos.y) < soupSize) {
            if (not used[pos.x][pos.y]) {
                used[pos.x][pos.y] = true;
                Pos p = {pos.x, pos.y};
                search(p, builtWord, used, foundWords, total);
                used[pos.x][pos.y] = false;
            }
        }
        pos.x -= directions[i].x;
        pos.y -= directions[i].y;
    }
    
    // Unset
    builtWord.pop_back();
    used[pos.x][pos.y] = false;
}


//Prints

void diccSortedVector::printDicc(){
    for (int i = 0; i < words.size(); i++){
        cout << words[i] << endl;
    }
}


void diccSortedVector::printSoup(){
    for (int i = 0; i < soupSize; i++){
        for(int j = 0 ; j < soupSize; j++){
            cout << soup[i][j] << " ";
        }
        cout << endl;
    }
}

void diccSortedVector::printPos(Pos p){
    cout << "(" << p.x << "," << p.y << ")";
}


// Readers for constructions

void diccSortedVector::readInput() {
    readWords();
    //cout << "Words Read" << endl; 
    readSoup();
    //cout << "Soup Read" << endl; 
    
}

void diccSortedVector::readWords () {
    cin >> totalWords;
    maxWordSize = 0;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) {
        cin >> words[i];
        if (words[i].size() > maxWordSize) maxWordSize = words[i].size();

        string s;
        prefixs.push_back(words[i]);
        for (int j = 0; j < words[i].size(); ++j) {
            s.push_back(words[i][j]);
            prefixs.push_back(s);
        }
    }
    sort(words.begin(), words.end());
    sort(prefixs.begin(), prefixs.end());
}



void diccSortedVector::readSoup () {
    // Read subset
    cin >> subsetSize; 
    for(int i =0 ;i < subsetSize; i++){
        string word; 
        cin >> word ; 
        subset.push_back(word);
    }
    
    // Read Soup Size
    cin >> soupSize;
    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];

}
