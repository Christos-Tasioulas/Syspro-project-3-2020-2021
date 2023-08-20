#ifndef CITIZENVIRUS
#define CITIZENVIRUS
#include <iostream>
#include <string>

using namespace std;

class CitizenVirus
{
    private:
        string virusName;
        bool isVaccinated;
        string dateVaccinated;

    public:
        // default date is "" if not vaccinated
        // Citizen Virus constructor
        CitizenVirus(string virus, bool is, string date="");
        // Citizen Virus destructor
        ~CitizenVirus();
        // printing Citizen Virus 
        void print(void);
        // the citizen has been vaccinated
        void set_vaccinated_state(void);
        // setting the vaccination date
        void set_date(string date);
        // returning the name of the virus
        string get_virus_name(void) const;
        // returning whether the citizen was vaccinated or not
        bool get_vaccination_state(void) const;
        // returning the vaccinaion date for the citizen
        string get_date() const;

};

#endif