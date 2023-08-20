#include "SkipList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// class SkipListNode

// Constructor
SkipListNode::SkipListNode(void* value, int levels)
{
    this->value = value;
    // the node will have a number of pointers pointing to next nodes 
    // depending on the levels it wiil be acended
    this->next_array = new SkipListNode* [levels];
    for(int i = 0; i < levels; i++)
    {
        this->next_array[i] = NULL;
    }
}

// Destructor
SkipListNode::~SkipListNode()
{
    delete[] this->next_array;
}

// returning the node's value
void* SkipListNode::get_value() const
{
    return this->value;
}

// returning the next node of the node in the given level
SkipListNode* SkipListNode::get_next(int level) const
{
    return this->next_array[level];
}

// changing the next node of the node in the given level
void SkipListNode::set_next(int level, SkipListNode* node)
{
    this->next_array[level] = node;
}


// class SkipList

// Constructor
SkipList::SkipList(int levels)
{
    this->count = 0;
    this->levels = levels;
    // there will be a pointer at the first level for every node possible
    this->first_array = new SkipListNode* [levels];
    for(int i = 0; i < levels; i++)
    {
        this->first_array[i] = NULL;
    }
    // seeding the rand for the insert function
    srand((unsigned int) time(NULL));
}

// Destructor
SkipList::~SkipList()
{
    // Destroying the list using only the first level
    SkipListNode* node = this->first_array[0];
    SkipListNode* nextnode;
    while(node != NULL)
    {
        nextnode = node->get_next(0);
        delete node;
        node = nextnode;
    }
    delete[] this->first_array;
}

// Inserting a value in the skip list sorted
void SkipList::Insert(void *v, int (*compare)(void *, void*))
{
    SkipListNode* node = new SkipListNode(v, this->levels);
    this->count++;
    // Checking whether the list is empty
    if(this->first_array[0] == NULL)
    {
        this->first_array[0] = node;
    }
    else
    {
        SkipListNode* temp;
        // Starting from the top levels
        int i = this->levels-1;
        temp = this->first_array[i];

        // initializing the pathing from the first node of each level
        SkipListNode* prevnodearray[this->levels];
        for(int j = 0; j < levels; j++)
        {
            prevnodearray[j] = NULL;
        }

        while(i >= 0)
        { 
            // Checking whether the level is empty
            if(this->first_array[i] == NULL)
            {
                i--;
                temp = this->first_array[i];
            }
            else if(temp != NULL)
            {
                // we don't need duplicates
                if(compare(v, temp->get_value()) == 0)
                {
                    this->count--;
                    delete node;
                    return;
                }
                // the given value is less than the current value we examine 
                else if(compare(v, temp->get_value()) < 0)
                {
                    // we go a level down if able starting from the previous node 
                    // or from the first node of the previous level
                    if((temp == this->first_array[i]) && (i > 0)) temp = this->first_array[i-1];
                    else temp = prevnodearray[i];
                    i--;
                }
                else
                {
                    prevnodearray[i] = temp;
                    // we reached the last node of the level
                    if(temp->get_next(i) == NULL)
                    {
                        i--;
                    }    
                    else temp = temp->get_next(i);
                }
            } 
        }

        int log = (int) log2(this->count);
        int level = 0;
        // the number of levels should be log2n in order to preserve O(log2n) complexity in the skip list
        while(level < log && level < this->levels)
        {
            
            int n = rand();
            // there is a 50 - 50 chance a node will ascend level 
            // but it will be inserted in the zero level either way
            if(((n % 100) > 50) || (level == 0))
            {
                // if the current level is empty
                if(this->first_array[level] == NULL)
                {
                    this->first_array[level] = node;
                }
                // if the value is less than any value in the current level
                else if(compare(v, this->first_array[level]->get_value()) < 0)
                {
                    node->set_next(level, this->first_array[level]);  
                    this->first_array[level] = node;   
                }
                else
                {
                    node->set_next(level, prevnodearray[level]->get_next(level));
                    prevnodearray[level]->set_next(level, node);
                }
                level++;  
            }
            else break;
        }
    }  
}

// Searching a value in the skip list
bool SkipList::Search(void *v, int (*compare)(void *, void*))
{

    // if there is nothing on the skip list
    if(this->first_array[0] == NULL) return false;

    SkipListNode* temp;
    // Starting from the top levels
    int i = this->levels-1;
    temp = this->first_array[i];

    // initializing the pathing from the first node of each level
    SkipListNode* prevnodearray[this->levels];
    for(int j = 0; j < levels; j++)
    {
        prevnodearray[j] = NULL;
    }

    while(i >= 0)
    { 
        // Checking whether the level is empty
        if(this->first_array[i] == NULL)
        {
            i--;
            temp = this->first_array[i];
        }
        else if(temp != NULL)
        {
            // we found it!!!
            if(compare(v, temp->get_value()) == 0)
            {
                return true;
            }
            // the given value is less than the current value we examine
            else if(compare(v, temp->get_value()) < 0)
            {
                // we go a level down if able starting from the previous node 
                // or from the first node of the previous level
                if((temp == this->first_array[i]) && (i > 0)) temp = this->first_array[i-1];
                else temp = prevnodearray[i];
                i--;
            }
            else
            {
                prevnodearray[i] = temp;
                // we reached the last node of the level
                if(temp->get_next(i) == NULL)
                {
                    i--;
                }    
                else temp = temp->get_next(i);
            }
        } 
    }
    // we found nothing
    return false;
}

// Removing a value from the skip list
void SkipList::Remove(void *v, int (*compare)(void *, void*))
{
    SkipListNode* temp;
    // Starting from the top levels
    int i = this->levels-1;
    temp = this->first_array[i];

    // if there is nothing on the skip list
    if(this->first_array[0] == NULL) return;

    // if the node is the first one from the list
    if(compare(v, this->first_array[0]->get_value()) == 0)
    {
        temp = this->first_array[0];
        while(i >= 0)
        {
            // checking if it is in other levels
            if((this->first_array[i] != NULL) && (compare(v, this->first_array[i]->get_value()) == 0))
            {
                if(this->first_array[i]->get_next(i)) this->first_array[i] = this->first_array[i]->get_next(i);
                else this->first_array[i] = NULL;
            }
            
            i--;
        }
        this->count--;
        delete temp;
        return;
    }

    // initializing the pathing from the first node of each level
    SkipListNode* prevnodearray[this->levels];
    for(int j = 0; j < levels; j++)
    {
        prevnodearray[j] = NULL;
    }

    while(i >= 0)
    { 
        // Checking whether the level is empty
        if(this->first_array[i] == NULL)
        {
            i--;
            temp = this->first_array[i];
        }
        else if(temp != NULL)
        {
            // the given value is less or equal than the current value we examine
            if(compare(v, temp->get_value()) <= 0)
            {
                // we go a level down if able starting from the previous node 
                // or from the first node of the previous level
                if((temp == this->first_array[i]) && (i > 0)) temp = this->first_array[i-1];
                else temp = prevnodearray[i];
                i--;
            }
            else
            {
                prevnodearray[i] = temp;
                // we reached the last node of the level
                if(temp->get_next(i) == NULL)
                {
                    i--;
                }    
                else temp = temp->get_next(i);
            }
        } 
    }

    // checking whether the node exists
    if(prevnodearray[0] == NULL) temp = this->first_array[0];
    else temp = prevnodearray[0]->get_next(0);
    
    if((temp == NULL) || (compare(v, temp->get_value()) != 0))
    {
        cout << "Value does not exist" << endl;
        return;
    }

    // removing the node starting from the highest possible level
    int level = this->levels-1;
    while(level >= 0)
    {
        // linking the previous node with the next one after the node to be removed is isolated
        if(this->first_array[level] != NULL) 
        {
            if(prevnodearray[level]->get_next(level) != NULL)
            {
                // checking if the node is the first of the current level
                if(temp == this->first_array[level])
                {
                    this->first_array[level] = temp->get_next(level);
                }
                else if(compare(v,prevnodearray[level]->get_next(level)->get_value()) == 0)
                {
                    prevnodearray[level]->set_next(level, temp->get_next(level));
                }
            }
            else if(temp == this->first_array[level])
            {
                this->first_array[level] = NULL;
            }
            else prevnodearray[level]->set_next(level, NULL);

        }
       level--;
    } 
    delete temp;
    this->count--;
}

// Printing the skip list
void SkipList::Print(void (*visit)(void*))
{  
    // printing every node of the list 
    SkipListNode* temp = this->first_array[0];
    while(temp != NULL)
    {
        visit(temp->get_value());
        cout << endl;
        temp = temp->get_next(0);
    }
}

// Returning the number of elements from the list
int SkipList::get_count(void) const
{
    return this->count;
}

// Returning the first node of the whole skip list
SkipListNode* SkipList::get_first() const
{
    return this->first_array[0];
}