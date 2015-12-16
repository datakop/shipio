#include "EntityManager.h"



Asteroid* EntityManager::createAsteroidAtPosition(cocos2d::Vec2 pos) {
    auto asteroid = Asteroid::create();
    asteroid->setPosition(pos);
    
    _entities.push_back(asteroid);
    
    return asteroid;
}

Ship* EntityManager::createShipAtPosition(cocos2d::Vec2 pos) {
    auto ship = Ship::create();
    ship->setPosition(pos);
    
    _entities.push_back(ship);
    
    return ship;
}

void EntityManager::createBulletAtPosition(cocos2d::Vec2 pos) {
//    auto bullet = cocos2d::PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
//    bullet->setContactTestBitmask(0xFFFFFFFF);
//    auto sprite = Sprite::create();
//    
//    sprite->addComponent(bullet);
//    sprite->setPosition(Point(visibleSize.width / 2 + origin.x + 30,
//                              visibleSize.height / 2 + origin.y));
//    this->addChild(sprite);
//    
//    sprite->getPhysicsBody()->applyImpulse(Vec2(10, 0));

}


EntityManager::~EntityManager() {}
