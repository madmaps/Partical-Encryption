#include "ParticalRandomGenerator.h"
#include <math.h>

ParticalRandomGenerator::ParticalRandomGenerator(std::string inPassword,std::string inRandomBits)
{
	password = inPassword;
	randomBits = inRandomBits;
	rows = ceil(sqrt(inPassword.length()+inRandomBits.length()));
	blocks = pow(ceil(sqrt(inPassword.length()+inRandomBits.length())),2);
	volume = ceil(sqrt(inPassword.length()+inRandomBits.length()))*16;
	Particals::setVolume(volume);
	unsigned int passwordCount=0,randomBitCount=0;
	Particals* tempPartical ;
	int addX=0, addY=0;
	for(int i = 0;i < blocks;i++)
	{
		if(passwordCount<=password.length())
		{
			addY = floor(i/rows)*16;
			addX = (i%rows)*16;
			tempPartical = new Particals(getX(password.at(passwordCount))+addX,getY(password.at(passwordCount))+addY,getXSpeed(password.at(passwordCount)),getYSpeed(password.at(passwordCount)),getSize(password.at(passwordCount)));
			m_particals.push_back(tempPartical);
			passwordCount++;
		}
		if(randomBitCount<=randomBits.length())
		{
			addY = floor(i/rows)*16;
			addX = (i%rows)*16;
			tempPartical = new Particals(getX(randomBits.at(randomBitCount))+addX,getY(randomBits.at(randomBitCount))+addY,getXSpeed(randomBits.at(randomBitCount)),getYSpeed(randomBits.at(randomBitCount)),getSize(randomBits.at(randomBitCount)));
			m_particals.push_back(tempPartical);
			randomBitCount++;
		}
	}
	int restOf = blocks-(randomBits.length()+password.length());
	for(int i = blocks-restOf;i<blocks;i++)
	{
		addY = floor(i/rows)*16;
		addX = (i%rows)*16;
		tempPartical = new Particals(addX+8,addY+8,0,0,1);
		m_particals.push_back(tempPartical);
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

double ParticalRandomGenerator::calculateXForce(const unsigned int& current) const
{
    double returnForce = 0;
    for(unsigned int i=0;i<m_particals.size();i++)
    {
        if(i!=current)
        {
            returnForce += m_particals.at(current)->calculateXForce(*m_particals.at(i));
        }
    }
    return returnForce;
}

double ParticalRandomGenerator::calculateYForce(const unsigned int& current) const
{
    double returnForce = 0;
    for(unsigned int i=0;i<m_particals.size();i++)
    {
        if(i!=current)
        {
            returnForce += m_particals.at(current)->calculateYForce(*m_particals.at(i));
        }
    }
    return returnForce;
}


