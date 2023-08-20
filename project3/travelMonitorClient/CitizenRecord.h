#ifndef CITIZENRECORD
#define CITIZENRECORD
#include "CitizenVirus.h"
#include <cstdlib>
#include "List.h"

class CitizenRecord
{
private:
    string citizenID;
    string firstname;
    string lastname;
    string country;
    unsigned short age;
    // List with viruses, yes or no vaccinated and vaccination date
    List* cvl_ptr;

public:
    // Citizen Record constructor
    // record array of strings as input
    CitizenRecord(string* record_array);
    // Citizen Record destructor
    ~CitizenRecord();
    // printing Citizen Record
    void print(void);
    // returning citizen's id
    string get_id() const;
    // returning citizen's first name
    string get_firstname() const;
    // returning citizen's last name
    string get_lastname() const;
    // returning citizen's country of origin
    string get_country() const;
    // returning citizen's age
    unsigned short get_age() const;
    // returning the virus list of the citizen
    List* get_virus_list(void) const;
};

#endif