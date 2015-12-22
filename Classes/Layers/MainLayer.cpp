#include "MainLayer.h"

using namespace cocos2d;


bool MainLayer::init() {
    if (!Layer::init())
        return false;

    this->scheduleUpdate();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto entityManager = EntityManager::getInstance();


    for (auto wallEdge : entityManager->getWallEdges()) {
        this->addChild(wallEdge);
    }

    this->addChild(entityManager->createScreenBox());
    this->addChild(entityManager->createShipAtPosition());
    this->addChild(entityManager->createEndPointAtPosition());
    this->addChild(entityManager->createAsteroidAtPosition(Point(visibleSize.width / 2 + origin.x + 30,
                                                                 visibleSize.height / 2 + origin.y + 100)));

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void MainLayer::update(float delta) {
    if (_drawNode) removeChild(_drawNode);
    _drawNode = DrawNode::create();


    for (int i = 1; i < _dotMap.size(); i += 2) {
        //CCLOG("ALL GOOD %lf %lf\n", _dotMap[i].first, _dotMap[i].second);
        _drawNode->drawDot(Vec2(_dotMap[i].first, _dotMap[i].second), 3, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
        //CCLOG("ALL GOOD2 %lf %lf %lf %lf\n", _dotMap[i - 1].first, _dotMap[i - 1].second, _dotMap[i].first, _dotMap[i].second);
        _drawNode->drawLine(Vec2(_dotMap[i - 1].first, _dotMap[i - 1].second),
                            Vec2(_dotMap[i].first, _dotMap[i].second),
                            Color4F(1.0f, 1.0f, 1.0f, 1.0f));

//        _drawNode->drawQuadBezier(Vec2(_dotMap[i-1].first, _dotMap[i-1].second),
//                                  Vec2(_dotMap[i].first, _dotMap[i].second),
//                                  Vec2(_dotMap[i + 1].first, _dotMap[i].second),
//                                  64, Color4F(1.0f, 0.0f, 1.0f, 1.0f));
    }


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

//    if (_ship && _ship->getHealth() < 0)
//        _ship->removeFromParentAndCleanup(true);
}


bool MainLayer::onContactBegin(PhysicsContact &contact) {

    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

//    if (nodeA && nodeB) {
//        if (nodeA->getTag() == 10) {
//            auto ship = static_cast<Ship *>(nodeA);
//            ship->setHealth(ship->getHealth() - 10);
//            nodeB->removeFromParentAndCleanup(true);
//            CCLOG("shut");
//        }
//
//        if (nodeB->getTag() == 10) {
//            auto ship = static_cast<Ship *>(nodeB);
//            ship->setHealth(ship->getHealth() - 10);
//            nodeA->removeFromParentAndCleanup(true);
//            CCLOG("shut");
//        }
//    }

    return true;
}

MainLayer::~MainLayer() {
    delete this->_entityManager;
}
