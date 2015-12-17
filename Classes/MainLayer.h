#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include <vector>

#include "cocos2d.h"
#include "Ship.h"
#include "EntityManager.h"


class MainLayer : public cocos2d::Layer {
public:
    static const int TAG = 100;

    CREATE_FUNC(MainLayer);

    void update(float delta);

    bool onContactBegin(cocos2d::PhysicsContact &contact);

    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _world = world; }

    ~MainLayer();

private:
    cocos2d::PhysicsWorld *_world;
    Ship *_ship;
    cocos2d::DrawNode *_drawNode;
    float _angle;

    EntityManager *_entityManager;

    std::vector<std::pair<double, double> > _dotMap;

    bool init();
};

#endif  // SHIPIO_MAINLAYER_H
