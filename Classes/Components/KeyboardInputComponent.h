#ifndef SHIPIO_KeyboardInputComponent_H
#define SHIPIO_KeyboardInputComponent_H

#include "map"

#include "cocos2d.h"

#include "GameComponent.h"

using namespace std;
using namespace cocos2d;


class KeyboardInputComponent : public GameComponent {
public:
    virtual bool init(cocos2d::Node *node);

    virtual void update(cocos2d::Node *node, float delta) = 0;

    bool isKeyPressed(EventKeyboard::KeyCode code);

private:
    map<EventKeyboard::KeyCode, bool> _keys;
};


#endif //SHIPIO_KeyboardInputComponent_H
