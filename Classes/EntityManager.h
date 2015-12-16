//
//  EntityManager.h
//  shipio
//
//  Created by Bors Kopin on 16.12.15.
//
//

#ifndef __shipio__EntityManager__
#define __shipio__EntityManager__

#include <cstdlib>

#include "Ship.h"
#include "Asteroid.h"


class EntityManager {
public:
    Asteroid* createAsteroidAtPosition(cocos2d::Vec2 pos);
    Ship* createShipAtPosition(cocos2d::Vec2 pos);
    void createBulletAtPosition(cocos2d::Vec2 pos);
    
    ~EntityManager();

private:
    std::vector<cocos2d::Sprite*> _entities;
};

#endif /* defined(__shipio__EntityManager__) */
