#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "ParticalRandomGenerator.h"

using namespace std;

int main(int argc, char* argv[])
{
	string password,password2;
	bool usingOutFile=false;
	bool askPassword = true;
	bool decrypt = false;
	ofstream outFile;
	ifstream inFile;
	streampos size;
	unsigned int numOfBytes;
	std::vector<string> Args;
	for(int i = 0 ;i < argc;i++)
	{
		Args.push_back(argv[i]);
	}
	
	for(int i = 1;i<argc-1;i++)
	{
		if(Args[i].at(0)=='-')
		{
			switch(Args[i].at(1))
			{
			case 'd':
				decrypt = true;
				break;
			case 'o':
				usingOutFile=true;
				outFile.open(Args[i+1]);
				i++;
				break;
			case 'p':
				askPassword = false;
				password = Args[i+1];
				if(password.length()<5)
				{
					cout << "Password is too short" << endl;
					return 0;
				}
				i++;
				break;
			case 'i':
				inFile.open(Args[i+1]);
				if(!inFile.is_open())
				{
					cout << "Error opening file" << endl;
					return 0;
				}
				inFile.seekg(0,ios::end);
				size = inFile.tellg();
				inFile.seekg(0,ios::beg);
				i++;
				break;
			case 'n':
				numOfBytes = atoi(Args[i+1].c_str());
				if(numOfBytes<8 || numOfBytes > 512)
				{
					cout << "Invalid number of random bytes" << endl;
					return 0;
				}
				i++;
				break;
			default:
				cout << "Invalid Argument" << endl;
				return 0;
			};
		}
		else
		{
			inFile.open(Args[i]);
			if(!inFile.is_open())
			{
				cout << "Error opening file" << endl;
				return 0;
			}
			inFile.seekg(0,ios::end);
			size = inFile.tellg();
			inFile.seekg(0,ios::beg);
		}
	}
	if(askPassword)
	{
		cout << "Enter password: " << endl;
		cin >> password;
		cout << "Re-Enter password: " << endl;
		cin >> password2;
		if(password!=password2)
		{
			cout << "Passwords don't match" << endl;
			return 0;
		}
	}
	
	if(!decrypt)
	{
		ParticalRandomGenerator randGen(password,"L4Jld2fis4IEls");
		char temp[1] ;
		char inFromFile[1];
		for(int i = 0; i<size;i++)
		{
			inFile.read(inFromFile,1);
			temp[0] = randGen.getRandomChar();
			temp[0] = temp[0] ^ inFromFile[0];
			if(usingOutFile)
			{
				outFile.write(temp,1);
			}
			else
			{
				cout << temp;
			}
		}
	}
	return 0;
}
