#include "CitizenRecord.h"

// Assisstant functions
void visit_citizen_virus(void* my_citizen_virus)
{
    CitizenVirus* cv = (CitizenVirus*)my_citizen_virus;  
    cv->print();     
}

// Citizen Record constructor
CitizenRecord::CitizenRecord(string* record_array)
{
    this->citizenID = record_array[0];
    this->firstname = record_array[1];
    this->lastname = record_array[2];
    this->country = record_array[3];
    this->age = atoi(record_array[4].c_str());
    CitizenVirus* cv;
    // if citizen vaccinated for this virus then it has a date
    if (record_array[6] == "YES")
    {   
        cv = new CitizenVirus(record_array[5], true, record_array[7]);
    } 
    else cv = new CitizenVirus(record_array[5], false, "");
    this->cvl_ptr = new List();
    this->cvl_ptr->ListInsertLast(cv);
    //cout << "record with id " << this->citizenID << " constructed" << endl; 
}

// Citizen Record destructor
CitizenRecord::~CitizenRecord()
{
    //cout << "record with id " << this->citizenID << " to be destroyed" << endl;
    this->citizenID = "\0";
    this->firstname = "\0";
    this->lastname = "\0";
    this->country = "\0";

    // destroying the list with the viruses of each citizen
    delete this->cvl_ptr;
}

// printing Citizen Record
void CitizenRecord::print(void)
{
    // space is a glitch breaker
    cout << "ID:" << this->citizenID << endl;
    cout << "First Name:" << this->firstname << endl;
    cout << "Last Name:" << this->lastname << endl;
    cout << "Country:" << this->country << endl;
    cout << "Age:" << this->age << endl << endl;
    cout << "Viruses Vaccinated:" << endl; 
    // printing the virus list
    this->cvl_ptr->print(visit_citizen_virus);
    cout << "____________________" << endl;
    
}

// returning citizen's id
string CitizenRecord::get_id() const
{
    return this->citizenID;
}

// returning citizen's first name
string CitizenRecord::get_firstname() const
{
    return this->firstname;
}

// returning citizen's last name
string CitizenRecord::get_lastname() const
{
    return this->lastname;
}

// returning citizen's country of origin
string CitizenRecord::get_country() const
{
    return this->country;
}

// returning citizen's age
unsigned short CitizenRecord::get_age() const
{
    return this->age;
}

// returning the virus list of the citizen
List* CitizenRecord::get_virus_list() const
{
    return this->cvl_ptr;
}