#include "particals.h"
#include <math.h>

double Particals::gravityForce = 10;
double Particals::massDiameterRatio = 1;
int Particals::volume = 100;

Particals::Particals()
{
    mass = 1;
    calculateDiameter();
    locationX=0;
    locationY=0;
    speedX=0;
    speedY=0;
}

Particals::Particals(double inLocationX, double inLocationY, int inMass)
{
    mass = inMass;
    calculateDiameter();
    locationX=inLocationX;
    locationY=inLocationY;
    speedX=0;
    speedY=0;
}

Particals::Particals(double inLocationX, double inLocationY, double inSpeedX, double inSpeedY, int inMass)
{
    mass = inMass;
    calculateDiameter();
    locationX=inLocationX;
    locationY=inLocationY;
    speedX=inSpeedX;
    speedY=inSpeedY;
}

void Particals::setVolume(const int inVolume)
{
	volume = inVolume;
}

void Particals::combine(Particals& inPartical)
{
    speedX = speedX*((double)mass/((double)mass+(double)inPartical.mass)) + inPartical.speedX*((double)inPartical.mass/((double)mass+(double)inPartical.mass));
    speedY = speedY*((double)mass/((double)mass+(double)inPartical.mass)) + inPartical.speedY*((double)inPartical.mass/((double)mass+(double)inPartical.mass));
    mass += inPartical.mass;
    calculateDiameter();

    inPartical.mass=0;
    inPartical.calculateDiameter();
    inPartical.locationX=0;
    inPartical.locationY=0;
    inPartical.speedX=0;
    inPartical.speedY=0;
}

void Particals::addForce(const double &inXForce, const double &inYForce)
{
    speedX+=inXForce/mass;
    speedY+=inYForce/mass;
}

void Particals::updateLocation()
{
	double dblVolume = (double)volume;
    locationX+=speedX;
	locationY+=speedY;

    if(locationX>dblVolume)
    {
        speedX=-speedX;
    }
    if(locationX<0)
    {
        speedX=-speedX;
    }


    if(locationY>dblVolume)
    {
        speedY=-speedY;
    }
    if(locationY<0)
    {
        speedY=-speedY;
    }
}

double Particals::calculateXForce(const Particals &inPartical) const
{
    double distance = sqrt(pow(inPartical.locationX-locationX,2)+pow(inPartical.locationY-locationY,2));
    if(distance>fabs(diameter/2+inPartical.diameter/2))
    {
		double force = (gravityForce*mass*inPartical.mass)/pow(distance,2);
		double xForce = (force/distance)*(inPartical.locationX-locationX);//sqrt(pow(distance,2)-pow(inPartical.locationY-locationY,2));
		return xForce;
	}
	return 0;
}

double Particals::calculateYForce(const Particals &inPartical) const
{
    double distance = sqrt(pow(inPartical.locationX-locationX,2)+pow(inPartical.locationY-locationY,2));
	if(distance>fabs(diameter/2+inPartical.diameter/2))
    {
		double force = (gravityForce*mass*inPartical.mass)/pow(distance,2);
		double yForce = (force/distance)*(inPartical.locationY-locationY);//sqrt(pow(force,2)-pow(inPartical.locationX-locationX,2));
		return yForce;
	}
	return 0;
}

double Particals::getX()const
{
    return locationX;
}

double Particals::getY()const
{
    return locationY;
}

double Particals::getDiameter()const
{
    return diameter;
}

double Particals::getSpeedX() const
{
    return speedX;
}

double Particals::getSpeedY() const
{
    return speedY;
}

int Particals::getMass() const
{
    return mass;
}


void Particals::calculateDiameter()
{
    diameter = 2 * sqrt(mass/M_PI) * massDiameterRatio;
}
