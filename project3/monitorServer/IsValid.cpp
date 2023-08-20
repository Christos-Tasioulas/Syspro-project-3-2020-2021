// C++ file to check whether input files and records are valid
#include "Interface.h"

int compare_strings(void* v1, void* v2)
{
    string s1 = *((string*) v1);
    string s2 = *((string*) v2);
    return strcmp(s1.c_str(), s2.c_str());
}

//confirming the record is invalid
void record_error(string* record_array)
{
    //cout << "ERROR IN RECORD:" << record_array[0] << endl;
    return;
}

// checking whether the given potential record attributes
// are valid according to a given list of citizen records
// returns: 
// >2 if the record is new, 
// >1 if the record already eixsts but not the virus
// >0 if the record is invalid
int is_valid(string* record_array, List* citizen_list)
{
    // If the citizen is not vaccinated for the virus but a date exists
    if(record_array[6] == "NO" && record_array[7] != "")
    {
        return 0;
    }

    // If the citizen is vaccinated for the virus but a date does not exist
    if(record_array[6] == "YES" && record_array[7] == "")
    {
        return 0;
    }
    
    ListNode* node;
    node = citizen_list->get_first();
    while(node != NULL)
    {
        CitizenRecord* CR = (CitizenRecord *) node->get_value();

        // if the id or the age does not exist
        if((record_array[0] == "") || (record_array[4] == ""))
        {
            return 0;
        }

        // if the age is smaller than 0 or greater than 120
        int age = atoi(record_array[4].c_str());
        if(age < 0 && age > 120)
        {
            return 0;
        }

        // if we have found the id already existing in the list
        if(record_array[0] == CR->get_id())
        {
            List* virus_list;
            virus_list = CR->get_virus_list();

            // but the firstname is different or does not exist
            if((record_array[1] != CR->get_firstname()) || (record_array[1] == ""))
            {
                return 0;
            }
            // or the lastname is different or does not exist
            else if((record_array[2] != CR->get_lastname()) || (record_array[2] == ""))
            {
                return 0;
            }
            // or the country is different or does not exist
            else if((record_array[3] != CR->get_country()) || (record_array[3] == ""))
            {
                return 0;
            }
            // or the age is different 
            else if(age != CR->get_age())
            {
                return 0;
            }

            // Now we have to check the virus 
            ListNode* vnode;
            vnode = virus_list->get_first();

            // If the date itself is invalid
            if((record_array[6] == "YES") && (date_valid(record_array[7]) == false))
            {
                return 0;
            }

            // Checking whether the virus exists in the citizen's virus list
            while(vnode != NULL)
            {
                CitizenVirus* CV = (CitizenVirus *) vnode->get_value();

                // The potential record is a duplicate
                if(record_array[5] == CV->get_virus_name()) 
                {
                    return 0;
                }

                vnode = vnode->get_next();
            }

            // Inserting the new virus on the citizen's virus list
            CitizenVirus* CV;
            if(record_array[6] == "YES")
            {
                CV = new CitizenVirus(record_array[5], true, record_array[7]);
            }
            else CV = new CitizenVirus(record_array[5], false, "");
            virus_list->ListInsertLast(CV);
            return 1;
            
        }
        node = node->get_next();
    }

    // the record is valid
    return 2;
}

// checks whether the date given is valid
bool date_valid(string date)
{
    // breaking the date string into 3 segments with the character '-' determining day, month and year
    char* c_date = new char[date.length() + 1];
    strcpy(c_date, date.c_str());
    char* cs;
    cs = strtok(c_date, "-");

    char dd[3], mm[3], year[5];

    if(cs == NULL)
    {
        return false;
    }
    int i = 0;
    while(1)
    {
        // the first one is the day
        if(i == 0)
        {
            strcpy(dd, cs);
        } 
        // the second one is the month
        else if(i == 1)
        {
            strcpy(mm, cs);
        }
        // the third one is the year
        else if(i == 2)
        {
            strcpy(year, cs);
        }

        cs = strtok(NULL, "-");
        if(cs == NULL)
        {
            break;
        }
        i++;  
    }
    delete[] c_date;

    // bool is_valid = true;
    // if we have more or less than 2 '-' the date is invalid
    if(i != 2) return false;

    // if the day has more than 2 characters the date is invalid
    if(strlen(dd) != 2) return false;
    // same goes to month
    else if(strlen(mm) != 2) return false;
    // the year should have 5 characters because it includes the '\0' character
    else if((strlen(year) != 5) && (strlen(year) != 4)) return false;

    int day = atoi(dd);
    int month = atoi(mm);
    int y = atoi(year);

    // we speculate that each month has 30 days in average
    if((day < 1) || (day > 30)) return false;
    // each year has 12 months
    else if((month < 1) || (month > 12)) return false;
    // we will start counting the years from 1970
    else if(y < 1970) return false;

    return true;
}



// compares two dates
int compare_dates(string date1, string date2)
{
    char* c_date1 = new char[date1.length() + 1];
    strcpy(c_date1, date1.c_str());
    char* cs;
    cs = strtok(c_date1, "-");

    char dd1[3], mm1[3], yyyy1[5];

    if(cs == NULL)
    {
        return 0;
    }
    int i = 0;
    while(1)
    {
        // the first one is the day
        if(i == 0)
        {
            strcpy(dd1, cs);
        } 
        // the second one is the month
        else if(i == 1)
        {
            strcpy(mm1, cs);
        }
        // the third one is the year
        else if(i == 2)
        {
            strcpy(yyyy1, cs);
        }

        cs = strtok(NULL, "-");
        if(cs == NULL)
        {
            break;
        }
        i++;  
    }

    char* c_date2 = new char[date2.length() + 1];
    strcpy(c_date2, date2.c_str());
    cs = strtok(c_date2, "-");

    char dd2[3], mm2[3], yyyy2[5];

    if(cs == NULL)
    {
        return false;
    }
    i = 0;
    while(1)
    {
        // the first one is the day
        if(i == 0)
        {
            strcpy(dd2, cs);
        } 
        // the second one is the month
        else if(i == 1)
        {
            strcpy(mm2, cs);
        }
        // the third one is the year
        else if(i == 2)
        {
            strcpy(yyyy2, cs);
        }

        cs = strtok(NULL, "-");
        if(cs == NULL)
        {
            break;
        }
        i++;  
    }

    int day1 = atoi(dd1);
    int month1 = atoi(mm1);
    int year1 = atoi(yyyy1);

    int day2 = atoi(dd2);
    int month2 = atoi(mm2);
    int year2 = atoi(yyyy2);

    delete[] c_date1;
    delete[] c_date2;

    if((year1 == year2) && (month1 == month2)) return day2-day1;
    else if(year1 == year2) return month2-month1;
    else return year2-year1;
}

// examining whether the virus given has a bloom filter in the list
BloomFilter* virus_has_a_bloom_filter(string virus, List* virus_bloom_list)
{
    // checking whether the list is empty
    if(virus_bloom_list->get_first() == NULL) return NULL;
    ListNode* node;
    node = virus_bloom_list->get_first();
    while(node != NULL)  
    {
        VirusBloom* vb = (VirusBloom*) node->get_value();
        if(vb->get_virus_name() == virus)
        {
            return vb->get_bloom_filter();
        }
        node = node->get_next();
    }

    return NULL;
}

// examining whether the virus given has skip lists in the list given
bool virus_has_skip_lists(string virus, List* virus_skip_list)
{
    // checking whether the list is empty
    if(virus_skip_list->get_first() == NULL) return false;
    ListNode* node;
    node = virus_skip_list->get_first();
    while(node != NULL)  
    {
        VirusSkip* vb = (VirusSkip*) node->get_value();
        // the vaccinated and non vaccinated skip list for each virus will be made one after another
        if(vb->get_virusname() == virus)
        {
            return true;
        }
        node = node->get_next();
    }

    return false;
}

// examining whether the virus given has a skip list in the list given
// returns the skiplist depending the yesno argument itself if it exists
// if yesno == yes returns the skip list for the vaccinated people
// otherwise returns the skip list for the non vaccinated people
SkipList* virus_has_a_skip_list(string virus, List* virus_skip_list, string yesno)
{
    // checking whether the list is empty
    if(virus_skip_list->get_first() == NULL) return NULL;

    // translating the yes no string to bool
    bool is_vaccinated;
    if(yesno == "YES") is_vaccinated = true;
    else if(yesno == "NO") is_vaccinated = false; 
    else return NULL;

    ListNode* node;
    node = virus_skip_list->get_first();
    while(node != NULL)  
    {
        VirusSkip* vb = (VirusSkip*) node->get_value();
        if(vb->get_virusname() == virus)
        {
            if(vb->get_vaccination_state() == is_vaccinated)
            {
                return vb->get_skip_list();
            }
        }
        node = node->get_next();
    }

    return NULL;
}

// testing whether the citizen id given exists in the list given
CitizenRecord* id_exists(string id, List* citizen_list)
{
    ListNode* node = citizen_list->get_first();
    while(node != NULL)
    {
        CitizenRecord* CR = (CitizenRecord*) node->get_value();
        if(id == CR->get_id())
        {
            return CR;
        }
        node = node->get_next();
    }
    return NULL;
}

// testing whether the citizen has been recorded with the virus given
CitizenVirus* virus_exists(string virus, CitizenRecord* CR)
{
    List* cvl = CR->get_virus_list();
    ListNode* node = cvl->get_first();

    while(node !=  NULL)
    {
        CitizenVirus* CV = (CitizenVirus*) node->get_value();
        if(CV->get_virus_name() == virus)
        {
            return CV;
        }
        node = node->get_next();
    }
    return NULL;

}

// returns whether the citizen has been vaccinated or not
bool citizen_is_vaccinated(string virus, CitizenRecord* CR)
{
    List* cvl = CR->get_virus_list();
    // checking whether the list is empty
    if(cvl == NULL) return false;
    ListNode* node = cvl->get_first();
    while(node != NULL)
    {    
        CitizenVirus* CV = (CitizenVirus*) node->get_value();
        if(CV->get_virus_name() == virus)
        {
            return CV->get_vaccination_state();
        }
        node = node->get_next();
    }
    return false;
}

// Finding if a country exists by checking a list of paths
bool country_exists(string country, List* paths)
{
    ListNode* node = paths->get_first();
    while(node != NULL)
    {    
        string path = *((string*) node->get_value());

        // turning a path into a country
        path = path.substr(PATHLEN, path.length()-PATHLEN);
        
        if(path == country)
        {
            return true;
        }
        node = node->get_next();
    }
    return false;
}

// evaluating if the files on the list are not and removing those that are not
void new_files_evaluation(List* files)
{
    ListNode* node = files->get_first();
    while(node != NULL)
    {
        string* file = (string*) node->get_value();
        char number = file->at(file->length()-5);
        if((number == '1') || (number == '2') || (number == '3'))
        {
            files->Remove(file, compare_strings);
            delete file;
        }
        node = node->get_next();
    }
}