#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct Class
{
 int term;
 string subject;
 string catalog;
 string letGrade;
 double numGrade;
 Class* next ;
};
typedef Class* ClassList;
struct Student
{
 string ID;
 ClassList ClassesTaken; // a linked list of Class objects
};
struct Course
{
 string subject;
 string catalog;
 double hours;
 string DR; // designation requirement
}; 

int main()
{
 int fish = 5;
 
 int *fishPointer = &fish;
 
 
 cout << fishPointer<<endl;
 
 istream HCInput, SDInput;
 
 vector <Course> MyVector;
 
 HCInput.open("HunterCourses.tsv")
 
 Course temp;
 while(!HCInput.eof())
 {
 
 HCInput >> temp.subject>>temp.catalog>>temp.hours>>temp.DR;
 push_back(temp);
  
 }
 
 return 0;
}
}
