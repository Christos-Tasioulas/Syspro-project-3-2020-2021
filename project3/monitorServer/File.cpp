#include "Interface.h"
#include <fstream>

//global variable for the size of the file
//int skip_size;

// Assistant functions

// comparing ids from the citizen records given
int compare_ids(void* c1, void* c2)
{
    CitizenRecord* cr1 = (CitizenRecord*) c1;
    CitizenRecord* cr2 = (CitizenRecord*) c2;
    string s1 = cr1->get_id();
    string s2 = cr2->get_id();
    return atoi(s1.c_str()) - atoi(s2.c_str());
}

// Returns the number of lines in the file
int get_file_size(string filename)
{
    string temp;

    ifstream citizenRecordsFileSize(filename);
    int file_size = 0;
    while (getline(citizenRecordsFileSize, temp))
    {
        file_size++;
    }
    return file_size;
}

// Opens the file given and saves the citizens, bloom filters and skip lists in the lists given
void open_citizen_file(string filename, Stats* s, int bloomsize, int skip_size)
{
    List* citizen_list = s->get_citizen_list();
    List* virus_bloom_list = s->get_virus_bloom_list();
    List* virus_skip_list = s->get_virus_skip_list();

    //cout << filename << endl;

    ifstream citizenRecordsFile(filename);
    string temp;
    string citizen_record[8];

    //cout << filename << endl;

    // using a while loop together with the getline() function to read the file line by line
    while (getline(citizenRecordsFile, temp)) 
    {
        
        // initialize the array with the records
        for(int n = 0; n < 8; n++)
        {
            citizen_record[n] = ""; 
        }

        // converting the string to c_string in order to token it
        char* record;
        record = new char [temp.length()+1];
        strcpy(record, temp.c_str());
        
        // seperating each line according to spaces
        // spaces determine each member of the class CitizenRecord
        char* cs;
        cs = strtok(record, " ");

        if(cs == NULL)
        {
            continue;
        }
        int i = 0;
        while(1)
        {
            string temp(cs);
            citizen_record[i] = temp;
            cs = strtok(NULL, " ");
            if(cs == NULL)
            {
                break;
            }
            i++;       
        }
		
        int valid = is_valid(citizen_record, citizen_list);
        if(valid == 0) record_error(citizen_record);  
        else 
        {
            CitizenRecord* CR;

            // if this is a new record
            if(valid == 2)
            {
                // creating a record with the array
                CR = new CitizenRecord(citizen_record);

                // inserting the record on a list with citizens
                citizen_list->ListInsertLast(CR);
            }
            else if(valid == 1) 
            {
                // citizen's id exists
                CR = id_exists(citizen_record[0], citizen_list);
            }

            // creating a bloom filter for the virus independent of the citizen's vaccination
            if(virus_has_a_bloom_filter(citizen_record[5], virus_bloom_list) == NULL)
            {
                VirusBloom* vb = new VirusBloom(citizen_record[5], bloomsize);
                virus_bloom_list->ListInsertLast(vb);
            }

            // creating two skip lists for the virus (vaccinated and not vaccinated people)
            // independent of the citizen's vaccination
            if(virus_has_skip_lists(citizen_record[5], virus_skip_list) == false)
            {
                VirusSkip* vs1 = new VirusSkip(citizen_record[5], "YES", skip_size);
                virus_skip_list->ListInsertLast(vs1);
                VirusSkip* vs2 = new VirusSkip(citizen_record[5], "NO", skip_size);
                virus_skip_list->ListInsertLast(vs2);
            }

            // coverting the id to c_string
            string id = CR->get_id();
            char* c_id = new char[id.length() + 1];
            strcpy(c_id, id.c_str());

            // inserting the citizen id in the BloomFilter only if they are vaccinated
            if(citizen_is_vaccinated(citizen_record[5], CR) == true)
            {
                SkipList* sl = virus_has_a_skip_list(citizen_record[5], virus_skip_list, "YES");
                BloomFilter* bf = virus_has_a_bloom_filter(citizen_record[5], virus_bloom_list);
                sl->Insert(CR, compare_ids); 
                bf->Insert((unsigned char*) c_id);    

            }
            else
            {
                string id = CR->get_id();
                SkipList* sl = virus_has_a_skip_list(citizen_record[5], virus_skip_list, "NO");
                sl->Insert(CR, compare_ids);
            }

            delete[] c_id;   

        } 

        delete[] record;

    }

    return;
}