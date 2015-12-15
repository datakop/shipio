#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"
#include "Ship.h"

class MainLayer : public cocos2d::Layer {
private:
    virtual bool init();

    cocos2d::PhysicsWorld *_world;
    Ship *_ship;
    
    cocos2d::DrawNode *_drawNode;
    float _angle;

public:
    static const int TAG = 100;
    
    CREATE_FUNC(MainLayer);
    void update(float delta);
    
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _world = world; }
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
};

#endif  // SHIPIO_MAINLAYER_H
