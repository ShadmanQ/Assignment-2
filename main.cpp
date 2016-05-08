#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
Name: Shadman Quazi
Class: CSCI 135

Description: This program uses two files to determine GPA's of a group of students. The first file is of courses, this file is loaded into a large piece of data to be stored and modified later. Same situation with the student file, however before each student gets loaded into a seperate piece of data, a list of classes a particular student is created and linked to that students ID. once both students and courses are loaded into the computer memory, they are used to calculate each students GPA, CS specific GPA, and a percentage of Non Liberal Arts. As these three things are created, they along with the Student ID are put into a new output file.

*/

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

void LoadCourseData(ifstream& x, vector <Course>& y);
void LoadStudentData (ifstream& IN, vector<Student>& sVec);
void add_class(int tm, string sub, string cat, string lGrade, double numGrades, ClassList& headp);
void create_student(Student& temp, string& object, int& t, string& s, string& c, string& LG, double& NG);
int validate(string x, vector<Student>& sVec);
void sort_Vec(vector <Student>& sVec);
void out_put(vector <Student>& x, vector <Course>& y, ofstream& OUT);
void Traverse(ClassList& TheList);
void Calc_GPA(double& Grades, ClassList ThisList, vector <Course> CV);
void CSCI_GPA_Calc(double& Grades, ClassList ThisList, vector <Course> CV);
void NLA_Calc(double& ptage, ClassList thislist, vector <Course> y);

int main()
{

ifstream HCInput, SDInput;
ofstream SDoutput;
vector <Course> CourseVector;
vector <Student> StudentVector;
LoadCourseData(HCInput, CourseVector);
LoadStudentData(SDInput, StudentVector);
sort_Vec(StudentVector);
cout<<StudentVector.size();
out_put(StudentVector,CourseVector, SDoutput);
HCInput.close();
SDInput.close();
SDoutput.close();

 return 0;
}

void LoadCourseData(ifstream& x, vector <Course>& y)//Load of the course data vector via file input
{
	x.open("HunterCourses.tsv");
	Course tempCourse;
	while(x >> tempCourse.subject>>tempCourse.catalog>>tempCourse.hours>>tempCourse.DR)//allows a full student to be made
	{
		 y.push_back(tempCourse);
	}

}


int validate(string x, vector<Student>& sVec)//to check if the current student is present in the student vector
{
	int i;
	for (int i = 0; i <= sVec.size(); i++)
	{
		if (sVec[i].ID == x)
		{
            		return i;//returns the specific index of the student in the student vector, allowing add_class to act on this specific index
		}
	}
	return -8675309;//return value for if the student isn't present in Student Vector, allowing the create_student function to initialize in main block
}

void add_class (ClassList& thingamajig, int tm, string id, string sub, string cat, string lg, double ng)//creates a node to be linked with a previously existing list dependent on the studend
{
ClassList NewClass;
NewClass = new Class;//a new node, with garbage to be filled
NewClass-> term= tm;
NewClass->subject = sub;
NewClass->catalog = cat;
NewClass->letGrade = lg;
NewClass->numGrade = ng;
NewClass->next = thingamajig;
thingamajig = NewClass;
}


void create_student(vector <Student>& studVec, Student& aStud, ClassList& aList, int& tm, string& id, string& sub, string& cat, string& lg, double& ng)//uses objects that were streamed in by the LoadStudentData function
{
	aStud.ID = id;
	ClassList firstClass;
	firstClass = new Class;//creation of new Class Node to be filled
	Class* top = new Class;
	firstClass->term = tm;
	firstClass->subject = sub;
	firstClass->catalog = cat;
	firstClass->letGrade = lg;
	firstClass->numGrade = ng;
	firstClass->next = NULL;//this block effectively creates a "data filled" head node for an eventual linked list, hence the NULL.
	aList=firstClass;
	studVec.push_back(aStud);
}

void LoadStudentData (ifstream& IN, vector<Student>& sVec)//to create the Student Vector via file input and a student vector present in the main block
{
IN.open("StudentData.tsv");
int stud_term;
string stud_ID, stud_subject, stud_catalog, stud_letGrade;
double stud_numGrade;
Student first_stud;
IN>>stud_ID>>stud_term>>stud_subject>>stud_catalog>>stud_letGrade>>stud_numGrade;
create_student(sVec, first_stud, first_stud.ClassesTaken, stud_term, stud_ID, stud_subject, stud_catalog, stud_letGrade, stud_numGrade);//used to put an initial element in the Vector
while(IN>>stud_ID>>stud_term>>stud_subject>>stud_catalog>>stud_letGrade>>stud_numGrade)
	{
		int check = validate(stud_ID, sVec);
		if (check < 0)//i.e. the student doesn't exist in the vector
		{
			Student temp_dude;
			create_student(sVec, temp_dude, temp_dude.ClassesTaken, stud_term, stud_ID, stud_subject, stud_catalog, stud_letGrade, stud_numGrade);
		}
		if (check >= 0)//i,.e. the student does exist in the vector
		{
			add_class(sVec[check].ClassesTaken, stud_term, stud_ID, stud_subject, stud_catalog, stud_letGrade, stud_numGrade);
		}

	}
}

void sort_Vec(vector <Student>& sVec)//to put the vector in numerical order by EMPL ID
{
    for(int i=0; i<sVec.size(); i++)
	{
	        for(int j=i; j<sVec.size(); j++)
		{
	            if(sVec[i].ID>sVec[j].ID)
			{
	                Student tempStudent;
	                tempStudent = sVec[i];
	                sVec[i]=sVec[j];
	                sVec[j]=tempStudent;
			}
		}
	}
}


void CSCI_GPA_Calc(double& CS_Grades, ClassList ThisList, vector <Course> CV)//creates a CS specific GPA via pass by reference of a temp CSCI_GPA in the main block
{
double hours=0.0;
double creds = 0.0;
double courseWeight = 0.0;
Class* traverse = ThisList;//pointer used to access the data of each node in ThisList
while(traverse!=NULL)
{
	for (int j = 0; j <CV.size(); j++)
		{
			if ((traverse->subject == "CSCI") &&(traverse->subject == CV[j].subject) && (traverse->catalog == CV[j].catalog) && (traverse->numGrade != -1))
				{
				courseWeight=((traverse->numGrade)*CV[j].hours);
				creds +=courseWeight;
				hours +=CV[j].hours;
				}
		}//this loop is used to find the total number CS_credits earned by a stuend and the number hours this student took part in
traverse=traverse->next;//to move to the next node
}
CS_Grades =creds/hours;//where the GPA is actually calculated
}

void Calc_GPA(double& Grades, ClassList ThisList, vector <Course> CV)//creates an overall GPA via pass-by reference of a temp GPA in the main block
{
double hours=0.0;
double creds = 0.0;
double courseWeight = 0.0;
Class* traverse = ThisList;//pointer used to access the data of each node
while(traverse!=NULL)
{
	for (int j = 0; j <CV.size(); j++)
		{
			if ((traverse->subject == CV[j].subject) && (traverse->catalog == CV[j].catalog) && (traverse->numGrade != -1))
				{
				courseWeight=((traverse->numGrade)*(CV[j].hours));
				creds +=courseWeight;
				hours +=CV[j].hours;
				}
		}//this loop is used to find the total number credits earned by a stuend and the number hours this student took part in
traverse=traverse->next;// to move to the next node
}
Grades =creds/hours;//where the GPA is actually calculated
}


void NLA_Calc(double& ptage, ClassList thisList, vector <Course> y)
{

double tot_hours = 0.0;
double NL_hours =0.0;
Class* traverse = thisList;
while(traverse!=NULL)
	{
		for (int  i = 0; i<y.size(); i++)
		{
			if((y[i].subject == traverse->subject) && (y[i].catalog) == (traverse->catalog))
				{
					tot_hours+=y[i].hours;
					if (y[i].DR == "RNL" || y[i].DR == "MNL" || y[i].DR == "GNL")
					{
						NL_hours+=y[i].hours;
					}
				}

		}
		traverse = traverse->next;
	}
	ptage = (NL_hours/tot_hours)*100;

}
void out_put(vector <Student>& x, vector <Course>& y, ofstream& OUT)//final output function
{

OUT.open("StudentSummary.tsv");//file output creation
double GPA = 0.0,  CSCI_GPA = 0.0, NLA_percentage = 0.0;//temp variables to be manipulated by the void functions below
for (int i=0; i<x.size();i++)
{

Calc_GPA(GPA, x[i].ClassesTaken, y);
CSCI_GPA_Calc(CSCI_GPA, x[i].ClassesTaken, y);
NLA_Calc(NLA_percentage, x[i].ClassesTaken, y);
OUT<<x[i].ID<<"\t"<<GPA<<"\t"<<CSCI_GPA<<"\t"<<NLA_percentage<<"%"<<endl;
}

}
