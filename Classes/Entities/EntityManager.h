#ifndef __shipio__EntityManager__
#define __shipio__EntityManager__

#include <cstdlib>

#include "cocos2d.h"

#include "Ship.h"
#include "Asteroid.h"
#include "EndPoint.h"


class EntityManager {
public:
    Asteroid *createAsteroidAtPosition(cocos2d::Vec2 pos);

    EndPoint *createEndPointAtPosition(cocos2d::Vec2 pos);

    Ship *createShipAtPosition(cocos2d::Vec2 pos);

    void createBulletAtPosition(cocos2d::Vec2 pos);

    ~EntityManager();

private:
    std::vector<cocos2d::Sprite *> _entities;
};

#endif /* defined(__shipio__EntityManager__) */
