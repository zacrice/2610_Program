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
			//cout << tokenized[i][foo] << endl;
			last = next + 1;
			foo++;
		}
		tokenized[i][foo] = instructions[i].substr(last, next-last);	//extracting token for last substring
		//cout << tokenized[i][foo] << endl;
		
		foo = 0;
	}
	//*************BEGIN FRIDAY WORK***********************
	//symbol table
	string labels[10];
	int labAdresses[10];
	int tabCount = 0;
	
	//store instruction value integers
	string rs, rt, rd, opcode, funct, shamt, immediate;	//stores values from array. can also be used to store binary array
	unsigned int rsVal, rtVal, rdVal, shamtVal, immediateVal;
	int format; //0 == r format, 1 == i format, 2 == j format
	for (int i = 0; i < 50; i++)
	{
		rsVal = 0;
		rtVal = 0;
		rdVal = 0;
		shamtVal = 0;
		immediateVal = 0;
		for (int j = 0; j < 5; j++)
		{
			if (!tokenized[i][j].empty())//when the string is not empty
			{
				cout << tokenized[i][j] << " ";
				//******* R format instructions*****
					if (tokenized[i][j] == "add")
					{
						format = 0;
						opcode = "000000";//store opcode and funct as binary stringst
						funct = "100000";//can concatenate with '+'
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
					
					else if (tokenized[i][j] =="addu")
					{
						format = 0;
						opcode = "000000";
						funct = "100001";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
					
					else if (tokenized[i][j] == "and")
					{
						format = 0;
						opcode = "000000";
						funct = "100100";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
						
					else if (tokenized[i][j] == "jr")
					{
						format = 0;
						opcode = "000000";
						funct = "001000";
						shamt = "00000";
						j++;
						rs = tokenized[i][j]; //only has one parameter
						rt = "00000";
						rd = "00000";
						//need to convert rs to coresponding int then binary then hex
					}
					
					else if (tokenized[i][j] == "nor")
					{
						format = 0;
						opcode = "000000";
						funct = "100111";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
						
					else if (tokenized[i][j] == "or")
					{
						format = 0;
						opcode = "000000";
						funct = "100101";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
						
					else if (tokenized[i][j] == "slt")
					{
						format = 0;
						opcode = "000000";
						funct = "101010";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
						
					else if (tokenized[i][j] == "sltu")
					{
						format = 0;
						opcode = "000000";
						funct = "101011";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
						
					else if (tokenized[i][j] == "sll")
					{
						format = 0;
						opcode = "000000";
						funct = "000000";
						rs = "00000";
						j++;
						rd = tokenized[i][j];
						j++;
						rt = tokenized [i][j];
						j++;
						shamt = tokenized[i][j]; //will read in integer as string
					}					//need to convert to unsigned int for binary conversion function
						
					else if (tokenized[i][j] == "srl")
					{
						format = 0;
						opcode = "000000";
						funct = "000010";
						rs = "00000";
						j++;
						rd = tokenized[i][j];
						j++;
						rt = tokenized [i][j];
						j++;
						shamt = tokenized[i][j]; //will read in integer as string
					}					//need to convert to unsigned int for binary conversion function
						
					else if (tokenized[i][j] == "sub")
					{
						format = 0;
						opcode = "000000";
						funct = "100010";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
					else if (tokenized[i][j] == "subu")
					{
						format = 0;
						opcode = "000000";
						funct = "100011";
						shamt = "00000";
						j ++;			//move to destination register
						rd = tokenized[i][j];
						j++;			//move to source register
						rs = tokenized[i][j];
						j++;			//move to target register
						rt = tokenized[i][j];
						//Need to convert each to corresponding ints then binary then hex
						//http://www.cplusplus.com/forum/general/65862/
					}
					
					//******* I format instructions *******
						
					else if (tokenized[i][j] == "addi")
					{
						format = 1;
						opcode = "001000";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
						
					else if (tokenized[i][j] == "addiu")
					{
						format = 1;
						opcode = "001001";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
						
					else if (tokenized[i][j] == "andi")
					{
						format = 1;
						opcode = "001100";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
						
					else if (tokenized[i][j] == "beq")
					{
						format = 1;
						opcode = "000100";
						j++;
						rs = tokenized[i][j];
						j++;
						rt = tokenized[i][j];
						j++;
						immediate = tokenized[i][j];
						//immediate will store the label
					}
						
					else if (tokenized[i][j] == "bne")
					{
						format = 1;
						opcode = "000101";
						j++;
						rs = tokenized[i][j];
						j++;
						rt = tokenized[i][j];
						j++;
						immediate = tokenized[i][j];
						//immediate will store the label
					}
					
					else if (tokenized[i][j] == "lw") //NEEDS A LOT OF WORK
					{	
						format = 1;
						opcode = "100011";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized[i][j]; //will store whole 0($s0) 
						}				//don't know how to convert
						
					else if (tokenized[i][j] == "ori")
					{
						format = 1;
						opcode = "001101";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
						
					else if (tokenized[i][j] == "slti")
					{
						format = 1;
						opcode = "001010";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
						
					else if (tokenized[i][j] == "sltiu")
					{
						format = 1;
						opcode = "001011";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized [i][j];
						j++;
						immediate = tokenized[i][j];
						//need to connect corresponding int to rt and rs
						//need to convert immediate to int to convert to binary
					}
					
					else if (tokenized[i][j] == "sw")	//NEEDS AS MUCH WORK AS lw
					{
						format = 1;
						opcode = "101011";
						j++;
						rt = tokenized[i][j];
						j++;
						rs = tokenized[i][j]; //will store whole 0($s0) 
					}				//don't know how to convert
						
						
				//******* J format instructions *****
					else if (tokenized[i][j] == "j")
					{
						format = 2;
						opcode = "000010";
						j++;
						immediate = tokenized[i][j];  //stores label
					}
						
					else if (tokenized[i][j] == "jal")
					{
						format = 2;
						opcode = "000011";
						j++;
						immediate = tokenized[i][j]; //stores label
					}
						
				//store labels and addresses in symbol table
					else
					{
						if (j == 0) //make sure lable is first word of instruction
						{
							labels[tabCount] = tokenized[i][j];
							labAdresses[tabCount] = i * 4; //only multiplies line the label is on by 4. does not store actual address
							tabCount++;
						}
					}
			}
		}
		//if format == 0 R format
			//concatenate each binary string in the correct order using '+'
		
		//if format == 1 I format
			//concatenate each binary string
		
		//if format == 2 J format
			//concatenate each binary string
	}

	return 0;
}
