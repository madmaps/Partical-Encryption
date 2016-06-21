#include "ParticalRandomGenerator.h"
#include <math.h>

ParticalRandomGenerator::ParticalRandomGenerator(std::string inPassword,std::string inRandomBits)
{
	password = inPassword;
	randomBits = inRandomBits;
	blocks = pow(ceil(sqrt(inPassword.length()+inRandomBits.length())),2);
	volume = ceil(sqrt(inPassword.length()+inRandomBits.length()))*16;
	Particals::setVolume(volume);
	unsigned int passwordCount=0,randomBitCount=0;
	Particals* tempPartical ;
	for(int i = 0;i < blocks;i++)
	{
		if(passwordCount<=password.length())
		{
			tempPartical = new Particals(getX(password.at(passwordCount)),getY(password.at(passwordCount)),getXSpeed(password.at(passwordCount)),getYSpeed(password.at(passwordCount)),getSize(password.at(passwordCount)));
			m_particals.push_back(tempPartical);
			passwordCount++;
		}
		if(randomBitCount<=randomBits.length())
		{
			tempPartical = new Particals(getX(randomBits.at(randomBitCount)),getY(randomBits.at(randomBitCount)),getXSpeed(randomBits.at(randomBitCount)),getYSpeed(randomBits.at(randomBitCount)),getSize(randomBits.at(randomBitCount)));
			m_particals.push_back(tempPartical);
			randomBitCount++;
		}
	}
	int restOf = blocks-(randomBits.length()+password.length());
	for(int i = blocks-restOf;i<blocks;i++)
	{
		//Create Generic Particles Here
	}
}

char ParticalRandomGenerator::getRandomChar()
{
	char temp = 'j';
	return temp;
}

ParticalRandomGenerator::~ParticalRandomGenerator()
{
}

int ParticalRandomGenerator::getX(const char inChar)const
{
	return (int)inChar%16;
}

int ParticalRandomGenerator::getY(const char inChar)const
{
	return floor((int)inChar/16);
}

int ParticalRandomGenerator::getXSpeed(const char inChar)const
{
	return ((int)inChar%16)-8;
}

int ParticalRandomGenerator::getYSpeed(const char inChar)const
{
	return (((int)inChar+5)%16)-8;
}

int ParticalRandomGenerator::getSize(const char inChar)const
{
	return (inChar%10)*5;
}


