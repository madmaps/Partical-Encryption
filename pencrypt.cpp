#include <iostream>
#include "ParticalRandomGenerator.h"

using namespace std;

int main()
{
	ParticalRandomGenerator randGen("password","L4Jld2fis4IEls");
	for(int i = 0; i<=32;i++)
	{
		cout << randGen.getRandomChar() << endl;
		//cout << i << endl;
		randGen.getRandomChar();
	}
	return 0;
}
