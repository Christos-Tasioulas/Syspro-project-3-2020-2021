// This file is where all the memory used for complex data structures will be freed
#include "Interface.h"

// Destroys the list after releasing all the memory the directories are occupying inside the list
void list_destroy_directories(List* directories)
{
	ListNode* node;
    node = directories->get_first();
    while(node != NULL)
    {
        string* directory;
        directory = (string*) node->get_value();
        delete directory;
        node = node->get_next();
    }
    delete directories;
}

// destroying everything the given virus-bloom filter list includes
void destroy_virus_bloom_list(List* virus_bloom_list)
{
    ListNode* node;
    node = virus_bloom_list->get_first();
    while(node != NULL)
    {
        VirusBloom* VB;
        VB = (VirusBloom*) node->get_value();
        delete VB;
        node = node->get_next();
    }
    delete virus_bloom_list;
}

// destroying everything the given travel request list includes
void destroy_travel_requests_list(List* travel_request_list)
{
    ListNode* node;
    node = travel_request_list->get_first();
    while(node != NULL)
    {
        TravelRequest* TR;
        TR = (TravelRequest*) node->get_value();
        delete TR;
        node = node->get_next();
    }
    delete travel_request_list;   
}