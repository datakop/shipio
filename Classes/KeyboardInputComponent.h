#ifndef __shipio__KeyboardInputComponent__
#define __shipio__KeyboardInputComponent__

#include "cocos2d.h"

class KeyboardInputComponent {
public:
    void update(cocos2d::Sprite &sprite, float delta);

private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keys;

    bool _isKeyPressed(cocos2d::EventKeyboard::KeyCode code);
};

#endif /* defined(__shipio__KeyboardInputComponent__) */
