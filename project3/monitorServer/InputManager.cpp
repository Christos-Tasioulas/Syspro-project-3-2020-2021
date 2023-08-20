// C++ file to manage and convert user's input into the correct output
#include "Interface.h"
#include <ctime>

//global variable for the size of the file
extern int skip_size;

// assistant functions

void visit_citizen1(void* my_citizen_record)
{
    CitizenRecord* CR = (CitizenRecord*) my_citizen_record;
    cout << CR->get_id() << " ";
    cout << CR->get_firstname() << " ";
    cout << CR->get_lastname() << " "; 
    cout << CR->get_country() << " ";
    cout << CR->get_age();
}

void visit_citizen_virus1(void* my_citizen_virus)
{
    CitizenVirus* cv = (CitizenVirus*)my_citizen_virus;  
    cv->print();     
}

// comparing ids from the citizen records given
int compare_ids1(void* c1, void* c2)
{
    CitizenRecord* cr1 = (CitizenRecord*) c1;
    CitizenRecord* cr2 = (CitizenRecord*) c2;
    string s1 = cr1->get_id();
    string s2 = cr2->get_id();
    return atoi(s1.c_str()) - atoi(s2.c_str());
}

int compare_countries(void* v1, void* v2)
{
    string s1 = *((string *) v1);
    string s2 = *((string *) v2);
    return strcmp(s1.c_str(), s2.c_str());
}

void visit_country(void* v1)
{
    string s1 = *((string *) v1);
    cout << s1 << endl;   
}

// // examines the /vaccinatedStatusBloom commands
// void vaccineStatusBloom(char* c_input, List* citizen_list, List* virus_bloom_list)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string citizenID, virusName;

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);

//         // checking what argument do we have
//         if(i == 1)
//         {
//             citizenID = temp;
//         }
//         else if(i == 2)
//         {
//             virusName = temp;
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 2)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 2)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         // testing whether the citizen exists
//         if(id_exists(citizenID, citizen_list) == NULL)
//         {
//             cout << "Error, Citizen with id: " << citizenID <<" does not exist" << endl;
//             return;
//         }

//         CitizenRecord* CR = id_exists(citizenID, citizen_list);

//         // examining whether we know if the citizen has been vaccinated for the virus
//         if(virus_exists(virusName, CR) == NULL)
//         {
//             cout << "We don't know if the citizen with id " << citizenID << " is vaccinated for the virus " << virusName << endl;
//             return;
//         }

//         // testing whether a bloom filter for this virus exists
//         if(virus_has_a_bloom_filter(virusName, virus_bloom_list) == NULL)
//         {
//             cout << "Error, Bloom Filter for virus: " << virusName << " does not exist" << endl;
//             return;
//         }

//         // Searching the vaccine status of the citizen for the virus
//         BloomFilter* bf = virus_has_a_bloom_filter(virusName, virus_bloom_list);
//         char* c_id = new char[citizenID.length() + 1];
//         strcpy(c_id, citizenID.c_str());
//         if((bf->Search((unsigned char*) c_id)) == true) 
//         {
//             cout << "MAYBE" << endl;
//         }
//         else cout << "NOT VACCINATED" << endl;
//         delete[] c_id;
//     }
// }

// // examines the /vaccinatedStatus commands
// void vaccineStatus(char* c_input, List* citizen_list, List* virus_skip_list)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string citizenID, virusName = "";

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);

//         // checking what argument do we have
//         if(i == 1)
//         {
//             citizenID = temp;
//         }
//         else if(i == 2)
//         {
//             virusName = temp;
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 2)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 1)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         // testing whether the citizen exists
//         if(id_exists(citizenID, citizen_list) == NULL)
//         {
//             cout << "Error, Citizen with id: " << citizenID <<" does not exist" << endl;
//             return;
//         }

//         CitizenRecord* CR = id_exists(citizenID, citizen_list);
//         List* cvl = CR->get_virus_list();

//         // a virus has not been given
//         if(virusName == "")
//         {
//             cvl->print(visit_citizen_virus1); 
//         }
//         else
//         {
//             // examining whether there is a skip list for the virus
//             if(virus_has_skip_lists(virusName, virus_skip_list) == false)
//             {
//                 cout << "Error, List for virus: " << virusName << " does not exist" << endl;
//                 return;
//             }

//             SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//             SkipList* sl2 = virus_has_a_skip_list(virusName, virus_skip_list, "NO");

//             // examining whether we know if the citizen has been vaccinated for the virus
//             if(virus_exists(virusName, CR) == NULL)
//             {
//                 cout << "We don't know if the citizen with id " << citizenID << " is vaccinated for the virus " << virusName << endl;
//                 return;
//             }
//             // searching if the citizen has been vaccinated or not
//             if(sl1->Search(CR, compare_ids1) == true)
//             {
//                 CitizenVirus* CV = virus_exists(virusName, CR);  
//                 cout << "VACCINATED ON " << CV->get_date() << endl;
//             }
//             else if(sl2->Search(CR, compare_ids1) == true)
//             {
//                 cout << "NOT VACCINATED" << endl;
//             }
//             else
//             {
//                 cout << "We don't know if the citizen with id " << citizenID << " is vaccinated for the virus " << virusName << endl;
//                 return;
//             }
//         }
//     }
// }

// // supporting function to handle the /populationStatus command
// void populationStatus_assisstsnt(string country, string virusName, string date1, string date2, List* virus_skip_list)
// {
//     // counting vaccinated, vaccinated between given dates and total people recorded with the virus given
//     int vaccinated_counter = 0;
//     int vaccinated_counter_between_dates = 0;
//     int total = 0;

//     SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//     SkipListNode* node = sl1->get_first();

//     // searching the vaccinated people skip list for people from the country given in order to count them
//     while(node != NULL)
//     {
//         CitizenRecord* CR = (CitizenRecord*) node->get_value();
//         if(CR->get_country() == country) 
//         {
//             vaccinated_counter++;
//             total++;
//             CitizenVirus* CV = virus_exists(virusName, CR);
//             // the citizen has been vaccinated between the dates
//             if((compare_dates(date1, CV->get_date()) >= 0) && (compare_dates(CV->get_date(), date2) >= 0)) vaccinated_counter_between_dates++;
//         }
//         node = node->get_next(0);
//     }

//     SkipList* sl2 = virus_has_a_skip_list(virusName, virus_skip_list, "NO");
//     node = sl2->get_first();

//     // searching the non vaccinated people skip list for people from the country given in order to count them
//     while(node != NULL)
//     {
//         CitizenRecord* CR = (CitizenRecord*) node->get_value();
//         if(CR->get_country() == country) total++;
//         node = node->get_next(0);
//     }

//     // we need the percentage of people vaccinated between the dates given and the total from the country
//     float percent;
//     if(total != 0) percent = ((float) vaccinated_counter_between_dates) / ((float) total);
//     else percent = 0; // we can't divide by zero
//     cout << country << " " << vaccinated_counter_between_dates << " " << 100.0 * percent << "%" << endl;
// }

// // examines the /populationStatus commands
// void populationStatus(char* c_input, List* virus_skip_list)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string country = "", virusName, date1, date2;
//     bool country_exists = true; 

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);
        
//         // testing whether this is a vrius or a country
//         if(i == 1)
//         {
//             country_exists = virus_has_skip_lists(temp, virus_skip_list);
//             // this is a country only if it is not a virus
//             if(country_exists == true) country_exists = false;
//             else country_exists = true;
//         } 

//         // we have a [country] argument
//         if(country_exists == true)
//         {
//             // checking what argument do we have
//             if(i == 1)
//             {
//                 country = temp;
//             }
//             else if(i == 2)
//             {
//                 virusName = temp;
//             }
//             else if(i == 3)
//             {
//                 date1 = temp;
//             }
//             else if(i == 4)
//             {
//                 date2 = temp;
//             }
//         }
//         else
//         {
//             // checking what argument do we have
//             if(i == 1)
//             {
//                 virusName = temp;
//             }
//             else if(i == 2)
//             {
//                 date1 = temp;
//             }
//             else if(i == 3)
//             {
//                 date2 = temp;
//             }
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 4)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 3)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         // Checking if the virus exits in the database
//         if(virus_has_skip_lists(virusName, virus_skip_list) == false)
//         {
//             cout << "Error, Skip List for virus " << virusName << " has not been found" << endl;
//             return;
//         }

//         // Checking if the date is valid
//         if ((date_valid(date1) == false) || (date_valid(date2) == false))
//         {
//             cout << "Invalid date has been given" << endl;
//             return;
//         }
        
//         // date2 > date1 always
//         if(compare_dates(date1, date2) < 0)
//         {
//             cout << "Error, " << date2 << " comes before " << date1 << endl;
//             return;
//         }

//         if(country_exists == true)
//         {
//             // calling the assistant function directly
//             populationStatus_assisstsnt(country, virusName, date1, date2, virus_skip_list);
//         }
//         else
//         {
//             // storing all the countries in a list
//             List* countries = new List(); 

//             SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//             SkipListNode* node = sl1->get_first();

//             // traversing the vaccinated skip list for the virusName to find countries
//             while(node != NULL)
//             {
//                 CitizenRecord* CR = (CitizenRecord*) node->get_value();
//                 string temp_country = CR->get_country();
//                 // we insert each country once
//                 if(countries->ListSearch(&temp_country, compare_countries) == false)
//                 {
//                     string* new_country = new string(temp_country);
//                     countries->ListInsertLast(new_country);
//                 }
//                 node = node->get_next(0);     
//             }

//             // calling the function for each country in the list
//             ListNode* temp = countries->get_first();
//             while(temp != NULL)
//             {
//                 string temp_country = *((string*) temp->get_value());
//                 populationStatus_assisstsnt(temp_country, virusName, date1, date2, virus_skip_list);
//                 temp = temp->get_next();
//             }

//             list_destroy_countries(countries);
//         }
//     }
// }

// // supporting function to handle the /popStatusByAge command
// void popStatusByAge_assisstsnt(string country, string virusName, string date1, string date2, List* virus_skip_list)
// {
//     // counting vaccinated, vaccinated between given dates and total people recorded with the virus given
//     // for each of the 4 age groups
//     int vaccinated_counter[4] = {0, 0, 0, 0};
//     int vaccinated_counter_between_dates[4] = {0, 0, 0, 0};
//     int total[4] = {0, 0, 0, 0};

//     SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//     SkipListNode* node = sl1->get_first();

//     // searching the vaccinated people skip list for people from the country given in order to count them
//     while(node != NULL)
//     {
//         CitizenRecord* CR = (CitizenRecord*) node->get_value();
//         if(country.compare(CR->get_country()) == 0) 
//         {
//             // grouping the people by age group
//             int age = CR->get_age();
//             if((age >= 0) && (age < 20))
//             {
//                 vaccinated_counter[0]++;
//                 total[0]++;
//             }
//             else if((age >= 20) && (age < 40))
//             {
//                 vaccinated_counter[1]++;
//                 total[1]++;
//             }
//             else if((age >= 40) && (age < 60))
//             {
//                 vaccinated_counter[2]++;
//                 total[2]++;
//             }
//             else if((age >= 60) && (age <= 80))
//             {
//                 vaccinated_counter[3]++;
//                 total[3]++;
//             }
//             CitizenVirus* CV = virus_exists(virusName, CR);
//             // the citizen has been vaccinated between the dates
//             if((compare_dates(date1, CV->get_date()) >= 0) && (compare_dates(CV->get_date(), date2) >= 0)) 
//             {
//                 // grouping the people by age group
//                 if((age >= 0) && (age < 20))
//                 {
//                     vaccinated_counter_between_dates[0]++;
//                 }
//                 else if((age >= 20) && (age < 40))
//                 {
//                     vaccinated_counter_between_dates[1]++;            
//                 }
//                 else if((age >= 40) && (age < 60))
//                 {
//                     vaccinated_counter_between_dates[2]++;
//                 }
//                 else if((age >= 60) && (age <= 80))
//                 {
//                     vaccinated_counter_between_dates[3]++;
//                 } 
//             }
//         }
//         node = node->get_next(0);
//     }

//     SkipList* sl2 = virus_has_a_skip_list(virusName, virus_skip_list, "NO");
//     node = sl2->get_first();

//     // searching the non vaccinated people skip list for people from the country given in order to count them
//     while(node != NULL)
//     {
//         CitizenRecord* CR = (CitizenRecord*) node->get_value();
//         if(country.compare(CR->get_country()) == 0) 
//         {
//             // grouping the people by age group    
//             int age = CR->get_age();   
//             if((age >= 0) && (age < 20))
//             {
//                 total[0]++;
//             }
//             else if((age >= 20) && (age < 40))
//             {
//                 total[1]++;            
//             }
//             else if((age >= 40) && (age < 60))
//             {
//                 total[2]++;
//             }
//             else if((age >= 60) && (age <= 80))
//             {
//                 total[3]++;
//             }           
//         }
//         node = node->get_next(0);
//     }

//     cout << country << endl;
//     for(int i = 0; i < 4; i++)
//     {
//         //cout << total[i] << endl; 
//         // we need the percentage of people vaccinated between the dates given and the total from the country
//         // divided by age group (0-20),(20-40),(40-60),(60-80)
//         float percent;
//         if(total[i]!=0) percent = ((float) vaccinated_counter_between_dates[i]) / ((float) total[i]);
//         else percent = 0; // we can't divide by zero
//         cout << i*20 << "-" << i*20+20 << " " << vaccinated_counter_between_dates[i] << " " << 100.0 * percent << "%" << endl;
//     }
    
// }

// // examines the /popStatusByAge commands
// void popStatusByAge(char* c_input, List* virus_skip_list)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string country = "", virusName, date1, date2;
//     bool country_exists = true;

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);

//         // testing whether this is a vrius or a country
//         if(i == 1) 
//         {         
//             country_exists = virus_has_skip_lists(temp, virus_skip_list);
//             // this is a country only if it is not a virus
//             if(country_exists == true) country_exists = false;
//             else country_exists = true;
//         }

//         // we have a [country] argument
//         if(country_exists == true)
//         {
//             // checking what argument do we have
//             if(i == 1)
//             {
//                 country = temp;
//             }
//             else if(i == 2)
//             {
//                 virusName = temp;
//             }
//             else if(i == 3)
//             {
//                 date1 = temp;
//             }
//             else if(i == 4)
//             {
//                 date2 = temp;
//             }
//         }
//         else
//         {
//             // checking what argument do we have
//             if(i == 1)
//             {
//                 virusName = temp;
//             }
//             else if(i == 2)
//             {
//                 date1 = temp;
//             }
//             else if(i == 3)
//             {
//                 date2 = temp;
//             }
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 4)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 3)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         // Checking if the virus exits in the database
//         if(virus_has_skip_lists(virusName, virus_skip_list) == false)
//         {
//             cout << "Error, Skip List for virus " << virusName << " has not been found" << endl;
//             return;
//         }

//         // Checking if the date is valid
//         if ((date_valid(date1) == false) || (date_valid(date2) == false))
//         {
//             cout << "Invalid date has been given" << endl;
//             return;
//         }
        
//         // date2 > date1 always
//         if(compare_dates(date1, date2) < 0)
//         {
//             cout << "Error, " << date2 << " comes before " << date1 << endl;
//             return;
//         }

//         if(country_exists == true)
//         {
//             // calling the assistant function directly
//             popStatusByAge_assisstsnt(country, virusName, date1, date2, virus_skip_list);
//         }
//         else
//         {
//             // storing all the countries in a list
//             List* countries = new List(); 

//             SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//             SkipListNode* node = sl1->get_first();

//             // traversing the vaccinated skip list for the virusName to find countries
//             while(node != NULL)
//             {
//                 CitizenRecord* CR = (CitizenRecord*) node->get_value();
//                 string temp_country = CR->get_country();
//                 // we insert each country once
//                 if(countries->ListSearch(&temp_country, compare_countries) == false)
//                 {
//                     string* new_country = new string(temp_country);
//                     countries->ListInsertLast(new_country);
//                 }
//                 node = node->get_next(0);     
//             }

//             // calling the function for each country in the list
//             ListNode* temp = countries->get_first();
//             while(temp != NULL)
//             {
//                 string temp_country = *((string*) temp->get_value());
//                 popStatusByAge_assisstsnt(temp_country, virusName, date1, date2, virus_skip_list);
//                 temp = temp->get_next();
//             }

//             list_destroy_countries(countries);
//         }
//     }
        
// }

// // examines the /insertCitizenRecord commands
// void insertCitizenRecord(char* c_input, List* citizen_list, List* virus_bloom_list, List* virus_skip_list, int bloom_size)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string record_array[8]; 

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);
//         // the arguments will be stored in an array
//         if((i>0) && (i<=8)) record_array[i-1] = temp;
//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 8)
//     {
//         cout << "Too many arguments!" << endl;
//         return;
//     }
//     else if(i < 7)
//     {
//         cout << "Too few arguments!" << endl;
//         return;
//     }
//     else
//     {
        
//         // Checking whether the potential record is valid or not
//         int valid = is_valid(record_array, citizen_list);

//         CitizenRecord* CR;

//         if(valid == 0)   
//         {
//             CR = id_exists(record_array[0], citizen_list);
//             int age = atoi(record_array[4].c_str());

//             SkipList* sl = virus_has_a_skip_list(record_array[5], virus_skip_list, "YES");

//             // checking if we have the same record as the one we found
//             if(CR->get_firstname() != record_array[1]) record_error(record_array);
//             else if(CR->get_lastname() != record_array[2]) record_error(record_array);
//             else if(CR->get_country() != record_array[3]) record_error(record_array);
//             else if(CR->get_age() != age) record_error(record_array);
//             // checking if the citizen has been vaccinated for the virus before
//             else if(sl->Search(CR, compare_ids1) == true)
//             {
                
//                 CitizenVirus* CV = virus_exists(record_array[5], CR);
//                 cout << "ERROR: CITIZEN " << CR->get_id() << " ALREADY VACCINATED ON: " << CV->get_date() << endl;
                
//             }
//             return;
//         }
//         else{

//             // if this is a new record
//             if(valid == 2)
//             {
//                 // creating a record with the array
//                 CR = new CitizenRecord(record_array);

//                 // inserting the record on a list with citizens
//                 citizen_list->ListInsertLast(CR);
//             }
//             else if(valid == 1) 
//             {
//                 // citizen's id exists
//                 CR = id_exists(record_array[0], citizen_list);
//             }

//             // creating a bloom filter for the virus independent of the citizen's vaccination
//             if(virus_has_a_bloom_filter(record_array[5], virus_bloom_list) == NULL)
//             {
//                 VirusBloom* vb = new VirusBloom(record_array[5], bloom_size);
//                 virus_bloom_list->ListInsertLast(vb);
//             }

//             // creating two skip lists for the virus (vaccinated and not vaccinated people)
//             // independent of the citizen's vaccination
//             if(virus_has_skip_lists(record_array[5], virus_skip_list) == false)
//             {
//                 VirusSkip* vs1 = new VirusSkip(record_array[5], "YES", skip_size);
//                 virus_skip_list->ListInsertLast(vs1);
//                 VirusSkip* vs2 = new VirusSkip(record_array[5], "NO", skip_size);
//                 virus_skip_list->ListInsertLast(vs2);
//             }

//             // coverting the id to c_string
//             string id = CR->get_id();
//             char* c_id = new char[id.length() + 1];
//             strcpy(c_id, id.c_str());

//             // inserting the citizen id in the BloomFilter only if they are vaccinated
//             if(citizen_is_vaccinated(record_array[5], CR) == true)
//             {
//                 SkipList* sl = virus_has_a_skip_list(record_array[5], virus_skip_list, "YES");
//                 BloomFilter* bf = virus_has_a_bloom_filter(record_array[5], virus_bloom_list);
//                 sl->Insert(CR, compare_ids1); 
//                 bf->Insert((unsigned char*) c_id);    

//             }
//             else
//             {
//                 string id = CR->get_id();
//                 SkipList* sl = virus_has_a_skip_list(record_array[5], virus_skip_list, "NO");
//                 sl->Insert(CR, compare_ids1);
//             }

//             delete[] c_id; 
//         }    
//     }
// }

// // returns the current date
// string get_current_date(void)
// {
//     // getting the current time
//     time_t now = time(0);
//     tm *ltm = localtime(&now);

//     // we should add 1900 to the year and 1 to the month for the correct results
//     int yyyy = 1900 + ltm->tm_year;
//     int mm = 1 + ltm->tm_mon;
//     int dd = ltm->tm_mday;

//     // we should make a string out of the current day
//     string day = to_string(dd);
//     // making the string valid if it is less than 1 digit
//     if(dd < 10)
//     {
//         string new_day = "0";
//         new_day.append(day);
//         day = new_day;
//     }  

//     // we should make a string out of the current month
//     string month = to_string(mm);
//     // making the string valid if it is less than 1 digit
//     if(mm < 10)
//     {
//         string new_month = "0";
//         new_month.append(month);
//         month = new_month;
//     }

//     // we should make a string out of the current year
//     string year = to_string(yyyy);
    
//     // appending the three strings and some '-' in between to form the date string
//     string date;
//     date.append(day);
//     date.append("-");
//     date.append(month);
//     date.append("-");
//     date.append(year);

//     return date;
// }

// // examines the /vaccinateNow commands
// void vaccinateNow(char* c_input, List* citizen_list, List* virus_bloom_list, List* virus_skip_list, int bloom_size)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string citizenID, firstName, lastName, country, age, virusName;

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);

//         // checking what argument do we have
//         if(i == 1)
//         {
//             citizenID = temp;
//         }
//         else if(i == 2)
//         {
//             firstName = temp;
//         }
//         else if(i == 3)
//         {
//             lastName = temp;
//         }
//         else if(i == 4)
//         {
//             country = temp;
//         }
//         else if(i == 5)
//         {
//             age = temp;
//         }
//         else if(i == 6)
//         {
//             virusName = temp;
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     // examining whether the number of arguments is exactly what we need
//     if(i > 6)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 6)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         CitizenRecord* CR = id_exists(citizenID, citizen_list);
//         // testing whether the citizen exists
//         if(CR == NULL)
//         {
//             cout << "Error, Citizen with id: " << citizenID <<" does not exists" << endl;
//             return;
//         }

//         // testing whether the whole command is valid
//         if(CR->get_firstname() != firstName)
//         {
//             cout << "Invalid Firstname" << endl;
//             return;
//         }

//         if(CR->get_lastname() != lastName)
//         {
//             cout << "Invalid Lastname" << endl;
//             return;
//         }

//         if(CR->get_country() != country)
//         {
//             cout << "Invalid Country" << endl;
//             return;
//         }

//         if(CR->get_age() != atoi(age.c_str()))
//         {
//             cout << "Invalid Age" << endl;
//             return;
//         }

//         CitizenVirus* CV;

//         // inserting the virus to the citizen's list
//         if(virus_exists(virusName, CR) == NULL)
//         {
//             CV = new CitizenVirus(virusName, false, "");
//             CR->get_virus_list()->ListInsertLast(CV);
//             if(virus_has_skip_lists(virusName, virus_skip_list) == true)
//             {
//                 SkipList* sl2 = virus_has_a_skip_list(virusName, virus_skip_list, "NO");
//                 // inserting the citizen in the non vaccinated skip list for the virus
//                 sl2->Insert(CR, compare_ids1);
//             }
//         }
 
//         // creating a bloom filter for the virus independent of the citizen's vaccination
//         if(virus_has_a_bloom_filter(virusName, virus_bloom_list) == NULL)
//         {
//             VirusBloom* vb = new VirusBloom(virusName, bloom_size);
//             virus_bloom_list->ListInsertLast(vb);
//         }

//         // creating two skip lists for the virus (vaccinated and not vaccinated people)
//         // independent of the citizen's vaccination
//         if(virus_has_skip_lists(virusName, virus_skip_list) == false)
//         {
//             VirusSkip* vs1 = new VirusSkip(virusName, "YES", skip_size);
//             virus_skip_list->ListInsertLast(vs1);
//             VirusSkip* vs2 = new VirusSkip(virusName, "NO", skip_size);
//             virus_skip_list->ListInsertLast(vs2);
//             // inserting the citizen in the non vaccinated skip list for the virus
//             vs2->get_skip_list()->Insert(CR, compare_ids1);
//         }

//         CV = virus_exists(virusName, CR);

        

//         // checking if the citizen has been already vaccinated
//         SkipList* sl1 = virus_has_a_skip_list(virusName, virus_skip_list, "YES");
//         if(sl1->Search(CR, compare_ids1) == true)
//         {
//             cout << "ERROR: CITIZEN " << CR->get_id() << " ALREADY VACCINATED ON: " << CV->get_date() << endl;
//             return;
//         }

//         // inserting the citizen id in the BloomFilter and the SKipList only if they are vaccinated
//         SkipList* sl2 = virus_has_a_skip_list(virusName, virus_skip_list, "NO");
//         if(sl2->Search(CR, compare_ids1) == true)
//         {
//             // removing the record from the skiplist of non vaccinated people if possible
//             sl2->Remove(CR, compare_ids1);
            
//             string date = get_current_date();

//             // changing the state in the respective record
//             CV->set_vaccinated_state();
//             CV->set_date(date);

//             // inserting the record in the vaccinated people virus skip list
//             sl1->Insert(CR, compare_ids1);

//             // changing the state in the respective bloom filter
//             BloomFilter* bf = virus_has_a_bloom_filter(virusName, virus_bloom_list);
//             string id = CR->get_id();
//             char* c_id = new char[id.length() + 1];
//             strcpy(c_id, id.c_str());
//             bf->Insert((unsigned char*) c_id);
//             delete[] c_id;
//         }
//     }
// }

// // examines the /list_nonVaccinated_Persons commands
// void list_nonVaccinated_Persons(char* c_input, List* citizen_list, List* virus_skip_list)
// {
//     char* cs;
//     cs = strtok(c_input, " ");

//     string virusName;

//     if(cs == NULL)
//     {
//         return;
//     }
//     int i = 0;
//     while(1)
//     {
//         string temp(cs);

//         // checking what argument do we have
//         if(i == 1)
//         {
//             virusName = temp;
//         }

//         cs = strtok(NULL, " ");
//         if(cs == NULL)
//         {
//             break;
//         }
//         i++;       
//     }

//     if(i > 1)
//     {
//         cout << "Too many arguments!" << endl;
//     }
//     else if(i < 1)
//     {
//         cout << "Too few arguments!" << endl;
//     }
//     else
//     {
//         if(virus_has_a_skip_list(virusName, virus_skip_list, "NO") == NULL)
//         {
//             cout << "Error, Skip List for virus " << virusName << " has not been found" << endl;
//             return;
//         }
//         else
//         {
//             SkipList* sl = virus_has_a_skip_list(virusName, virus_skip_list, "NO");
//             if(sl->get_count() == 0) cout << "All people we know have been vaccinated" << endl;
//             else sl->Print(visit_citizen1);
//         }
        
//     }
// }

// responds to /travelRequest commands
void travelRequest(char* c_input, Stats* s, int sock)
{
    char* cs;
    cs = strtok(c_input, " ");

    string citizenID, date, countryFrom, countryTo, virusName;

    if(cs == NULL)
    {
        return;
    }
    int i = 0;
    while(1)
    {
        string temp(cs);

        // checking what argument do we have
        if(i == 1)
        {
            citizenID = temp;
        }
        else if(i == 2)
        {
            date = temp;
        }
        else if(i == 3)
        {
            countryFrom = temp;
        }
        else if(i == 4)
        {
            countryTo = temp;
        }
        else if(i == 5)
        {
            virusName = temp;
        }

        cs = strtok(NULL, " ");
        if(cs == NULL)
        {
            break;
        }
        i++;       
    }

    // examining whether the number of arguments is exactly what we need
    if(i > 5)
    {
        cout << "Too many arguments!" << endl;
    }
    else if(i < 5)
    {
        cout << "Too few arguments!" << endl;
    }
    else
    {
    }
}

// responds to /addVaccinationRecord commands
void addVaccinationRecords(char* c_input, Stats* s, List* paths, int sock)
{
    char* cs;
    cs = strtok(c_input, " ");

    string country;

    if(cs == NULL)
    {
        return;
    }
    int i = 0;
    while(1)
    {
        string temp(cs);

        if(i == 1)
        {
            country = temp;
        }

        cs = strtok(NULL, " ");
        if(cs == NULL)
        {
            break;
        }
        i++;       
    }

    // examining whether the number of arguments is exactly what we need
    if(i > 1)
    {
        cout << "Too many arguments!" << endl;
    }
    else if(i < 1)
    {
        cout << "Too few arguments!" << endl;
    }
    else
    {
        string exists = "Exists";
        bool c_e = country_exists(country, paths);
        if(c_e == false)
        {
            exists = "Does not exist";
        }

        if(write_string(sock, exists) == false)
        {
            cout << "Error at InputManager.cpp at line 1183" << endl;
            return;
        }

        if(c_e == true)
        {
            List* files = open_directories(paths);
            new_files_evaluation(files);
            CyclicBuffer* cb = s->get_cyclic_buffer();
            producer(cb, files);
            List* virus_bloom_list = s->get_virus_bloom_list();
            int bloomsize = s->get_size_Of_Bloom();
            int sb = send_bloomfilters(virus_bloom_list, sock, bloomsize);
            if(sb != 0)
            {
                cout << "Error at InputManager.cpp at line 1197" << endl;
            }
        }

    }
}

// responds to /searchVaccinationStatus commands
void searchVaccinationStatus(char* c_input, Stats* s, int sock)
{
    char* cs;
    cs = strtok(c_input, " ");

    string citizenID;

    if(cs == NULL)
    {
        return;
    }
    int i = 0;
    while(1)
    {
        string temp(cs);

        if(i == 1)
        {
            citizenID = temp;
        }

        cs = strtok(NULL, " ");
        if(cs == NULL)
        {
            break;
        }
        i++;       
    }

    // examining whether the number of arguments is exactly what we need
    if(i > 1)
    {
        cout << "Too many arguments!" << endl;
    }
    else if(i < 1)
    {
        cout << "Too few arguments!" << endl;
    }
    else
    {
    }
}

// managing the input given from the user
// the lists as arguments are the ones to check the existence and the 
// validity of the arguments given
void input_manager(string input, Stats* s, List* paths, int sock)
{
    char* c_input = new char [input.length() + 1];
    strcpy(c_input, input.c_str());

    // copying the command in order not to lose it
    char* c_input_copy = new char [input.length() + 1];
    strcpy(c_input_copy, c_input);

    // determining what we will do with the given command
    char* argument;
    argument = strtok(c_input_copy, " ");

    if(argument == NULL)
    {
        return;
    }

    string value(argument);

    if(value == "/travelRequest")
    {
        travelRequest(c_input, s, sock);
    }
    else if(value == "/addVaccinationRecords")
    {
        addVaccinationRecords(c_input, s, paths, sock);
    }
    else if(value == "/searchVaccinationStatus")
    {
        searchVaccinationStatus(c_input, s, sock);
    }
    else 
    {
        cout << "Command not found!" << endl;
    }

    delete[] c_input;
    delete[] c_input_copy;
}