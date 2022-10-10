#include "diccSortedVector.h"


const Pos u = {0, -1}; 
const Pos d = {0, 1};
const Pos l = {-1,0};
const Pos r = {1,0};
const Pos dl = {-1,1};
const Pos dr = {1,1};
const Pos ul = {-1,-1}; 
const Pos ur = {1,-1}; 

const vector<Pos> directions = {u, d, l, r, dl, dr, ul, ur};

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
    cout << "Deleting word " << words.size() << endl;
    if( i >= 0 || i < words.size()){
        words.erase(words.begin()+i);
        return true;
    }
    return false; 
}

//Actual Implementation of functions

//Una paraula no pot reutilitzar lletres d'altres paraules
//Falta guardar posicions de les paraules trobades i marcarles com a visited
void diccSortedVector::exploreSoup () {
    //Comencem per dalt a l'esquera
    vector<vector<bool>> visited(soupSize, vector<bool>(soupSize));
    init(visited, soupSize);
    vector<string> original = words;
    cout<<"Hello visiting soup"<<endl; 

    for (int i = 0; i < soupSize && words.size()!=0;i++ ){
        for (int j= 0; j < soupSize && words.size()!=0;j++ ){
            string stringInicial = "";
            Pos inicial = {i,j};
            cout<<"Accessing dfs"<< i << j <<endl;
            bool result = DFS(inicial, stringInicial, visited);
             
        }    
    }
    cout << "Done, words not found: " << endl;
    printDicc();

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


Pos diccSortedVector::move(Pos pos, Pos next){
    return {pos.x+next.x, pos.y+next.y};
}

bool diccSortedVector::allowedMove(Pos pos, Pos next){
    Pos final = {pos.x+next.x, pos.y+next.y};
    if(final.x < 0 || final.y < 0 || final.x >= soupSize || final.y > soupSize) return false;
    return true;
}

string buildWord(vector<Pos> word){
    string result = "";
        for (for int i = 0; i< word.size(); i++){
            result=result+getSoup(word[i]);
        }
    return result;       
}

// Function to perform DFS
// Traversal on the matrix grid[]
bool diccSortedVector::DFS(Pos pos, string builtWord, vector<vector<bool>> visited)
{
    // Initialize a stack of pairs and
    // push the starting cell into it
    stack<pair<Pos, vector<Pos>>> st;
    vector<Pos> cami = {pos}; 
    st.push({pos, cami});
    cout << "Pushed ";

    if(exists(builtWord) == -1){ //Em sembla que aixo no serveix de re
        cout << "No word starts with " << builtWord << endl;
        return false;
    }
    while (!st.empty()) {
        Pos curr = st.top().first;
        vector<Pos> word = st.top().second;
        word.push_back(curr);
        st.pop();  
        string built = buildWord(word);
        cout <<"PossibleWord: " << built << endl;

        
        int x = exists(built);
        cout << "State of substring: "<< built<< " " << x << endl; 
        if( x >=0 ){
            //Cas que han trobat la paraula
            string paraula = getDicc(x);
            bool borrat = deleteWord(x);
            cout << "Found word: " << paraula << "--------------------------------------------" <<endl;
            if(!borrat) cout <<"Error, s'ha trobat una paraula que no es pot borrar: "<<  paraula <<endl; 
            return true; 
        }else if(x == -2 ){
            cout << "Im in"<<endl;
            //esc -> esc no troba resultat 
            // Mark the current
            // cell as visited
            visited[curr.x][curr.y] = true;
    
            // Print the element at
            // the current top cell    
            // Push all the adjacent cells
            for (int i = 0; i < 7; i++) {
                Pos adj = move(curr,directions[i]);
                if(allowedMove(curr, adj) && ! visited[adj.x][adj.y]){
                    cout<<"pushing"<<endl;
                    st.push({adj, word});
                }
            }
        }else{

        }
    }
    return false;
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



// Readers for constructions

void diccSortedVector::readInput() {
    readWords();
    cout << "Words Read" << endl; 
    readSoup();
    cout << "Soup Read" << endl; 
    
}

void diccSortedVector::readWords () {
    string x;
    cin >> x;
    while(x != "END"){
        words.push_back(x);
        cin >> x;
    } 
    sort(words.begin(),words.end());
    cout << "Words Read and sorted" << endl;
}



void diccSortedVector::readSoup () {
    cout << "Set Soup Size" << endl; 
    // Read Soup Size
    soupSize =20;

    // Read Soup Values
    char c;
    soup = vector<vector<char>>(soupSize, vector<char>(soupSize));
    cout << soup.size() << soup[0].size() << endl; 

    for (int i = 0; i < soupSize; ++i){
        for (int j = 0; j < soupSize; ++j){
            cin >> c;
            soup[i][j] = c;
        }
    }
}
