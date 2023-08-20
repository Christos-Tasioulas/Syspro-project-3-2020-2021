#include "List.h"

//Class List

// List constructor
List::List()
{
    this->head = NULL;
    this->last = NULL;
    this->size = 0;
}

// List destructor
List::~List()
{
    this->size = 0;
    this->last = NULL;
    ListNode* node;
    node = this->head;
    // destroying each node of the list
    while(node != NULL)
    {
        this->head = node->get_next();
        delete node; 
        node = this->head; 
    }
}

// Returning the first node of the list
ListNode* List::get_first(void) const
{
    return this->head;
}

// Returning the first node of the list
ListNode* List::get_last(void) const
{
    return this->last;
}

// Returning the size of the list
int List::get_size(void) const
{
    return this->size;
}

// Inserting a value inside the list
void List::ListInsertFirst(void* value)
{
    ListNode* node;
    node = new ListNode(value);

    // this is the only node
    if(this->head == NULL)
    {   
        this->last = node;
    }
    else node->set_next(this->head);
    // inserting the node at the start
    this->head = node;
    this->size++;
}

// Inserting a value after a specific node
void List::ListInsertAfter(void* value, ListNode* node)
{
    if(node == NULL)
    {
        this->ListInsertFirst(value);
    }
    else if(node == this->last)
    {
        this->ListInsertLast(value);
    }
    else
    {
        ListNode* newNode = new ListNode(value);
        newNode->set_next(node->get_next());
        node->set_next(newNode);
    }
}

// Inserting a value as the end of the list
void List::ListInsertLast(void* value)
{
    ListNode* node;
    node = new ListNode(value);

    // this is the only node
    if(this->last == NULL)
    {
        this->head = node;
    }
    else this->last->set_next(node);
    // inserting the node at the end
    this->last = node;
    this->size++;
}

// Searching the value on the list
bool List::ListSearch(void* value, int (*compare)(void *, void *))
{
    ListNode* node;
    node = this->head;
    // traversing the list node by node
    while(node != NULL)
    {
        // We found it 
        if(compare(value, node->get_value()) == 0) return true;
        node = node->get_next();
    }
    // it doesn't exist
    return false;
}

// Searching the node on the list with the value given
ListNode* List::ListNodeSearch(void* value, int (*compare)(void *, void *))
{
    ListNode* node;
    node = this->head;
    // traversing the list node by node
    while(node != NULL)
    {
        // We found it 
        if(compare(value, node->get_value()) == 0) return node;
        node = node->get_next();
    }
    // it doesn't exist
    return NULL;
}

// Removing the node given from the list
void List::Remove(void* value, int (*compare)(void *, void *))
{
    ListNode* node = this->head;
    ListNode* prev = NULL;

    while(node != NULL)
    {
        // we found the node
        if(compare(node->get_value(), value) == 0)
        {
            if(prev != NULL)
            {
                prev->set_next(node->get_next());
            }
            // it is the first node
            else
            {
                this->head = node->get_next();
            }
            // it is the last node
            if(node->get_next() == NULL)
            {
                this->last = prev;
            }
            node->set_next(NULL);
            
            delete node;
            return;

        }
        // marking the previous node
        prev=node;
        node=node->get_next();
    }
}

// printing a list visiting the value
void List::print(void (*visit)(void *))
{
    ListNode* node;
    node = head;
    while(node != NULL)
    {
        // printing each node 
        node->print(visit);
        node = node->get_next();

        // another glitch breaker
        cout << endl;
    }
}

//Class ListNode

// ListNode constructor 
ListNode::ListNode(void* v)
{
    this->value = v;
    this->next = NULL;
}

// ListNode destructor
ListNode::~ListNode()
{
    this->next = NULL;
}

// changing the value of a node to the given value
void ListNode::set_value(void* v)
{
    this->value = v;
}

// getting the value of the node
void* ListNode::get_value() const
{
    return this->value;
}

// changing the next node to the given node
void ListNode::set_next(ListNode* node)
{
    this->next = node;
}

// getting the next node
ListNode* ListNode::get_next(void) const
{
    return this->next;
}

// printing the node value
void ListNode::print(void (*visit)(void *))
{
    visit(this->value);
}