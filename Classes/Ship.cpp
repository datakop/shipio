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
    this->scheduleUpdate();
}

void Ship::setOptions() {
    this->getPhysicsBody()->setVelocityLimit(_maxSpeed);
    this->getPhysicsBody()->setAngularVelocityLimit(_maxAngularSpeed);
}


void Ship::addEvents() {
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        keys[keyCode] = true;
        auto vel = this->getPhysicsBody()->getVelocity();
        CCLOG("%f %f\n", vel.x, vel.y);
    };

    keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        keys.erase(keyCode);
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

Ship::~Ship() {
    this->getEventDispatcher()->removeAllEventListeners();
}

bool Ship::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
    return keys.find(code) != keys.end();
}

void Ship::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it

    auto rot = this->getRotation();
    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;

    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A)) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, _rotatePower), Vec2(54, 24));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D)) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, -_rotatePower), Vec2(54, -24));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W)) {
        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(cos(rot), -sin(rot)));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S)) {
        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(-cos(rot), sin(rot)));
    }
    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_SPACE)) {
        this->getPhysicsBody()->setAngularVelocity(0);
        this->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, bool> Ship::keys;