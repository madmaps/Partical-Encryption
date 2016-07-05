#ifndef __PARTICALRANDOMGENERATOR__
#define __PARTICALRANDOMGENERATOR__
#include <string>
#include <vector>
#include "particals.h"

class ParticalRandomGenerator
{
public:
	ParticalRandomGenerator(std::string inPassword,std::string inRandomBits);
	unsigned char getRandomChar();
	
	~ParticalRandomGenerator();

protected:
private:
	std::string password;
	std::string randomBits;
	int volume;
	int volMulti;
	int rows;
	unsigned int blocks;
	std::vector<Particals*> m_particals;
	unsigned int blockCountdown;
	unsigned int cycleCount;
	
	void updateParticals(const unsigned int inFrames);
	int getX(const char inChar)const;
	int getY(const char inChar)const;
	int getXSpeed(const char inChar)const;
	int getYSpeed(const char inChar)const;
	int getSize(const char inChar)const;
	int getCycles(const char inChar)const;
	double calculateXForce(const unsigned int& current) const;
	double calculateYForce(const unsigned int& current) const;

	
	
};
#endif	
