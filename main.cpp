/*
Zachary Rice & Michael Hummer
CSCE 2610
Assignment 01
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string.h>
using namespace std;
int main()
{
	string fileName;
	cout << "please input filename" << endl;
	cin >> fileName;
	//store enttire file into one string
	ifstream in(fileName.c_str());
	stringstream buffer;
	buffer << in.rdbuf();
	string entireFile = buffer.str();
	//cout << entireFile << endl << endl;
	//declare cursors to iterate through the string
	size_t pos1 = 0;
	size_t pos2;
	//count number of newline characters in the string
	size_t n = count(entireFile.begin(), entireFile.end(), '\n');
	//array to store each line
	string instructions[50];
	
	for (int i = 0; i < n+1; i++)
	{
		pos2 = entireFile.find("\n", pos1); //search for newline. pos2 will be where the\n was found
		instructions[i] = entireFile.substr(pos1, (pos2-pos1)); //store the substring between the two cursors in the array of instructions
		cout << instructions[i] << endl;
		pos1 = pos2+1; //set pos1 to the next character after pos2 to search for next line
	}
	char *p;
	//tokenize each instuction
	for (int i = 0; i < n+1; i++)
	{
		p = strtok(instructions[i], " ,");
		while (p)
		{
			printf("Token: %s\n", p);
			p = strtok(NULL, " ,");
		}
	}
	return 0;
}
	
