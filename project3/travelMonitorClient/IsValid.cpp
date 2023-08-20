// C++ file to check whether input files and records are valid
#include "Interface.h"
#include <cstring>

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