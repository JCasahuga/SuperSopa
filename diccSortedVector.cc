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

Pos diccSortedVector::move(Pos pos, Pos next){
    return {pos.x+next.x, pos.y+next.y};
}

bool diccSortedVector::allowedMove(Pos pos, Pos next){
    Pos final = {pos.x+next.x, pos.y+next.y};
    if(final.x < 0 || final.y < 0 || final.x >= soupSize || final.y > soupSize) return false;
    return true;
}


bool isPrefix(string search, string diccEntry){
    if(search < diccEntry && diccEntry.compare(0, search.size(), search) == 0 ) return true;
    return false;
}
// Implementation of SPECIAL binary search
// O(log n) -- Recursive Implementation

// -1 if NO, -2 if maybe, int >=0 [index in vector] if yes

int binarySearch(vector<string> words, string &word, int low, int high, bool prefix){
        if (low > high){
            if(prefix) return -2;
            return -1; 
        }else{
            int half = (low + high)/2; 
            if (word.compare(words[half]) == 0) {
                return half;
            }
            else if (word.compare(words[half]) > 0){
                bool pre = isPrefix(word, words[half]);
                return binarySearch(words, word, half + 1, high, pre);  
            }else {
                bool pre = isPrefix(word, words[half]);
                return binarySearch(words, word, low, half - 1, pre) ;
            }
        }
}
 

// A utility function to get the ASCII value
// of the character at index d in a string
// int char_at(string str, int d)
// {
//     if (str.size() <= d)
//         return -1;
//     else
//         return str.at(d);
// }

// // Non stable radix sort 
// void MSD_sort(vector<string> str, int lo, int hi, int d){
// // recursion break condition
//     cout << hi << lo << endl; 
//     cout << "what" <<endl;

//     for (int i=0; i< str.size(); i++) cout << str[i] ;
//     cout << endl; 


//     if (hi <= lo) {
//         cout << "break" << hi << ' '  <<lo << endl;
//         return;
//     }
//     int count[256 + 2] = { 0 };
 
//     // temp is created to easily swap strings in str[]
//     // int temp[n] can also be used but,
//     // it will take more space.
//     unordered_map<int, string> temp;
 
//     // Store occurrences of most significant character
//     // from each string in count[]
//     for (int i = lo; i <= hi; i++) {
//         int c = char_at(str[i], d);
//         count[c]++;
//     }
 
//     // Change count[] so that count[] now contains actual
//     //  position of this digits in temp[]
//     for (int r = 0; r < 256 + 1; r++)
//         count[r + 1] += count[r];
 
//     // Build the temp
//     for (int i = lo; i <= hi; i++) {
//         int c = char_at(str[i], d);
//         temp[count[c]++] = str[i];
//     }
 
//     // Copy all strings of temp to str[], so that str[] now
//     // contains partially sorted strings
//     for (int i = lo; i <= hi; i++)
//         str[i] = temp[i - lo];
 
//     // Recursively MSD_sort() on each partially sorted
//     // strings set to sort them by their next character
//     for (int r = 0; r < 256; r++)
//         MSD_sort(str, lo + count[r], lo + count[r + 1] - 1,
//                  d + 1);


//     //TODO
// }
//Public classes


//Constructora
diccSortedVector::diccSortedVector(){}


diccSortedVector::diccSortedVector(vector<string> words){ 
    sort(words.begin(),words.end());
    this->words = words;
}

//Consultora

int diccSortedVector::exists(string &word){
    vector<string> words = this->words;
    bool maybe = false;
    return binarySearch(words, word, 0, words.size() - 1, maybe);
}

bool diccSortedVector::deleteWord(int i ){
    if( i <= 0 || i > words.size()){
        words.erase(words.begin()+i-1);
        return true;
    }
    return false; 
}

//Prints

void diccSortedVector::printDicc(){
    for (int i = 0; i < words.size(); i++){
        cout << words[i] << endl;
    }
}


void diccSortedVector::printSoup(){
    for (int i = 0; i < soupSize; i++){
        cout << words[i] << endl;
    }
}

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
}

char diccSortedVector::getSoup(Pos pos){
    return soup[pos.x][pos.y];
}

string diccSortedVector::getDicc(int i){
    return words[i];
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

void init(vector<vector<bool>> visited, int soupSize){    //Ugly, TODO    
    for(int i=0; i < soupSize; i++){
        for(int k = 0; k < soupSize; k++){
            visited[i][k]= false;
        }
    }
}

void diccSortedVector::exploreSoup () {
    //Comencem per dalt a l'esquera
    Pos inicial = {0,0};
    vector<vector<bool>> visited(soupSize, vector<bool>(soupSize));
    init(visited, soupSize);

    for (int i = 0; i < soupSize && words.size()!=0;i++ ){
        for (int j= 0; j < soupSize && words.size()!=0;j++ ){
            string stringInicial = "";
            bool result = DFS(inicial, stringInicial, visited);
        }    
    }
}

// Function to perform DFS
// Traversal on the matrix grid[]
bool diccSortedVector::DFS(Pos pos, string builtWord, vector<vector<bool>> visited)
{
    // Initialize a stack of pairs and
    // push the starting cell into it
    stack<Pos> st;
    st.push(pos);
    string possibleWord = builtWord + getSoup(pos);
 
    // Iterate until the
    // stack is not empty
    while (!st.empty()) {
        // Pop the top pair
        Pos curr = st.top();
        st.pop();
        int x = exists(possibleWord);
        if( x >=0 ){
            //Cas que han trobat la paraula
            string paraula = getDicc(x);
            bool borrat = deleteWord(x);
            if(!borrat) cout <<"Error, s'ha trobat una paraula que no es pot borrar: "<<  paraula <<endl; 
            return true; 
        }else if(x == -2 ){
            // Mark the current
            // cell as visited
            visited[curr.x][curr.y] = true;
    
            // Print the element at
            // the current top cell
            cout <<getSoup(curr) << " ";
    
            // Push all the adjacent cells
            for (int i = 0; i < 7; i++) {
                Pos adj = move(curr,directions[i]);
                if(allowedMove(curr, adj) && ! visited[adj.x][adj.y]){
                    st.push(adj);
                }
            }
        }
    }
    return false;
    //word is not there
}