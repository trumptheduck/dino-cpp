#ifndef __Vector2_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __Vector2_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Vector2
{
public:
	float x = 0;
	float y = 0;
	Vector2() {};
	Vector2(float pX, float pY)
	{
		x = pX;
		y = pY;
	};
};
#endif