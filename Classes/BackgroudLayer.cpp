#include "BackgroudLayer.h"

using namespace cocos2d;


bool BackgroudLayer::init() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Todo: Move to EntityManager
    auto bgLayer = Sprite::create("bg.jpg");
    bgLayer->setScale(visibleSize.height / bgLayer->getContentSize().height);
    bgLayer->setPosition(Point(visibleSize.width / 2 + origin.x,
                               visibleSize.height / 2 + origin.y));

    this->addChild(bgLayer);
}
