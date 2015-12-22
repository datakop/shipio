#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include <map>
#include <vector>

#include "cocos2d.h"

#include "../Components/GameComponent.h"

using namespace std;
using namespace cocos2d;


class Ship : public Sprite {
public:
    float forwardPower;
    float backwardPower;
    float rotatePower;
    float maxSpeed;
    float maxAngularSpeed;

    static Ship *create(vector<GameComponent *> components);

    Ship(vector<GameComponent *> components)
            : _components(move(components))
            , forwardPower(50)
            , backwardPower(50)
            , rotatePower(15)
            , maxSpeed(150)
            , maxAngularSpeed(10) {};

    ~Ship();

    void initOptions();

    void update(float delta);

private:
    vector<GameComponent *> _components;
};

#endif /* defined(SHIPIO_SHIP_H) */
