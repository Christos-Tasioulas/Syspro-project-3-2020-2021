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

// // destroying everything the given countries stats list includes
// void destroy_country_stats_list(List* country_stats_list)
// {
//     ListNode* node;
//     node = country_stats_list->get_first();
//     while(node != NULL)
//     {
//         CountryStats* CS;
//         CS = (CountryStats*) node->get_value();
//         delete CS;
//         node = node->get_next();
//     }
//     delete country_stats_list;
// }

// destroying everything the given list of filenames includes
void list_destroy_files(List* files)
{
	ListNode* node;
    node = files->get_first();
    while(node != NULL)
    {
        string* file;
        file = (string*) node->get_value();
        delete file;
        node = node->get_next();
    }
    delete files; 
}