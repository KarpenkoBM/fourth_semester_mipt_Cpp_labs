#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace nlohmann;

struct Student
{
    std::string name;
    std::string surname;
    int age = 0;
    int year = 0;
    float AverageMark = 0.0;
};

std::istream& operator >> (std::istream &in,  Student &s)
{
    in >> s.surname >>  s.name>> s.age>>s.year>>s.AverageMark;
    return in;
}
std::ostream& operator << (std::ostream &out,  const Student &s)
{
    out << s.surname <<' ' <<  s.name<< ' '<<s.age<< ' '<< s.year<<' '<<s.AverageMark;
    return out;
}

int main()
{
    int n = 0;
    std::cin>> n;
    Student s[n];
     std::filesystem::create_directory("students");
    for (auto i = 0; i < n; i++)
    {
        std::cin>> s[i];
        json object;
        object["surname"] = s[i].surname;
        object["name"] = s[i].name;
        object["age"] = s[i].age;
        object["year"] = s[i].year;
        object["AverageMark"] = s[i].AverageMark;
        std::ofstream file("students/student "+s[i].surname+".json");
        file << object;
    }

}
