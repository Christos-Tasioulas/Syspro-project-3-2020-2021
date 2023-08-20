#ifndef CYCLICBUFFER
#define CYCLICBUFFER
#include <string>
#include <pthread.h>

using namespace std;

class CyclicBuffer
{

private:
    string* array;
    int size; // cyclicBufferSize 
    int count; // the number of elements in the array
    int start; // the index in which we will fetch a string from the buffer
    int end; // the index in which we will insert a string from the buffer
    pthread_mutex_t mtx;
    pthread_cond_t cond_nonempty;
    pthread_cond_t cond_nonfull;

public:
    // Constructor
    CyclicBuffer(int cbs);
    // Destructor
    ~CyclicBuffer();
    // Returns the array where the data will be stored
    string* get_array(void) const;
    // returns the first string in the order
    string get_string();
    // sets the string given in the right index
    void set_string(string s);
    // returns the cyclicBufferSize
    int get_size(void) const;
    // returns the number of elements in the array
    int get_count(void) const;
    int get_start(void) const;
    int get_end(void) const;
    // returns the thread condition 'nonempty'
    pthread_cond_t get_nonempty(void) const;
    // returns the thread condition 'nonfull'
    pthread_cond_t get_nonfull(void) const;
};

#endif