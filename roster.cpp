// Vector and List algorithms
// Alex Donahue
// 9/21/2026

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
using namespace std;


void readRoster(list<string>& roster, string fileName);  
void printRoster(const list<string>& roster); 
// Check double enrolled
void checkDoubleEnrolled(list<string>& currentRoster, const list<string>& cs123, const list<string>& cs4);

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{ 
		cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl; 
		exit(1);
	}

	
	vector <list<string>> courseStudents; 
	// lists representing cs1-3 and cs4
	list<string> cs123;
	list<string> cs4;
	for(int i = 1; i < argc - 1; ++i)
	{
		list<string> roster;
		readRoster(roster, argv[i]);  
		cout << "\n\n" << argv[i] << "\n";  
		printRoster(roster);
		if (i <= 3)
		{
			// Copies the values
			cs123.insert(cs123.end(), roster.begin(), roster.end());
		}
		else if (i == 4)
		{
			cs4.insert(cs4.end(), roster.begin(), roster.end());
		}
		courseStudents.push_back(move(roster)); 
	}

	// reading in dropouts
	list<string> dropouts; 
	readRoster(dropouts, argv[argc - 1]); 
	cout << "\n\n dropouts \n"; 
	printRoster(dropouts);

	list<string> allStudents;
 
	for(auto& lst : courseStudents) 
		allStudents.splice(allStudents.end(),lst);

	cout << "\n\n all students unsorted \n"; 
    printRoster(allStudents);

	allStudents.sort();
	cout << "\n\n all students sorted \n"; 
	printRoster(allStudents);

	allStudents.unique(); 
	cout << "\n\n all students, duplicates removed \n"; 
	printRoster(allStudents);

	for (const auto& str : dropouts)
		allStudents.remove(str);
	cout << "\n\n all students, dropouts removed \n"; 
	printRoster(allStudents);
	
	// Main solution part
	checkDoubleEnrolled(allStudents, cs123, cs4);
	cout << "\n\n all students, double enrolled removed \n"; 
	printRoster(allStudents);
	return 0;
}

void readRoster(list<string>& roster, string fileName)
{
	ifstream course(fileName); // I am trying it
    
	string first, last;
	while(course >> first >> last)
		roster.push_back(first + ' ' + last);
	course.close();
}

// printing a list out
void printRoster(const list<string>& roster)
{
	for(const auto& str : roster)
		cout << str << endl;
}

// Check double enrolled
void checkDoubleEnrolled(list<string>& currentRoster, const list<string>& cs123, const list<string>& cs4)
{
	// Loop to find duplicates
	for (auto i = cs123.begin(); i != cs123.end(); i++)
	{
		for (auto j = cs4.begin(); j != cs4.end(); j++)
		{
			if (*i == *j)
			{
				currentRoster.remove(*i);
			}
		}	
		
	}	
}
