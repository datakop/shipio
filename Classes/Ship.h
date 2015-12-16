#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include "cocos2d.h"
#include "Brain.h"

#include <map>

class Ship : public cocos2d::Sprite {
private:
    void initOptions();

    void addEvents();

public:
    static Ship *create();

    ~Ship();

    virtual void update(float delta) override;

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

    void setOptions();

    void setHealth(int health) { _health = health; }

    int getHealth() { return _health; }

private:
    Brain *_brain;
    int _health = 100;
    float _forwardPower = 15;
    float _rotatePower = 1;
    float _maxSpeed = 110;
    float _maxAngularSpeed = 1;
    static std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};

#endif /* defined(SHIPIO_SHIP_H) */
