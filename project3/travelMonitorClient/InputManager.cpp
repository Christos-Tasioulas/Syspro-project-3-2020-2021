// C++ file to manage and convert user's input into the correct output
#include "Interface.h"
#include <cstring>
#include <ctime>

// assistant functions

// responds to /travelRequest commands
void travelRequest(char* c_input, List* travel_request_list, List* virus_bloom_list, int bloom_size, int* socks, int numMonitors)
{
    char* c_input_copy = new char[strlen(c_input) + 1];
    strcpy(c_input_copy, c_input);

    char* cs;
    cs = strtok(c_input_copy, " ");

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
        delete[] c_input_copy;
    }
    else if(i < 5)
    {
        cout << "Too few arguments!" << endl;
        delete[] c_input_copy;
    }
    else
    {
    }
}

// responds to /travelStats commands
void travelStats(char* c_input, List* travel_request_list, List* virus_bloom_list)
{
    char* cs;
    cs = strtok(c_input, " ");

    string virusName, date1, date2, country = "";

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
            virusName = temp;
        }
        else if(i == 2)
        {
            date1 = temp;
        }
        else if(i == 3)
        {
            date2 = temp;
        }
        else if(i == 4)
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
    if(i > 4)
    {
        cout << "Too many arguments!" << endl;
    }
    else if(i < 3)
    {
        cout << "Too few arguments!" << endl;
    }
    else
    {
        // checking if the virus exists
        if(virus_has_a_bloom_filter(virusName, virus_bloom_list) == NULL)
        {
            cout << "Error virus does not exist" << endl;
            return;
        }

        // checking if the dates are valid
        if((date_valid(date1) == false) || (date_valid(date2) == false))
        {
            cout << "Error dates are not valid" << endl;
            return; 
        }

        // checking if [date1, date2] can exist
        if(compare_dates(date1, date2) < 0)
        {
            cout << "[date1, date2] is impossible" << endl;
            return;
        }

        int total_requests = 0, accepted = 0, rejected = 0;
        ListNode* node = travel_request_list->get_first();
        while(node != NULL)
        {
            TravelRequest* TR = (TravelRequest*) node->get_value();

            if(TR->get_virus() == virusName)
            {
                string date = TR->get_date();
                if((compare_dates(date1, date) >= 0) && (compare_dates(date, date2) >= 0))
                {
                    if((country == "") || (country == TR->get_country()))
                    {
                        total_requests++;
                        if(TR->get_state() == "ACCEPTED")
                        {
                            accepted++;
                        }
                        else if(TR->get_state() == "REJECTED")
                        {
                            rejected++;
                        }
                    }
                }
            }

            node = node->get_next();
        }

        cout << "TOTAL REQUESTS: " << total_requests << endl;
        cout << "ACCEPTED: " << accepted << endl;
        cout << "REJECTED: " << rejected << endl;
    }
}

// responds to /addVaccinationRecord commands
void addVaccinationRecords(char* c_input, List* virus_bloom_list, int bloom_size, int* socks, int numMonitors)
{
    char* c_input_copy = new char[strlen(c_input) + 1];
    strcpy(c_input_copy, c_input);

    char* cs;
    cs = strtok(c_input_copy, " ");

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
        delete[] c_input_copy;
    }
    else if(i < 1)
    {
        cout << "Too few arguments!" << endl;
        delete[] c_input_copy;
    }
    else
    {
        for(int i=0; i<numMonitors; i++)
        {
            // sending the command to the servers
            string input(c_input);
            if(write_string(socks[i], input) == false)
            {
                cout << "Error at InputManager.cpp in line 223" << endl;
                delete[] c_input_copy;
                return;
            }

            char* country_exists = read_string(socks[i]);
            if(country_exists == NULL)
            {
                cout << "Error at InputManager.cpp in line 223" << endl;
                delete[] c_input_copy;
                return;
            }
            else if(!strcmp(country_exists, "Exists"))
            {
                receive_bloomfilters(virus_bloom_list, socks[i], bloom_size);
                delete[] c_input_copy;
                return;
            }
        }
    }

    
}

// responds to /searchVaccinationStatus commands
void searchVaccinationStatus(char* c_input, int* socks, int numMonitors)
{
    char* c_input_copy = new char[strlen(c_input) + 1];
    strcpy(c_input_copy, c_input);

    char* cs;
    cs = strtok(c_input_copy, " ");

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
        delete[] c_input_copy;
    }
    else if(i < 1)
    {
        cout << "Too few arguments!" << endl;
        delete[] c_input_copy;
    }
    else
    {
    }
}

// managing the input given from the user
// the lists as arguments are the ones to check the existence and the 
// validity of the arguments given
void input_manager(string input, List* travel_request_list, List* virus_bloom_list, int bloom_size, int* socks, int numMonitors)
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
        travelRequest(c_input, travel_request_list, virus_bloom_list, bloom_size, socks, numMonitors);
    }
    else if(value == "/travelStats")
    {
        travelStats(c_input, travel_request_list, virus_bloom_list);        
    }
    else if(value == "/addVaccinationRecords")
    {
        addVaccinationRecords(c_input, virus_bloom_list, bloom_size, socks, numMonitors);
    }
    else if(value == "/searchVaccinationStatus")
    {
        searchVaccinationStatus(c_input, socks, numMonitors);
    }
    else 
    {
        cout << "Command not found!" << endl;
    }

    delete[] c_input;
    delete[] c_input_copy;
}