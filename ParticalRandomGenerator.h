#ifndef __PARTICALRANDOMGENERATOR__
#define __PARTICALRANDOMGENERATOR__
#include <string>
#include <vector>
#include "particals.h"

class ParticalRandomGenerator
{
public:
	ParticalRandomGenerator(std::string inPassword,std::string inRandomBits);
	char getRandomChar();
	
	~ParticalRandomGenerator();

protected:
private:
	std::string password;
	std::string randomBits;
	int volume;
	int rows;
	int blocks;
	std::vector<Particals*> m_particals;
	
	int getX(const char inChar)const;
	int getY(const char inChar)const;
	int getXSpeed(const char inChar)const;
	int getYSpeed(const char inChar)const;
	int getSize(const char inChar)const;
};
#endif	
