#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include "cocos2d.h"
#include "Brain.h"

class Ship : public cocos2d::Sprite {
private:
    void initOptions();

    void addEvents();

public:
    static Ship *create();

    ~Ship();

    void setHealth(int health) { _health = health; }

    int getHealth() { return _health; }

private:
    Brain *_brain;
    int _health = 100;
};

#endif /* defined(SHIPIO_SHIP_H) */
