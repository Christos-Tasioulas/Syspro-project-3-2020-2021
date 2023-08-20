#include "CountryBlooms.h"
#include <cstring>

// Assistant functions

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

CountryBlooms::CountryBlooms(char* country, int s_fd, int r_fd)
{
    this->country = new char[strlen(country)+1];
    strcpy(this->country, country);

    this->r_fd = r_fd;
    this->s_fd = s_fd;    

    this->virus_bloom_list = new List();
}

CountryBlooms::~CountryBlooms()
{
    delete[] this->country;

    destroy_virus_bloom_list(this->virus_bloom_list);
}

// returns the country's name
char* CountryBlooms::get_country(void) const
{
    return this->country;
}

// returns the sending pipe's file descriptor that matches the country
int CountryBlooms::get_s_fd(void) const
{
	return this->s_fd;
}

// returns the sending pipe's file descriptor that matches the country
int CountryBlooms::get_r_fd(void) const
{
	return this->r_fd;
}

// returns the list with a bloom filter for each virus
List* CountryBlooms::get_virus_bloom_list(void) const
{
    return this->virus_bloom_list;
}

// changes the current list of bloom filters with the list given
void CountryBlooms::set_virus_bloom_list(List* list)
{
    this->virus_bloom_list = list;
}