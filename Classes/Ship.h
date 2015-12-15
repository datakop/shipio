#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include "cocos2d.h"

class Ship : public cocos2d::Sprite {
private:
    void initOptions();

    void addEvents();

public:
    int health = 100;

    static Ship *create();
    ~Ship();
};

#endif /* defined(SHIPIO_SHIP_H) */
