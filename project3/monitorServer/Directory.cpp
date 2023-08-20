#include "Interface.h"
#include <dirent.h>

// Assistant functions

// visiting a citizen to print
// void visit_citizen(void *my_citizen)
// { 
//     CitizenRecord *c = (CitizenRecord *) my_citizen;
//     c->print();
// }

// // visiting an id from the citizen record given
// void visit_id(void *cr)
// {
//     CitizenRecord* CR = (CitizenRecord*) cr; 
//     string id = CR->get_id();
//     cout << id;
// }

// visiting a virus bloom filter to print
// void visit_virus_bloom(void *my_virus_bloom)
// { 
//     VirusBloom *vb = (VirusBloom *) my_virus_bloom;
//     cout << vb->get_virus_name() << endl;
//     vb->get_bloom_filter()->Print();
// }

// // visiting a virus bloom filter to print
// void visit_virus_skip(void *my_virus_skip)
// { 
//     VirusSkip *vs = (VirusSkip *) my_virus_skip;
//     cout << vs->get_virusname() << endl;
//     if(vs->get_vaccination_state() == true) cout << "Vaccinated People IDs:" << endl;
//     else cout << "Not Vaccinated People IDs:" << endl;
//     vs->get_skip_list()->Print(visit_id);
// }

// Reads and opens all the directories in the given list and their files 
// The names are needed for the countrystats class
// Returns a list with all the files we read
List* open_directories(List* directories_list)
{

    // int skip_size = 0;

    ListNode* node = directories_list->get_first();
    List* files = new List();

	while(node != NULL)
	{

        // int file_size = 0;

		string directory = *((string*) node->get_value());
		//cout << directory << endl;

		DIR* dir;
		struct dirent* en;
		
		dir=opendir(directory.c_str());
		
		// error checking the directory
		if(!dir)
		{
			cout << "Error, directory does not exist" << endl;
			return NULL;
		}

		
		// string country=directory;
        // country = country.substr(PATHLEN, country.length()-PATHLEN);
		
        // CountryStats* cs = new CountryStats(directory);

		// reading inside the directory
		while((en = readdir(dir)) != NULL)
		{
            if(strcmp(en->d_name, ".") && strcmp(en->d_name, ".."))
            {
                // getting the size of each file before reading inside
                string filename(en->d_name);
                string directory_copy = directory;
                directory_copy.append("/"); 
                directory_copy.append(filename); 

                char* c_filename = new char[directory_copy.length()+1];
                strcpy(c_filename, directory_copy.c_str());
                //file_size+=get_file_size(c_filename);
                //cout << directory_copy << endl;
                string* filename_p = new string(directory_copy);
                // inserting the file at the end of the list
                files->ListInsertLast(filename_p);

            }

		}	

        closedir(dir);
        node = node->get_next();
    }
	
	return files;
}

//     // determining the size of the skip list from the size of all the files
    //     skip_size = (int) log2(file_size);

    //     // opening the directory's files
    //     ListNode* temp = files->get_first();

    //     // reading each files records and inserting it to the correct country
    //     while(temp != NULL)
    //     {
    //        char* filename = ((char*) temp->get_value());
    //        open_citizen_file(filename, cs, bloomsize, skip_size);
    //        temp = temp->get_next();
    //     }	
		
	// 	country_stats_list->ListInsertLast(cs);
		
    //     // destroying the list with the files
    //     list_destroy_files(files);
    //     node = node->get_next();	

	// }
	
    // //ListNode* node;
    // node = country_stats_list->get_first();

    // while(node != NULL)
    // {
    //     CountryStats* cs = ((CountryStats*) node->get_value());

    //     List* virus_bloom_list = cs->get_virus_bloom_list();

    //     ListNode* temp = virus_bloom_list->get_first();

    //     while (temp != NULL)
    //     {

    //         // Writing to parent "Take bloomfilters"
    //         // bool w = write_string(pipes_fds[1], "Take bloomfilters");
    //         // if(w == false)
    //         // {
    //         //     cout << "Error writing at the pipe" << endl;
    //         //     return 137;
    //         // }

    //         VirusBloom* vb = ((VirusBloom*) temp->get_value());

    //         // receiving "OK" from parent
    //         //char* ok = read_string(pipes_fds[0]);

    //         // Sending the virus name to the parent
    //         string virusname = vb->get_virus_name();
            
    //         bool w = write_string(pipes_fds[1], virusname);
    //         if(w == false)
    //         {
    //             cout << "Error writing at the pipe" << endl;
    //             return false;
    //         }    
            
    //         //cout << virusname << endl;
            
    //         char* message = read_string(pipes_fds[0]);
    //         if(message == NULL)
    //         {
    //             cout << "Error reading the pipe" << endl;
    //             return false;
    //         }
            
    //         cout << message << endl;

    //         //BloomFilter* bf = vb->get_bloom_filter();

    //         temp = temp->get_next();
    //     }

	// bool ready = write_string(pipes_fds[1], "No viruses left");
	// if(ready == false)
	// {
	// 	cout << "Error writing at the pipe" << endl;
    //     return false;
	// }	
	
	// char* message = read_string(pipes_fds[0]);
	// if(message == NULL)
	// {
	// 	cout << "Error reading the pipe" << endl;
	// 	return false;
	// }
	
	// cout << message << endl;