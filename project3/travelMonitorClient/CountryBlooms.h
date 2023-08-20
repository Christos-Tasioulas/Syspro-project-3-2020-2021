#ifndef COUNTRYBLOOMS
#define COUNTRYBLOOMS
#include "VirusBloom.h"
#include "List.h"

class CountryBlooms
{
    private:
        char* country;
        int s_fd;
        int r_fd;
        List* virus_bloom_list;
    public:
        // Constructor
        CountryBlooms(char* country, int s_fd, int r_fd);
        // Destructor
        ~CountryBlooms();
        // returns the country's name
        char* get_country(void) const;
		// returns the sending pipe's file descriptor that matches the country
		int get_s_fd(void) const;
		// returns the sending pipe's file descriptor that matches the country
		int get_r_fd(void) const;
        // returns the list with a bloom filter for each virus
        List* get_virus_bloom_list(void) const;
        // changes the current list of bloom filters with the list given
        void set_virus_bloom_list(List* list);
};

#endif