#pragma once
#include<math.h>
#include<iostream>

class positionV
{
public: float x;
		float y;
		float angle;
		float velocity;
		int mass;
		int timeG;
		positionV(float x, float y, int angle,float velocity,int mass)
		{
			this->timeG = 0;
			this->x = x;
			this->y = y;
			this->angle = (3.14 / 180)*angle;
			this->velocity = velocity;
			this->mass = mass;
		}


};



float distanceBTW(positionV ob1, positionV ob2)
{
	return sqrt(pow(ob1.x - ob2.x, 2) + pow(ob1.y - ob2.y, 2));
}

float angleBTW(positionV ob1, positionV ob2)
{
	return atan((ob2.y - ob1.y) / (ob2.x - ob1.x));
}

int time = 0.0001;
positionV gravityTo(positionV ob1,positionV ob2)
{

	float distance = distanceBTW(ob1, ob2);
	float angle = angleBTW(ob1, ob2) * (3.14/180);

	float grav = ob2.mass / pow(distance, 2);
	

	ob2.x += ob2.velocity*cos(ob2.angle) + grav*cos(angle);
	ob2.y += ob2.velocity*sin(ob2.angle) - grav*sin(angle);


	time++;
	return ob2;
}


