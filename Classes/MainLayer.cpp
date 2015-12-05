//
// Created by ospanoff on 04.12.15.
//

#include "MainLayer.h"
#include "Ship.h"


using namespace cocos2d;

bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
        return false;

    scheduleUpdate();
    
    MySprite* _mySprite = MySprite::create();
    _mySprite->setPosition(Vec2(100, 100));
    this->addChild(_mySprite, 1); // add the sprite someplace.

    return true;
}

void MainLayer::update(float deltaTime)
{

}