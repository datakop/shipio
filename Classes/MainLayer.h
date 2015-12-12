#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"
#include "Ship.h"

class MainLayer : public cocos2d::Layer {
private:
    virtual bool init();

    cocos2d::PhysicsWorld *_world;
    Ship *_ship;

public:
    CREATE_FUNC(MainLayer);
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _world = world; }
};

#endif  // SHIPIO_MAINLAYER_H
