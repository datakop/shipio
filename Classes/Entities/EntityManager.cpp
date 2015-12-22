#include <vector>

#include "EntityManager.h"

#include "../Components/SimpleComponent.h"
#include "../Components/FireComponent.h"
#include "../Components/ShipKeyboardComponent.h"


void EntityManager::init() {}


Sprite *EntityManager::createAsteroidAtPosition(cocos2d::Vec2 pos) {
    auto asteroid = Sprite::create("asteroid.png");
    asteroid->setPosition(pos);

    auto body = PhysicsBody::createBox(Size(asteroid->getContentSize().width - 30,
                                            asteroid->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    asteroid->setPhysicsBody(body);

    _entities.push_back(asteroid);
    return asteroid;
}

Ship *EntityManager::createShipAtPosition(cocos2d::Vec2 pos) {
    std::vector<GameComponent *> components = {
            new SimpleComponent(),
            new FireComponent(),
            new ShipKeyboardComponent()
    };
    auto ship = Ship::create(components);
    ship->setPosition(pos);

    auto shipBody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(0.01, 0.5, 0));
    shipBody->setContactTestBitmask(0x12);

    ship->setPhysicsBody(shipBody);
    ship->getPhysicsBody()->setVelocityLimit(ship->maxSpeed);
    ship->getPhysicsBody()->setAngularVelocityLimit(ship->maxAngularSpeed);

    _entities.push_back(ship);
    return ship;
}

Sprite *EntityManager::createEndPointAtPosition(cocos2d::Vec2 pos) {
    auto endPoint = Sprite::create("end_point2.png");
    endPoint->setPosition(pos);

    auto body = PhysicsBody::createBox(Size(endPoint->getContentSize().width - 30,
                                            endPoint->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    endPoint->setPhysicsBody(body);

    _entities.push_back(endPoint);
    return endPoint;
}

void EntityManager::createBulletAtPosition(cocos2d::Vec2 pos, float rot) {
    auto bulletSprite = Sprite::create();
    auto bullet = PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
    bullet->setContactTestBitmask(0x12);
    bulletSprite->addComponent(bullet);

    bulletSprite->setPosition(pos + Vec2(50, 0));

    bulletSprite->getPhysicsBody()->applyImpulse(Vec2(cosf(rot) * 10, sinf(-rot)));

}


EntityManager::~EntityManager() {

}
