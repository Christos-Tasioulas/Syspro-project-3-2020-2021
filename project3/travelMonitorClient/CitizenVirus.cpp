#include "CitizenVirus.h"

// Citizen Virus constructor
CitizenVirus::CitizenVirus(string virus, bool is, string date)
{
    this->virusName = virus;
    this->isVaccinated = is;
    this->dateVaccinated = date;
}

// Citizen Virus destructor
CitizenVirus::~CitizenVirus()
{
    this->virusName = "\0";
    this->isVaccinated = false;
    this->dateVaccinated = "\0";
}

// printing Citizen Virus 
void CitizenVirus::print(void)
{
    // space is a glitch breaker
    cout << this->virusName << " ";
    // if the citizen has been vaccined for the virus has a date
    //cout << "Vaccinated: ";
    if (this->isVaccinated == true)
    {
        cout << "YES" << " ";
        cout << this->dateVaccinated;
    }
    else cout << "NO";
}

// returning the name of the virus
string CitizenVirus::get_virus_name(void) const
{
    return this->virusName;
}

// returning whether the citizen was vaccinated or not
bool CitizenVirus::get_vaccination_state(void) const
{
    return this->isVaccinated;
}

// returning the vaccinaion date for the citizen
string CitizenVirus::get_date() const
{
    return this->dateVaccinated;
}

// the citizen has been vaccinated
void CitizenVirus::set_vaccinated_state(void)
{
    this->isVaccinated = true;
}

// setting the vaccination date
void CitizenVirus::set_date(string date)
{
    this->dateVaccinated = date;
}
