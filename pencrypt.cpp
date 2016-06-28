#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "ParticalRandomGenerator.h"
#include <random>

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
	unsigned int numOfBytes=32;
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
				if(numOfBytes<8 || numOfBytes > 255)
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
	
	char temp[1];
	string randomBits;
	if(!decrypt)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0,255);
		temp[0] = (unsigned char)numOfBytes;
		outFile.write(temp,1);
				
		for(unsigned int i=0;i<numOfBytes;i++)
		{
			randomBits+= (unsigned char)dist(mt);
		}
		outFile.write(randomBits.c_str(),numOfBytes);
	}
	else
	{
		inFile.read(temp,1);
		numOfBytes = (unsigned int)temp[0] & 0xFF;
		for(unsigned int i = 0;i<numOfBytes;i++)
		{
			inFile.read(temp,1);
			randomBits+=(unsigned char)temp[0];
		}
		size-=numOfBytes+1;

	} 
	ParticalRandomGenerator randGen(password,randomBits);
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
	
	return 0;
}
