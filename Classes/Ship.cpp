#include "Ship.h"


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
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();

        if (rect.containsPoint(p))
            return true; // to indicate that we have consumed it.

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        Ship::touchEvent(touch);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Ship::touchEvent(cocos2d::Touch *touch) {
    CCLOG("Ship is touched.");
}
