#pragma once

#include <ctime>
#include <string>

class Student
{
public:
    Student();
    virtual ~Student();
    
    int getId() { return Id; }
    void setId(int id){ Id = id; }

    std::string getFirstName(){ return FirstName; }
    void setFirstName(std::string firstName){ FirstName = firstName; }

    std::string getLastName(){ return LastName; }
    void setLastName(std::string lastName){ LastName = lastName; }

    std::string getSex(){ return Sex; }
    void setSex(std::string sex){ Sex = sex; }

    std::string getSchool(){ return School; }
    void setSchool(std::string school){ School = school; }

    std::string getCampusAddress(){ return CampusAddress; }
    void setCampusAddress(std::string campusAddress){ CampusAddress = campusAddress; }

    std::string getHomeAddress(){ return HomeAddress; }
    void setHomeAddress(std::string homeAddress){ HomeAddress = homeAddress; }

    std::string getProvinceCity(){ return ProvinceCity; }
    void setProvinceCity(std::string provinceCity){ ProvinceCity = provinceCity; }

    std::tm getAdmissionTime(){ return AdmissionTime; }
    void setAdmissionTime(std::tm admissionTime){ AdmissionTime = admissionTime; }

    //std::set stores its values in a sorted binary tree,
    //so it needs to know how to compare the values it holds.
    //By default it uses std::less as a comparison function,
    //which for un - specialized user defined types tries to call operator<.
    //So, the easiest way to tell the set how to compare your objects is
    //to define an operator< for your class :
    bool operator<(const Student& s) const
    {
        return Id < s.Id;
    }

private:
    int Id;
    std::string FirstName;
    std::string LastName;
    std::string Sex;
    std::string School;
    std::string CampusAddress;
    std::string HomeAddress;
    std::string ProvinceCity;
    std::tm AdmissionTime;
};
