#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include "cocos2d.h"

class Ship : public cocos2d::Sprite {
public:
    static Ship *create();

    void initOptions();

    void addEvents();

    void touchEvent(cocos2d::Touch *touch);
};

#endif /* defined(SHIPIO_SHIP_H) */
