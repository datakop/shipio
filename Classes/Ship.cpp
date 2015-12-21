#include "Ship.h"

using namespace cocos2d;

Ship *Ship::create() {
    Ship *ship = new Ship();
    if (ship->initWithFile("shipio.png")) {
        ship->autorelease();
        ship->initOptions();
        return ship;
    }
    CC_SAFE_DELETE(ship);
    return nullptr;
}


void Ship::initOptions() {
    this->scheduleUpdate();

    this->setTag(10);

    auto shipBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.01, 0.5, 0));
    shipBody->setContactTestBitmask(0xFFFFFFFF);

    this->setPhysicsBody(shipBody);
    this->getPhysicsBody()->setVelocityLimit(_maxSpeed);
    this->getPhysicsBody()->setAngularVelocityLimit(_maxAngularSpeed);

    this->_setUpEvents();
}

void Ship::_fire(float rot) {

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

}


void Ship::_setUpEvents() {
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        _keys[keyCode] = true;
        auto vel = this->getPhysicsBody()->getVelocity();
        CCLOG("%f %f\n", vel.x, vel.y);
    };

    keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        _keys.erase(keyCode);
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

Ship::~Ship() {
    this->getEventDispatcher()->removeAllEventListeners();
}

bool Ship::_isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
    return _keys.find(code) != _keys.end();
}

void Ship::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it

    auto rot = this->getRotation();
    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;

    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A)) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, _rotatePower), Vec2(54, 24));
    }
    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D)) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, -_rotatePower), Vec2(54, -24));
    }
    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W)) {
        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(cos(rot), -sin(rot)));
    }
    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        _isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S)) {
        this->getPhysicsBody()->applyImpulse(_forwardPower * Vec2(-cos(rot), sin(rot)));
    }
    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_SPACE)) {
        this->getPhysicsBody()->setAngularVelocity(0);
        this->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
    if (_isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_T)) {
        this->_fire(rot);
    }
}

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, bool> Ship::_keys;

