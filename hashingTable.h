#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

class hashingTable
{
    public:
        // Constructor
        hashingTable();

        // Initialize Hash Table
        void doubleHash(const int size);

        // Inserts Value Into Table If Possible
        bool insert(const unsigned int value);

        // Searches Value in the Table
        bool search(const unsigned int value);

        vector<int> hashTable;
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