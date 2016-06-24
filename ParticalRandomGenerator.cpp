#include "ParticalRandomGenerator.h"
#include <math.h>
#include <iostream>

ParticalRandomGenerator::ParticalRandomGenerator(std::string inPassword,std::string inRandomBits)
{
	password = inPassword;
	randomBits = inRandomBits;
	unsigned int totalLength  = (inPassword.length())+(inRandomBits.length());
	rows = ceil(sqrt(totalLength));
	blocks = pow(ceil(sqrt(totalLength)),2);
	volume = rows*volMulti;
	Particals::setVolume(volume);
	unsigned int passwordCount=0,randomBitCount=0;
	Particals* tempPartical ;
	int addX=0, addY=0;
	for(unsigned int i = 0;i<=totalLength-1;)
	{
		if(passwordCount<=password.length()-1)
		{
			addY = floor(i/rows)*volMulti;
			addX = (i%rows)*volMulti;
			tempPartical = new Particals(getX(password.at(passwordCount))+addX,getY(password.at(passwordCount))+addY,getXSpeed(password.at(passwordCount)),getYSpeed(password.at(passwordCount)),getSize(password.at(passwordCount)));
			m_particals.push_back(tempPartical);
			passwordCount++;
			i++;
		}
		if(randomBitCount<=randomBits.length()-1)
		{
			addY = floor(i/rows)*volMulti;
			addX = (i%rows)*volMulti;
			tempPartical = new Particals(getX(randomBits.at(randomBitCount))+addX,getY(randomBits.at(randomBitCount))+addY,getXSpeed(randomBits.at(randomBitCount)),getYSpeed(randomBits.at(randomBitCount)),getSize(randomBits.at(randomBitCount)));
			m_particals.push_back(tempPartical);
			randomBitCount++;
			i++;
		}
	}
	int restOf = blocks-(randomBits.length()+password.length());
	for(unsigned int i = blocks-restOf;i<blocks;i++)
	{
		addY = floor(i/rows)*volMulti;
		addX = (i%rows)*volMulti;
		tempPartical = new Particals(addX,addY,0,0,1);
		m_particals.push_back(tempPartical);
	}
	updateParticals(200);
}

double ParticalRandomGenerator::getRandomChar()
{
	double  returnChar;
	if(blockCountdown>blocks)
	{
		returnChar = m_particals.at(blockCountdown-blocks-1)->getX();
	}
	else
	{
		returnChar = m_particals.at(blockCountdown-1)->getY();
	}
	blockCountdown--;
	if(blockCountdown<=0)
	{
		updateParticals(200);
	}
	return returnChar;
}

ParticalRandomGenerator::~ParticalRandomGenerator()
{
}

int ParticalRandomGenerator::getX(const char inChar)const
{
	return (volMulti/16)*((int)inChar%16);
}

int ParticalRandomGenerator::getY(const char inChar)const
{
	return (volMulti/16)*floor((int)inChar/16);
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
	return 1;//(inChar%3)*1;
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

void ParticalRandomGenerator::updateParticals(const unsigned int inFrame)
{
	for(unsigned int j = 0;j<inFrame;j++)
	{
		for(unsigned int i=0;i<m_particals.size();i++)
		{
			m_particals.at(i)->addForce(calculateXForce(i),calculateYForce(i));
		}
		for(unsigned int i=0;i<m_particals.size();i++)
		{
			m_particals.at(i)->updateLocation();
		}
	}
	blockCountdown = blocks*2;
}


