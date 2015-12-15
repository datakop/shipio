#include "Ship.h"

using namespace cocos2d;

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
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        auto rot = this->getRotation();
        rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;
        
        int power = 1000;

        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                this->getPhysicsBody()->applyImpulse(Vec2(0, power/10), Vec2(54, 24));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                this->getPhysicsBody()->applyImpulse(Vec2(0, -power/10), Vec2(54, -24));
                break;


            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                this->getPhysicsBody()->applyImpulse(Vec2(power * cosf(rot), power * sinf(-rot)));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                this->getPhysicsBody()->applyImpulse(Vec2(-power * cosf(rot), power * sinf(rot)));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
                this->getPhysicsBody()->setAngularVelocity(0);
                this->getPhysicsBody()->setVelocity(Vec2(0, 0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_T: {
                cocos2d::Scene *scene = cocos2d::Director::getInstance()->getRunningScene();
                auto layer = scene->getChildByTag(100);

                auto bulletSprite = Sprite::create();
                auto bullet = PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
                bullet->setContactTestBitmask(0xFFFFFFFF);
                bulletSprite->addComponent(bullet);
                
//                bulletSprite->setPosition(Vec2(cosf(rot) + 10, sinf(-rot)));
                bulletSprite->setPosition(this->getPosition() + Vec2(50, 0));
                layer->addChild(bulletSprite);
                
                bulletSprite->getPhysicsBody()->applyImpulse(Vec2(cosf(rot)*10, sinf(-rot)));
                break;
            }
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

Ship::~Ship() {
    this->getEventDispatcher()->removeAllEventListeners();
}
