#ifndef SHIPIO_SIMPLECOMPONENT_H
#define SHIPIO_SIMPLECOMPONENT_H

#include "cocos2d.h"

#include "GameComponent.h"


class SimpleComponent : public GameComponent {
public:
    bool init(cocos2d::Node *node);

    void update(cocos2d::Node *node, float delta);
};


#endif //SHIPIO_SIMPLECOMPONENT_H
