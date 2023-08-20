#ifndef BLOOMFILTER
#define BLOOMFILTER
#include <string>
#include <iostream>

using namespace std;

class BloomFilter
{
private:
    int size;
    unsigned char* array;
public:
    // Constructor
    BloomFilter(int size);
    // Destructor
    ~BloomFilter();
    // returns the array of the bloom filter
    unsigned char* get_array(void) const;
    // merging two bloom filter arrays with bitwise or at all indexes
    void set_array(unsigned char* bf_array);
    // Inserting an element in the bloom filter
    void Insert(unsigned char* value);
    // Searching the probability of an element existing in the bloom filter
    bool Search(unsigned char* value);
    // Printing the bloom filter using integers
    void Print();
};

#endif