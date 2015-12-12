#include "MainLayer.h"

USING_NS_CC;

bool MainLayer::init() {
    if (!Layer::init())
        return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    _ship = Ship::create();
    auto shipBody = PhysicsBody::createBox(_ship->getContentSize(), PhysicsMaterial(0.001, 1, 0));
    _ship->setPhysicsBody(shipBody);
    _ship->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(_ship);

    return true;
}