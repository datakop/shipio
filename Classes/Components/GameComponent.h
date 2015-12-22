#ifndef SHIPIO_GameComponent_H
#define SHIPIO_GameComponent_H

#include "cocos2d.h"


class GameComponent {
public:
    virtual bool init(cocos2d::Node *node) = 0;

    virtual void update(cocos2d::Node *node, float delta) = 0;
private:
};


#endif //SHIPIO_GameComponent_H
