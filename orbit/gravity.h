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
		positionV(float x, float y, int angle,float velocity,int mass)
		{
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

positionV gravityTo(positionV ob1,positionV ob2)
{
	float distance = distanceBTW(ob1, ob2);
	float angle = angleBTW(ob1, ob2) * (3.14/180);

	float grav = ob1.mass / pow(distance, 2);
	
	if ((ob2.x - ob1.x) < 0 && (ob2.y - ob1.y) < 0)
	{
		angle = 270 - angle;
	}
	else if ((ob2.x - ob1.x) < 0 && (ob2.y - ob1.y) > 0)
	{
		angle = 180 - angle;
	}

	else if((ob2.x - ob1.x) > 0 && (ob2.y - ob1.y) < 0)
	{
		angle = 270 + angle;
	}
	
	else if ((ob2.x - ob1.x) > 0 && (ob2.y - ob1.y) > 0)
	{
		angle =  angle;
	}
	ob2.x += ob2.velocity*std::cos(ob2.angle) - grav*std::sin(angle*3.14 / 180);
	ob2.y += ob2.velocity*std::sin(ob2.angle) - grav*std::cos(angle*3.14 / 180);

	return ob2;
}


