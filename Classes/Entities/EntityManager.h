#ifndef __shipio__EntityManager__
#define __shipio__EntityManager__

#include <cstdlib>

#include "cocos2d.h"

#include "Ship.h"

using namespace cocos2d;


class EntityManager {
public:
    /**
     * Returns a shared instance of the EntityManager.
     */
    static EntityManager *getInstance();

    void init();

    Ship *getShip() { return _ship; };

    std::vector<Sprite *> getWallEdges() { return _wallEdges; };

    Ship *createShipAtPosition(cocos2d::Vec2 pos = Vec2(0, 0));

    Sprite *createAsteroidAtPosition(cocos2d::Vec2 pos);

    Sprite *createEndPointAtPosition(cocos2d::Vec2 pos = Vec2(0, 0));

    Sprite *createBulletAtPosition(cocos2d::Vec2 pos, float rot);

    Node *createScreenBox();

    ~EntityManager();

private:
    Size _visibleSize;
    Vec2 _origin;
    std::vector<Node *> _entities;

    Ship *_ship;

    std::vector<Sprite *> _wallEdges;
    std::pair<double, double> _start;
    std::pair<double, double> _end;

};

#endif /* defined(__shipio__EntityManager__) */
