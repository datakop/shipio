#include "MainLayer.h"

using namespace cocos2d;


bool MainLayer::init() {
    if (!Layer::init())
        return false;

    this->scheduleUpdate();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,
                                visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    _ship = Ship::create();
    _ship->setTag(10);

    auto shipBody = PhysicsBody::createBox(_ship->getContentSize(), PhysicsMaterial(0.01, 1, 0));
    shipBody->setContactTestBitmask(0xFFFFFFFF);

    _ship->setPhysicsBody(shipBody);
    _ship->setPosition(Point(visibleSize.width / 2 + origin.x,
                             visibleSize.height / 2 + origin.y));
    _ship->setOptions();
    this->addChild(_ship);

    CCLOG("%f %f", _ship->getContentSize().width, _ship->getContentSize().height);
    CCLOG("%f %f", visibleSize.width / _ship->getContentSize().width,
          visibleSize.height / _ship->getContentSize().height);


    auto bullet = PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
    bullet->setContactTestBitmask(0xFFFFFFFF);
    auto sprite = Sprite::create();

    sprite->addComponent(bullet);
    sprite->setPosition(Point(visibleSize.width / 2 + origin.x + 30,
                              visibleSize.height / 2 + origin.y));
    this->addChild(sprite);

    sprite->getPhysicsBody()->applyImpulse(Vec2(10, 0));


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void MainLayer::update(float delta) {
    if (_drawNode) removeChild(_drawNode);
    _drawNode = DrawNode::create();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 centr = Point(visibleSize.width / 2 + origin.x,
                       visibleSize.height / 2 + origin.y);


    Vec2 d(40 * cosf(_angle), 40 * sinf(_angle));
    Vec2 point2 = centr + d;

    Vec2 points[5];
    int num = 0;
    auto func = [&points, &num](PhysicsWorld &world,
                                const PhysicsRayCastInfo &info, void *data) -> bool {
        if (num < 5) {
            points[num++] = info.contact;
        }
        return true;
    };

    _world->rayCast(func, centr, point2, nullptr);

    _drawNode->drawSegment(centr, point2, 1, Color4F::RED);
    for (int i = 0; i < num; ++i) {
        _drawNode->drawDot(points[i], 3, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    }
    addChild(_drawNode);

    _angle += 1.5f * (float) M_PI / 180.0f;

    if (_ship && _ship->getHealth() < 0)
        _ship->removeFromParentAndCleanup(true);
}


bool MainLayer::onContactBegin(PhysicsContact &contact) {

    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {
        if (nodeA->getTag() == 10) {
            auto ship = static_cast<Ship *>(nodeA);
            ship->setHealth(ship->getHealth() - 10);
            nodeB->removeFromParentAndCleanup(true);
            CCLOG("shut");
        }

        if (nodeB->getTag() == 10) {
            auto ship = static_cast<Ship *>(nodeB);
            ship->setHealth(ship->getHealth() - 10);
            nodeA->removeFromParentAndCleanup(true);
            CCLOG("shut");
        }
    }

    return true;
}