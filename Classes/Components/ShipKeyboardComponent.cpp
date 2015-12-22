#include "ShipKeyboardComponent.h"



void ShipKeyboardComponent::update(Node *node, float delta) {
    auto ship = static_cast<Ship *>(node);

    auto rot = ship->getRotation();
    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;

    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A)) {
        ship->getPhysicsBody()->applyImpulse(Vec2(0, ship->rotatePower), Vec2(54, 24));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D)) {
        ship->getPhysicsBody()->applyImpulse(Vec2(0, -ship->rotatePower), Vec2(54, -24));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W)) {
        ship->getPhysicsBody()->applyImpulse(ship->forwardPower * Vec2(cos(rot), -sin(rot)));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S)) {
        ship->getPhysicsBody()->applyImpulse(ship->backwardPower * Vec2(-cos(rot), sin(rot)));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_SPACE)) {
        ship->getPhysicsBody()->setAngularVelocity(0);
        ship->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}
