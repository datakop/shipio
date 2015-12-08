#include "MainLayer.h"
#include "Ship.h"

MainLayer::MainLayer() {}


bool MainLayer::init() {
    if (!cocos2d::Layer::init())
        return false;

    auto ship = Ship::create();
    ship->setPosition(cocos2d::Vec2(100, 100));
    this->addChild(ship, 1);

    return true;
}


MainLayer::~MainLayer() {}
