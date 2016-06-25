#include <iostream>
#include "ParticalRandomGenerator.h"
#include <math.h>

using namespace std;

int main()
{
	ParticalRandomGenerator randGen("pasword","L4Jld2fis4IEls");
	char temp ;
	for(int i = 0; i<=10000;i++)
	{
		temp = randGen.getRandomChar();
		cout << temp;
	}
	return 0;
}
