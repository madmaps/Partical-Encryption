#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "ParticalRandomGenerator.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream inFile(argv[1], ios::in|ios::binary|ios::ate);
	ofstream outFile(argv[2], ios::out|ios::binary);
	if(!inFile)
	{
		return 0;
	}
	streampos size = inFile.tellg();
	inFile.seekg(0,ios::beg);
	
	
	string password,password2;
	cout << "Enter password: " << endl;
	cin >> password;
	cout << "Re-Enter password: " << endl;
	cin >> password2;
	if(password!=password2)
	{
		cout << "Passwords don't match" << endl;
		return 0;
	}
	ParticalRandomGenerator randGen(password,"L4Jld2fis4IEls");
	
	
	char temp[1] ;
	char inFromFile[1];
	for(int i = 0; i<size;i++)
	{
		inFile.read(inFromFile,1);
		temp[0] = randGen.getRandomChar();
		temp[0] = temp[0] ^ inFromFile[0];
		outFile.write(temp,1);
	}
	return 0;
}
