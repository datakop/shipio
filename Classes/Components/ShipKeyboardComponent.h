#ifndef __shipio__KeyboardInputComponent__
#define __shipio__KeyboardInputComponent__


#include "cocos2d.h"

#include "KeyboardInputComponent.h"

#include "../Entities/Ship.h"

using namespace cocos2d;


class ShipKeyboardComponent : public KeyboardInputComponent {
public:
    void update(cocos2d::Node *node, float delta);
};


#endif /* defined(__shipio__KeyboardInputComponent__) */
