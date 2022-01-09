#ifndef __Obstacles_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Obstacles_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/Obstacle/Obstacle.h"

class KillObstacle : public Obstacle {
public:
    KillObstacle(float x, float y, float width, float height, std::string src)
        : Obstacle(x, y, width, height, src) {
        isInstaKill = true;
    }
};

class MoneyObstacle : public Obstacle {
public:
    MoneyObstacle(float x, float y, float width, float height, std::string src, float pMoney)
        : Obstacle(x, y, width, height, src) {
        money = pMoney;
    }
};

class AcademicObstacle : public Obstacle {
public:
    AcademicObstacle(float x, float y, float width, float height, std::string src)
        : Obstacle(x, y, width, height, src) {
        increaseWarning = true;
    }
};


#endif