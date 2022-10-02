#include <iostream>
#include <vector>
using namespace std;

// En Aquest Algoritme Treballarem Els Caracters Com Enters
// Per Tal de Indexar-los En La Taula

int tableSize;
int prime = 64763;

vector<int> hashTable;
int keysPresent = 0;

vector<vector<char>> soup;

vector<int> offSetsX = {1,-1,0,0,1,1,-1,-1};
vector<int> offSetsY = {0,0,1,-1,1,-1,-1,1};

int maxWordSize = 0;

// Check if value is Prime
bool isPrime(int n)
{
    if (n == 1 || n == 0)
        return false;
  
    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Initialize Hash Table
void doubleHash(int size) {
    tableSize = size;
    /*
    prime = size - 1;
    while (!isPrime(size)) ++prime;
    hashTable = vector<int>(prime, -1);
    */
   hashTable = vector<int>(prime, -1);
}

// Returns value of h1(s)
int hash1(int s) {
    return abs(s%tableSize);
}

// Returns value of h2(s)
int hash2(int s) {
    return abs(prime - (s%prime));
}

// Inserts Value Into Table If Possible
void insert(int value) {
    if (value == -1 || value == -2)
        cout << "Can't be Inserted" << endl;

    int hashed = hash1(value);
    int offset = hash2(value);

    while (hashTable[hashed] != -1) {
        if (hashTable[hashed] == -2) break;
        hashed = (hashed+offset) % tableSize;
    }

    hashTable[hashed] = value;
    ++keysPresent;
}

// Searches Value in the Table
bool search(int value) {
    int hashed = hash1(value);
    int offset = hash2(value);
    int initialPos = hashed;
    bool firstItr = true;
    
    while(true) {
        if(hashTable[hashed] == -1)                  
            break;
        else if(hashTable[hashed] == value)      
            return true;
        else if(hashed == initialPos && !firstItr)    // Stop search if one complete traversal of hash table is completed.
            return false;
        else
            hashed = ((hashed + offset) % tableSize);  // if none of the above cases occur then update the index and check at it.

        firstItr = false;
    }
    return false;
}

// Erases Value of the Table
void erase(int value) {
    if(!search(value))
        return;    
        
    int hashed = hash1(value);
    int offset = hash2(value);

    while(hashTable[hashed] != -1) {
        if(hashTable[hashed] == value){
            hashTable[hashed] = -2;
            keysPresent--;
            return;
        }
        else hashed = (hashed + offset) % tableSize;
    }
}

// Returns true if the Table is Full
bool isFull() {
    return keysPresent == tableSize;
}

// Store the string as Int
int stringToInt(string s) {
    const int p = 31;
    const int m = 1e9 + 9;
    int hash_value = 0;
    int p_pow = 1;
    for (int i = 0; i < s.size(); ++i) {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Explores All Combinations of the Soup
void exploreSoup(int n, string s, int x, int y, vector<vector<char>>& used, int total) {
    used[x][y] = -1;
    s.push_back(soup[x][y]);
    //cout << s << endl;
    int v = stringToInt(s);
    if (search(v)) {
        cout << "Found " << s << endl;
    }

    if (total+1 >= maxWordSize) return;

    for (int i = 0; i < 8; ++i) {
        int xPos = x + offSetsX[i];
        int yPos = y + offSetsY[i];
        if (min(xPos, yPos) >= 0 && max(xPos, yPos) < n) {
            char aux = used[xPos][yPos];
            if (aux != -1) {
                used[xPos][yPos] = -1;
                exploreSoup(n, s, xPos, yPos, used, total+1);
                used[xPos][yPos] = aux;
            }
        }
    }

}

int main() {
    doubleHash(64768);
    // Read Words to Find
    int nW;
    cin >> nW;
    for (int i = 0; i < nW; ++i) {
        string word;
        cin >> word;
        insert(stringToInt(word));
        int size = word.size();
        maxWordSize = max(size, maxWordSize);
    }

    // Read Soupector<vector<char>> Size
    int n;
    cin >> n;

    // Read Soup Values
    char c;
    soup = vector<vector<char>>(n, vector<char>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> soup[i][j];
        }
    }

    // Explore Soup
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<vector<char>> used = soup;
            exploreSoup(n, "", i, j, used, 0);
        }
    }

    //vector<vector<char>> used = soup;
    //exploreSoup(n, "", 0, 2, used, 0);
}