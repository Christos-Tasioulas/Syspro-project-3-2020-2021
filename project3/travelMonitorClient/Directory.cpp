// FIle managing directories
#include "Interface.h"
#include <cstring>
#include <dirent.h>

// Assistant functions

// function to print directories
// void visit_directory(void* n)
// {
//     char* name = (char*) n;
//     cout << name;
// }

// function to compare directory names
int compare_names(const void* a, const void* b)
{
    char* name_a = (char*) a;
    char* name_b = (char*) b;
    return strcmp(name_a, name_b);
}

// Sorting alphabetically the files or subdirectories included in the drectory given and 
// Returning the list with the items
List* directory_sorting(string input_dir)
{
    DIR* dir;
    struct dirent* en;

    // opening the directory
    dir = opendir(input_dir.c_str());

    // error checking the directory
    if(!dir)
    {
        cout << "Error, directory does not exist" << endl;
        return NULL;
    }

    // creating a list for the subdirectories we will find
    List* directory_list = new List();

    // reading inside the directory
    while((en = readdir(dir)) != NULL)
    {
        string input_dir_copy = input_dir;

        char* directory = new char[strlen(en->d_name)+1];
        strcpy(directory, en->d_name);
        directory[strlen(en->d_name)] = '\0';

        // we are not interested in . and ..
        if(strcmp(directory, ".") && strcmp(directory, ".."))
        {
            input_dir_copy.append("/");
            string subdirectory(directory);
            input_dir_copy.append(subdirectory);

            // inserting the first element
            if(directory_list->get_size() == 0)
            {
                string* new_dir = new string(input_dir_copy);
                directory_list->ListInsertFirst(new_dir);
            }
            else
            {
                // a flag indicating if the directory was inserted before the last one 
                bool inserted = false;

                ListNode* temp = directory_list->get_first();
                ListNode* prev = NULL;

                while(temp != NULL)
                {
                    // checking if the value we are examining is lower alphabetically than the current's node value
                    string* value = (string *) temp->get_value();
                    if(strcmp(directory, value->c_str()) < 0)
                    {
                        // if yes we insert the value after the previous node
                        string* new_dir = new string(input_dir_copy);
                        directory_list->ListInsertAfter(new_dir, prev);
                        inserted = true;
                        break;
                    }
                    prev = temp;
                    temp = temp->get_next();
                }
                // inserting the node at the end of the list
                if(inserted == false)
                {
                    string* new_dir = new string(input_dir_copy);
                    directory_list->ListInsertLast(new_dir);
                } 
            }

        }

        
    }    

    // closing the directory
    closedir(dir);

    return directory_list;    
}