#include <iostream>
#include "ParticalRandomGenerator.h"

using namespace std;

int main()
{
	ParticalRandomGenerator randGen("pass","randy");
	for(int i = 0; i<=20;i++)
	{
		cout << randGen.getRandomChar() << endl;
	}
	return 0;
}
