// class SkipListNode
#ifndef SKIPLIST
#define SKIPLIST
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

class SkipListNode
{
private:
    void* value;
    SkipListNode** next_array;

public:
    // Constructor
    SkipListNode(void* value, int levels);
    // Destructor
    ~SkipListNode();
    // returning the node's value
    void* get_value() const;
    // returning the next node of the node in the given level
    SkipListNode* get_next(int level) const;
    // changing the next node of the node in the given level
    void set_next(int level, SkipListNode* node);
};

// class SkipList

class SkipList
{
private:
    int levels;
    int count;
    SkipListNode** first_array;

public:
    // Constructor
    SkipList(int levels);
    // Destructor
    ~SkipList();
    // Inserting a value in the skip list sorted
    void Insert(void *v, int (*compare)(void *, void*));
    // Searching a value in the skip list
    bool Search(void *v, int (*compare)(void *, void*));
    // Removing a value from the skip list
    void Remove(void *v, int (*compare)(void *, void*));
    // Printing the skip list
    void Print(void (*visit)(void*));
    // Returning the number of elements from the list
    int get_count(void) const;
    // Returning the first node of the whole skip list
    SkipListNode* get_first() const;
};


#endif

