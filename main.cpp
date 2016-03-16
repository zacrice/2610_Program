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

	int count = 0; //number of lines read in
	//counts number of commands entered
	for(int i = 0;!instructions[i].empty(); i++)
	{
		count ++;
	}

	//tokenize each instuction
	string tokenized[50][5], temp;	//tokenized will store tokenized instructions.

	for(int i = 0;i < count; i++)
	{
		int foo = 0;
		string delim = " ";

		size_t last = 0;
		size_t next = 0;
		string token;
		while ((next = instructions[i].find(delim, last)) != string::npos) //look for space until npos (the end of the string), store position in next
		{
			temp = instructions[i].substr(last, next-last);	//extracting the token
			//removing commas from the tokens that end in commas
			if(temp.substr( temp.length() - 1 ) == ",")	//if endchar = ","
			{
				temp = temp.substr(0, temp.size()-1);		//temp = temp - endchar
				tokenized[i][foo] = temp;
			}
			else
			{
				tokenized[i][foo] = temp;
			}
			cout << tokenized[i][foo] << endl;
			last = next + 1;
			foo++;
		}
		tokenized[i][foo] = instructions[i].substr(last, next-last);	//extracting token for last substring
		cout << tokenized[i][foo] << endl;
		foo = 0;
	}

	/*char *p;
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
	return 0;*/
}
