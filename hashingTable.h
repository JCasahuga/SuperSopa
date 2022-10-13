#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

class hashingTable
{
    public:
        hashingTable();

        // Initialize Hash Table
        void doubleHash(long int size);

        // Inserts Value Into Table If Possible
        bool insert(long int value);

        // Searches Value in the Table
        bool search(long int value);

        // Erases Value of the Table
        void erase(long int value);

        // Returns true if the Table is Full
        bool isFull();

        vector<int> hashTable;
        long int keysPresent = 0;
        long int tableSize = INT64_C(1) << 2;
        long int prime;

    private:
        // Check if value is Prime
        bool isPrime(const long int n);

        // Returns value of h1(s)
        unsigned long int  hash1(long int s);

        // Returns value of h2(s)
        unsigned long int  hash2(long int s);
};