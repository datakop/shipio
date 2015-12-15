#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"
#include "Ship.h"
#include "Map.h"

class MainLayer : public cocos2d::Layer {
private:
    virtual bool init();

public:
    CREATE_FUNC(MainLayer);

    void update(float delta);

    bool onContactBegin(cocos2d::PhysicsContact &contact);

    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _world = world; }

private:
    cocos2d::PhysicsWorld *_world;
    Ship *_ship;
    Map *_map;
    cocos2d::DrawNode *_drawNode;
    float _angle;

public:
    static const int TAG = 100;
};

#endif  // SHIPIO_MAINLAYER_H
