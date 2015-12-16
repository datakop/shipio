#ifndef SHIPIO_SHIP_H
#define SHIPIO_SHIP_H

#include "cocos2d.h"
#include "Brain.h"

#include <map>


class Ship : public cocos2d::Sprite {
public:
    static Ship *create();
    
    void setHealth(int health) { _health = health; }
    int getHealth() { return _health; }

    void update(float delta);
    
    void initOptions();

    ~Ship();

private:
    int _health = 100;
    float _forwardPower = 77;
    float _rotatePower = 13;
    float _maxSpeed = 150;
    float _maxAngularSpeed = 1;
    static std::map<cocos2d::EventKeyboard::KeyCode, bool> _keys;
    Brain *_brain;
    
    void _setUpEvents();
    
    bool _isKeyPressed(cocos2d::EventKeyboard::KeyCode);
};

#endif /* defined(SHIPIO_SHIP_H) */
