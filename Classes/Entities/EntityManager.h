#ifndef __shipio__EntityManager__
#define __shipio__EntityManager__

#include <cstdlib>

#include "cocos2d.h"

#include "Ship.h"


class EntityManager {
public:

    void init();

    Sprite *createAsteroidAtPosition(cocos2d::Vec2 pos);

    Sprite *createEndPointAtPosition(cocos2d::Vec2 pos);

    Ship *createShipAtPosition(cocos2d::Vec2 pos);

    void createBulletAtPosition(cocos2d::Vec2 pos, float rot);

    ~EntityManager();

private:
    std::vector<cocos2d::Sprite *> _entities;
};

#endif /* defined(__shipio__EntityManager__) */
