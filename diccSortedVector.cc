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

void init(vector<vector<bool>> visited, int soupSize){    //Ugly, TODO    
    for(int i=0; i < soupSize; i++){
        for(int k = 0; k < soupSize; k++){
            visited[i][k]= false;
        }
    }
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

int diccSortedVector::exists(string &word){
    vector<string> words = this->words;
    bool maybe = false;
    return binarySearch( word, 0, words.size() - 1, maybe);
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


//Function to keep track of used positions by other words and therefore avoid cycles
void setVisited(vector<Pos>path, vector<vector<bool>> &visited){
    for(int i = 0; i < path.size(); i++){
        visited[path[i].x][path[i].y] = true;
    }
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


//Explore soup
// Worst case there are no words in the soup, so we have to check every position
//Every position n² times the Backtracking algorithm times set Visited. Set visited has O(w) where w is the length of the word
void diccSortedVector::exploreSoup () {
    vector<vector<bool>> visited(soupSize, vector<bool>(soupSize));
    init(visited, soupSize);
    vector<string> original = words;

    //For each position, if there's still words left to look for
    // And it has not been used by another word, start a DFS
    for (int i = 0; i < soupSize && words.size()!=0;i++ ){
        for (int j= 0; j < soupSize && words.size()!=0;j++ ){
            if(! visited[i][j]){
                string stringInicial = "";
                Pos inicial = {i,j};
                vector<Pos> path = bckT(inicial, stringInicial, visited);
                setVisited(path, visited); 
                
            }
        }    
    }

    //Words not found that are in the dictionary, 
    cout << "Done, words not found: " << endl;
    printDicc();
    //Printing of the soup words found
    cout << "Words found; "<< endl; 
    for(int i = 0; i < soupSize; i++){
        for(int j = 0; j < soupSize; j++){
            if(visited[i][j]) cout << soup[i][j] << " ";
            else cout << "· ";
        }
        cout << endl;
    }

}



// Implementation of SPECIAL binary search
// O(log n) -- Recursive Implementation

// -1 if NO, -2 if maybe, int >=0 [index in vector] if yes

int diccSortedVector::binarySearch(string &word, int low, int high, bool prefix){
        if (low > high){
            if(prefix) return -2;
            return -1; 
        }else{
            int half = (low + high)/2; 
            bool pre = isPrefix(word, words[half]);
            if(prefix && ! pre) return -2; 
            else if (word.compare(words[half]) == 0) {
                return half;
            }
            else if (word.compare(words[half]) > 0){
                return binarySearch(word, half + 1, high, pre);  
            }else {
                return binarySearch(word, low, half - 1, pre) ;
            }
        }
}

// Function to perform backtracking
// The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node. 
vector<Pos> diccSortedVector::bckT(Pos pos, string builtWord, vector<vector<bool>> visited)
{
    // Initialize a stack of pairs and
    // push the starting cell and into it
    stack<pair<Pos, vector<Pos>>> st;
    vector<Pos> path; 
    st.push({pos, path});
    

    while (!st.empty()) {
        //Extraction of the first element of the stack
        Pos curr = st.top().first;
        vector<Pos> word = st.top().second;
        word.push_back(curr);
        st.pop();  
        //Build the word from the path
        string built = buildWord(word);
        
        //Check if the word is in the dictionary, special binarySearch
        int x = exists(built);
        if( x >= 0 ){
            //We have found the word, delete it from the dictionary
            string paraula = getDicc(x);
            bool borrat = deleteWord(x);
            cout << "Found word: " << paraula  <<endl;
            if(!borrat) cout <<"Error, s'ha trobat una paraula que no es pot borrar: "<<  paraula <<endl; 
            return word; 
        }else if(x == -2 ){
            //The word has not been found but it is a prefix of a word in the dictionary 
            for (int i = 0; i < 8; i++) {
                Pos adj = move(curr,directions[i]);
                if(allowedMove(adj) && (!visited[adj.x][adj.y]) && !inPath(adj, word)){
                    st.push({adj, word});
                }
            }
        }
        //There exists no prefix of the word in the dictionary, so we discard it and stop exploring the path
    }
    return {};
    //word is not there
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
    cout << "(" << p.x << "," << p.y << ")" << endl;
}


// Readers for constructions

void diccSortedVector::readInput() {
    readWords();
    cout << "Words Read" << endl; 
    readSoup();
    cout << "Soup Read" << endl; 
    
}

void diccSortedVector::readWords () {
    cin >> totalWords;
    words = vector<string>(totalWords, "-1");
    for (int i = 0; i < totalWords; ++i) 
        cin >> words[i];
    sort(words.begin(),words.end());
    cout << "Words Read and sorted" << endl;
}



void diccSortedVector::readSoup () {
    // Read Soup Size
    cin >> soupSize;

    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j)
            cin >> soup[i][j];
}

