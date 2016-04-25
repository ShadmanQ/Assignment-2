#include <iostream>
#include <fstream>
#include <string>

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
 
 return 0;
}
}
