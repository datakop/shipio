#include "Asteroid.h"

using namespace cocos2d;


Asteroid *Asteroid::create() {
    Asteroid *obj = new Asteroid();
    if (obj->initWithFile("asteroid.png")) {
        obj->autorelease();
        obj->initOptions();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}


bool Asteroid::initOptions() {
    CCLOG("%f", this->getContentSize().width);

    auto body = PhysicsBody::createBox(Size(this->getContentSize().width - 30,
                                            this->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    this->setPhysicsBody(body);

    return true;
}
