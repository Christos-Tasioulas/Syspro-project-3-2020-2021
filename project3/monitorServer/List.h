#ifndef LIST
#define LIST
#include <iostream>

using namespace std;

// ListNode
class ListNode
{
private:
    void* value;
    ListNode* next;
public:
    // ListNode constructor 
    ListNode(void* v);
    // ListNode destructor
    ~ListNode();
    // changing the value of a node to the given value
    void set_value(void* v);
    // getting the value of the node
    void* get_value() const;
    // changing the next node to the given node
    void set_next(ListNode* node);
    // getting the next node
    ListNode* get_next(void) const;
    // printing the node value
    void print(void (*visit)(void *));
};

// List
class List
{
private:
    ListNode* head;
    ListNode* last;
    int size;
public:
    // List constructor
    List();
    // List destructor
    ~List();
    // Returning the first node of the list
    ListNode* get_first(void) const;
    // Returning the first node of the list
    ListNode* get_last(void) const;
    // Returning the size of the list
    int get_size(void) const;
    // Inserting a value as the head of the list
    void ListInsertFirst(void* value);
    // Inserting a value after a specific node
    void ListInsertAfter(void* value, ListNode* node);
    // Inserting a value as the end of the list
    void ListInsertLast(void* value);
    // Searching the value on the list
    bool ListSearch(void* value, int (*compare)(void *, void *));
    // Searching the node on the list with the value given
    ListNode* ListNodeSearch(void* value, int (*compare)(void *, void *));
    // Removing the node given from the list
    void Remove(void* value, int (*compare)(void *, void *)); 
    // printing a list visiting the value
    void print(void (*visit)(void *));
};

#endif