#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

class hashingTable
{
    public:
        hashingTable();

        // Initialize Hash Table
        void doubleHash(int size);

        // Inserts Value Into Table If Possible
        bool insert(unsigned int value);

        // Searches Value in the Table
        bool search(unsigned int value);

        // Erases Value of the Table
        void erase(unsigned int value);

        // Returns true if the Table is Full
        bool isFull();

        void printHash();

        vector<int> hashTable;
        int keysPresent = 0;
        int tableSize = INT64_C(1) << 2;
        int prime;

    private:
        // Check if value is Prime
        bool isPrime(const int n);

        // Returns value of h1(s)
        unsigned int  hash1(int s);

        // Returns value of h2(s)
        unsigned int  hash2(int s);
};