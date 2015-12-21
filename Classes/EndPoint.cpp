//
// Created by ospanoff on 21.12.15.
//
#include "EndPoint.h"

using  namespace cocos2d;

EndPoint *EndPoint::create() {
    EndPoint *obj = new EndPoint();
    if (obj->initWithFile("end_point2.png")) {
        obj->autorelease();
        obj->initOptions();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool EndPoint::initOptions() {
    //CCLOG("%f", this->getContentSize().width);

    auto body = PhysicsBody::createBox(Size(this->getContentSize().width - 30,
                                            this->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    this->setPhysicsBody(body);

    return true;
}
