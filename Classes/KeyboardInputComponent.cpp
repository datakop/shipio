#include "KeyboardInputComponent.h"

bool KeyboardInputComponent::_isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
    return _keys.find(code) != _keys.end();
}

void KeyboardInputComponent::update(cocos2d::Sprite &sprite, float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it

//    auto rot = this->getRotation();
//    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;
//    
//    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
//        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A)) {
//        this->getPhysicsBody()->applyImpulse(Vec2(0, _rotatePower), Vec2(54, 24));
//    }
//    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
//        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D)) {
//        this->getPhysicsBody()->applyImpulse(Vec2(0, -_rotatePower), Vec2(54, -24));
//    }
//    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) ||
//        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W)) {
//        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(cos(rot), -sin(rot)));
//    }
//    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
//        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S)) {
//        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(-cos(rot), sin(rot)));
//    }
//    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_SPACE)) {
//        this->getPhysicsBody()->setAngularVelocity(0);
//        this->getPhysicsBody()->setVelocity(Vec2(0, 0));
//    }
}
