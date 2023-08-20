#include "BloomFilter.h"

// hash functions

// This algorithm (k=33) was first reported by dan bernstein many years 
// ago in comp.lang.c. 
// The magic of number 33 (why it works better than many other constants, 
// prime or not) has never been adequately explained.
unsigned long djb2(unsigned char *str) {
	unsigned long hash = 5381;
	int c; 
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}



// This algorithm was created for sdbm (a public-domain reimplementation of ndbm) 
// database library. it was found to do well in scrambling bits, causing better 
// distribution of the keys and fewer splits. it also happens to be a good 
// general hashing function with good distribution. The actual function 
// is hash(i) = hash(i - 1) * 65599 + str[i]; what is included below 
// is the faster version used in gawk. There is even a faster, duff-device 
// version. The magic constant 65599 was picked out of thin air while experimenting 
// with different constants, and turns out to be a prime. this is one of the 
// algorithms used in berkeley db (see sleepycat) and elsewhere.
unsigned long sdbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while ((c = *str++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}



// Return the result of the Kth hash funcation. This function uses djb2 and sdbm.
// None of the functions used here is strong for cryptography purposes but they
// are good enough for the purpose of the class.

// The approach in this function is based on the paper:
// https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf
unsigned long hash_i(unsigned char *str, unsigned int i) {
	return djb2(str) + i*sdbm(str) + i*i;
}


// class BloomFilter

// Constructor
BloomFilter::BloomFilter(int size)
{
    this->size = size;
    this->array = new unsigned char [size];
    for(int i = 0; i < size; i++)
    {
        this->array[i] = 0;
    }
}

// Destructor
BloomFilter::~BloomFilter()
{
    // Bloom Filter is just an array of unsigned char
    delete[] this->array; 
}

// merging two bloom filter arrays with bitwise or at all indexes
void BloomFilter::set_array(unsigned char* bf_array)
{
    for(int i=0; i<this->size; i++)
    {
        this->array[i] = this->array[i] | bf_array[i];
    }
}

// returns the array of the bloom filter
unsigned char* BloomFilter::get_array(void) const
{
    return this->array;
}

// Inserting an element in the bloom filter
void BloomFilter::Insert(unsigned char* value)
{
    unsigned long result_1 = djb2(value);
    unsigned long result_2 = sdbm(value);
    unsigned long result_3 = hash_i(value, 2);

    unsigned long results[3] = {result_1, result_2, result_3};

    // algorithm to find out the mask we will use to insert the 3 results in the filter
    for(int i = 0; i < 3; i++)
    {
        int temp = results[i]%(this->size*8);

        int index=temp/8;         //byte index in the array
        int bit= temp%8;           //bit index of byte

        char mask=1;
        int j;

        for(j=0; j<bit; j++){

            mask = mask << 1;
        }

        // (the 8 bits the bit we want is located) or (the bit index we want to change (mask)) 
        this->array[index] = this->array[index] | mask;
    }
} 

// Searching the probability of an element existing in the bloom filter
bool BloomFilter::Search(unsigned char* value)
{
    unsigned long result_1 = djb2(value);
    unsigned long result_2 = sdbm(value);
    unsigned long result_3 = hash_i(value, 2);

    unsigned long results[3] = {result_1, result_2, result_3};
    bool exists = true;

    // algorithm to find out the mask we will use to examine whether the element exists
    for(int i = 0; i < 3; i++)
    {
        int temp = results[i]%(this->size*8);

        int index=temp/8;         //byte index in the array
        int bit= temp%8;           //bit index of byte

        unsigned char mask=1;
        int j;

        for(j=0; j<bit; j++){

            mask = mask << 1;
        }

        // determining if the bit representing the hash function result exists
        if((this->array[index] & mask) != mask)
       {
           // we need all 3 bits in order to confirm the probability that the id exists
           exists = false;
           break;
       }
    }

    return exists;
} 

// Printing the bloom filter using integers
void BloomFilter::Print()
{
    for(int i = 0;  i < this->size; i++)
    {
        // turning unsigned char to int in order to be printable
        cout << (int) this->array[i] << " ";
    }
    cout << endl;
}