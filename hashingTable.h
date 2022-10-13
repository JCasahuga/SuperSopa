#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

class hashingTable
{
    public:
        hashingTable();

        // Initialize Hash Table
        void doubleHash(const int size);

        // Inserts Value Into Table If Possible
        bool insert(const unsigned int value);

        // Searches Value in the Table
        bool search(const unsigned int value);

        // Erases Value of the Table
        void erase(const unsigned int value);

        // Returns true if the Table is Full
        bool isFull();

        void printHash();

        vector<int> hashTable;
        int keysPresent = 0;
        int tableSize;
        int prime;

    private:
        // Check if value is Prime
        bool isPrime(const int n);

        // Returns value of h1(s)
        unsigned int  hash1(const int s);

        // Returns value of h2(s)
        unsigned int  hash2(const int s);
};