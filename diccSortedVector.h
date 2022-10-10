#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include<algorithm> 
#include <stack>
using namespace std;

#ifndef _DICCSORTEDVECTOR_HH_
#define _DICCSORTEDVECTOR_HH_

using namespace std;

//Different states for soup exploring
#define NO -1;
#define MAYBE -2;

//Helper functions and typedef to explore the soup
typedef struct{
    int x;
    int y;
} Pos;


class diccSortedVector
{
    private:
        vector<string> words;
        int totalWords; 

        int soupSize;
        vector<vector<char>> soup;
        
        void readWords(); 
        void readSoup(); 
        int binarySearch(string &word, int low, int high, bool prefix);


    public:
        diccSortedVector();

        diccSortedVector(vector<string> words);

        int exists(string &word);

        void printDicc();

        void printSoup();

        bool deleteWord(int i); 

        void readInput();

        void exploreSoup();

        bool DFS(Pos pos, string builtWord, vector<vector<bool>> visited);
        
        string getWord(int i);
        
        Pos move(Pos pos, Pos next);

        bool allowedMove(Pos pos, Pos next);

        string getDicc(int i);
        char getSoup(Pos pos);
};
#endif
