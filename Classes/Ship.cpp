#include "Ship.h"

USING_NS_CC;

Ship *Ship::create() {
    Ship *ship = new Ship();
    if (ship->initWithFile("shipio.png")) {
        ship->autorelease();
        ship->initOptions();
        ship->addEvents();

        return ship;
    }

    CC_SAFE_DELETE(ship);

    return nullptr;
}


void Ship::initOptions() {
    // do things here like setTag(), setPosition(), any custom logic.
}


void Ship::addEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *event) { return true; };
    touchListener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) { };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        auto rot = this->getRotation();
        rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;
        CCLOG("%f", rot);

        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                this->getPhysicsBody()->applyImpulse(Vec2(0, 100), Vec2(54, 24));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                this->getPhysicsBody()->applyImpulse(Vec2(0, -100), Vec2(54, -24));
                break;


            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                this->getPhysicsBody()->applyImpulse(Vec2(100 * cosf(rot), 100 * sinf(-rot)));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                this->getPhysicsBody()->applyImpulse(Vec2(-100 * cosf(rot), 100 * sinf(rot)));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
                this->getPhysicsBody()->setAngularVelocity(0);
                this->getPhysicsBody()->setVelocity(Vec2(0, 0));
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}