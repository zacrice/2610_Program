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
#include <stdlib.h>
#include <bitset>
#include <iomanip>
using namespace std;

class instruction
{
	public:
		int format;
		string rs, rt, rd, opcode, funct, shamt, immediate, addr, final;
		unsigned long finalVal;
};

class lable
{
	public:
		string text;
		int address;
};

string registerVal(string reg);

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
		//cout << instructions[i] << endl;
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
	int labCount = 0;
	//count number of lables
	for(int i = 0; i < count; i++)
	{
		string isLabel = ":";
		size_t found = tokenized[i][0].find(isLabel);
		if (found!=string::npos)
		{
			labCount++;
		}
	}

	instruction instr[count];
	lable lab[labCount];

	//symbol table
	//string labels[10];
	//int labAdresses[10];
	int tabCount = 0;
    
    for(int i = 0; i < count; i++)
    {
        string isLabel = ":";
        size_t found = tokenized[i][0].find(isLabel);
        if (found!=string::npos)
        {
            lab[tabCount].text = tokenized[i][0];
            lab[tabCount].address = i * 4; //only multiplies line the label is on by 4. does not store actual address
            tabCount++;
        }
    }
    
    ofstream outfile;
    outfile.open("output.txt");
    
	for (int i = 0; i < count; i++)
	{
        stringstream ss;
        int j = 0, temp1 = 0;
        string isLabel = ":";
        size_t found = tokenized[i][0].find(isLabel);
        if (found!=string::npos)
        {
            j++;
        }
        
        //******* R format instructions*****
        if (tokenized[i][j] == "add")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";//store opcode and funct as binary stringst
            instr[i].funct = "100000";//can concatenate with '+'
            instr[i].shamt = "00000";
            j++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] =="addu")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100001";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "and")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100100";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "jr")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "001000";
            instr[i].shamt = "00000";
            j++;
            instr[i].rs = registerVal(tokenized[i][j]); //only has one parameter
            instr[i].rt = "00000";
            instr[i].rd = "00000";
            //need to convert rs to coresponding int then binary then hex
        }
        
        else if (tokenized[i][j] == "nor")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100111";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "or")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100101";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "slt")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "101010";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "sltu")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "101011";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        else if (tokenized[i][j] == "sll")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "000000";
            instr[i].rs = "00000";
            j++;
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;
            instr[i].rt = registerVal(tokenized [i][j]);
            j++;
            instr[i].shamt = registerVal(tokenized[i][j]); //will read in integer as string
        }					//need to convert to unsigned int for binary conversion function
        
        else if (tokenized[i][j] == "srl")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "000010";
            instr[i].rs = "00000";
            j++;
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;
            instr[i].rt = registerVal(tokenized [i][j]);
            j++;
            instr[i].shamt = registerVal(tokenized[i][j]); //will read in integer as string
        }					//need to convert to unsigned int for binary conversion function
        
        else if (tokenized[i][j] == "sub")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100010";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        else if (tokenized[i][j] == "subu")
        {
            instr[i].format = 0;
            instr[i].opcode = "000000";
            instr[i].funct = "100011";
            instr[i].shamt = "00000";
            j ++;			//move to destination register
            instr[i].rd = registerVal(tokenized[i][j]);
            j++;			//move to source register
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;			//move to target register
            instr[i].rt = registerVal(tokenized[i][j]);
            //Need to convert each to corresponding ints then binary then hex
            //http://www.cplusplus.com/forum/general/65862/
        }
        
        //******* I format instructions *******
        
        else if (tokenized[i][j] == "addi")
        {
            instr[i].format = 1;
            instr[i].opcode = "001000";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "addiu")
        {
            instr[i].format = 1;
            instr[i].opcode = "001001";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized [i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "andi")
        {
            instr[i].format = 1;
            instr[i].opcode = "001100";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized [i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "beq")
        {
            instr[i].format = 1;
            instr[i].opcode = "000100";
            j++;
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //immediate will store the label
        }
        
        else if (tokenized[i][j] == "bne")
        {
            instr[i].format = 1;
            instr[i].opcode = "000101";
            j++;
            instr[i].rs = registerVal(tokenized[i][j]);
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //immediate will store the label
        }
        
        else if (tokenized[i][j] == "lw") //NEEDS A LOT OF WORK
        {
            instr[i].format = 1;
            instr[i].opcode = "100011";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized[i][j]); //will store whole 0($s0)
            j = 5;
        }				//don't know how to convert
        
        else if (tokenized[i][j] == "ori")
        {
            instr[i].format = 1;
            instr[i].opcode = "001101";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized [i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "slti")
        {
            instr[i].format = 1;
            instr[i].opcode = "001010";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized [i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "sltiu")
        {
            instr[i].format = 1;
            instr[i].opcode = "001011";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized [i][j]);
            j++;
            istringstream (tokenized[i][j]) >> temp1;
            instr[i].immediate = bitset< 16 >(temp1).to_string();
            //need to connect corresponding int to rt and rs
            //need to convert immediate to int to convert to binary
        }
        
        else if (tokenized[i][j] == "sw")	//NEEDS AS MUCH WORK AS lw
        {
            instr[i].format = 1;
            instr[i].opcode = "101011";
            j++;
            instr[i].rt = registerVal(tokenized[i][j]);
            j++;
            instr[i].rs = registerVal(tokenized[i][j]);
            //will store whole 0($s0)
        }				//don't know how to convert
        
        
        //******* J format instructions *****
        else if (tokenized[i][j] == "j")
        {
            instr[i].format = 2;
            instr[i].opcode = "000010";
            j++;
            instr[i].addr = tokenized[i][j];  //stores label
        }
        
        else if (tokenized[i][j] == "jal")
        {
            instr[i].format = 2;
            instr[i].opcode = "000011";
            j++;
            instr[i].addr = tokenized[i][j]; //stores label
        }
        
        //R format
        if (instr[i].format == 0)
        {
            instr[i].final = instr[i].opcode;
            instr[i].final += instr[i].rs;
            instr[i].final += instr[i].rt;
            instr[i].final += instr[i].rd;
            instr[i].final += instr[i].shamt;
            instr[i].final += instr[i].funct;
        }
        //I Format
        else if (instr[i].format == 1)
        {
            instr[i].final = instr[i].opcode;
            instr[i].final += instr[i].rs;
            instr[i].final += instr[i].rt;
            instr[i].final += instr[i].immediate;
        }
        //J Format
        else if (instr[i].format == 2)
        {
            ;
        }
        //cout << instr[i].final << endl;
        
        instr[i].finalVal = strtoul(instr[i].final.c_str(), NULL, 2);
        //cout << "0x" << setfill('0') << setw(8) << hex << instr[i].finalVal << endl;
        outfile << "0x" << setfill('0') << setw(8) << hex << instr[i].finalVal << endl;
	}
    outfile << endl << "Lable" << "\t\t\t\t" << "Address" << endl;
    for(int i = 0; i < labCount; i++)
    {
        outfile << lab[i].text << "\t\t\t\t" << "0x" << setfill('0') << setw(8) << hex << lab[i].address << endl;
    }
    outfile.close();
	return 0;
}

string registerVal(string reg)
{
	if(reg == "$zero")
	{
		return "00000";
	}
	else if(reg == "$t0")
	{
		return "01000";
	}
	else if(reg == "$t1")
	{
		return "01001";
	}
	else if(reg == "$t2")
	{
		return "01010";
	}
	else if(reg == "$t3")
	{
		return "01011";
	}
	else if(reg == "$t4")
	{
		return "01100";
	}
	else if(reg == "$t5")
	{
		return "01101";
	}
	else if(reg == "$t6")
	{
		return "01110";
	}
	else if(reg == "$t7")
	{
		return "01111";
	}
	else if(reg == "$s0")
	{
		return "10000";
	}
	else if(reg == "$s1")
	{
		return "10001";
	}
	else if(reg == "$s2")
	{
		return "10010";
	}
	else if(reg == "$s3")
	{
		return "10011";
	}
	else if(reg == "$s4")
	{
		return "10100";
	}
	else if(reg == "$s5")
	{
		return "10101";
	}
	else if(reg == "$s6")
	{
		return "10110";
	}
	else if(reg == "$s7")
	{
		return "10111";
	}
	else if(reg == "$t8")
	{
		return "11000";
	}
	else if(reg == "$t9")
	{
		return "11001";
	}
	else
	{
		return "00000";
	}

}
