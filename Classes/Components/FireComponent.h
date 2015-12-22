#ifndef SHIPIO_FIRECOMPONENT_H
#define SHIPIO_FIRECOMPONENT_H


#include "cocos2d.h"

#include "KeyboardInputComponent.h"

using namespace cocos2d;


class FireComponent : public KeyboardInputComponent {
public:
    void update(Node *node, float delta);

private:
    void _fire(Node *sender, float rot);
};


#endif //SHIPIO_FIRECOMPONENT_H
