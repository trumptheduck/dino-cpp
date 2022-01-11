#ifndef __Obstacles_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Obstacles_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/Obstacle/Obstacle.h"
#include "Classes/Vector2/Vector2.h"

class Cop : public Obstacle {
public:
	Cop(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 170, 150, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 3;
	}
};

class Algebra : public Obstacle {
public:
	Algebra(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 100, 150, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 0;
	}
};

class Analysis : public Obstacle {
public:
	Analysis(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 100, 150, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 0;
	}
};

class Physics : public Obstacle {
public:
	Physics(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 100, 150, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 7;
	}
};

class Philosophy : public Obstacle {
public:
	Philosophy(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 100, 150, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 2;
	}
};

class Girlfriend : public Obstacle {
public:
	Girlfriend(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 50, 190, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = -4;
	}
};

class PigSpear : public Obstacle {
public:
	PigSpear(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 220, 20, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = 10;
	}
};
class Sami : public Obstacle {
public:
	Sami(Vector2* vector, sf::Texture ptexture) : Obstacle(vector->x, vector->y, 120, 176, ptexture) {
		pos->y = vector->y - dim->y;
		speed->x = -5;
	}
};


#endif