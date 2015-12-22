#include "KeyboardInputComponent.h"


bool KeyboardInputComponent::isKeyPressed(EventKeyboard::KeyCode code) {
    return _keys.find(code) != _keys.end();
}


bool KeyboardInputComponent::init(Node *node) {
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        _keys[keyCode] = true;
    };

    keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        _keys.erase(keyCode);
    };

    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, node);
}
