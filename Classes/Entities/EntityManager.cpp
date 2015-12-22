#include <vector>

#include "EntityManager.h"

#include "../Components/SimpleComponent.h"
#include "../Components/FireComponent.h"
#include "../Components/ShipKeyboardComponent.h"

#include "../MapGenerator/MapGenerator.h"


static EntityManager *s_SharedEntityManager = nullptr;


EntityManager *EntityManager::getInstance() {
    if (!s_SharedEntityManager) {
        s_SharedEntityManager = new(std::nothrow) EntityManager();
        CCASSERT(s_SharedEntityManager, "FATAL: Not enough memory");
        s_SharedEntityManager->init();
    }

    return s_SharedEntityManager;
}

void EntityManager::init() {
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    auto m = new MapGenerator();
    pair<vector<pair<double, double> >, pair<pair<double, double>, pair<double, double> > > m_c_c;
    m_c_c = m->main(_visibleSize);

    auto dotMap = m_c_c.first;
    _start = m_c_c.second.first;
    _end = m_c_c.second.second;

    for (int i = 1; i < dotMap.size(); i += 2) {
        auto seg = PhysicsBody::createEdgeSegment(Vec2(dotMap[i - 1].first, dotMap[i - 1].second),
                                                  Vec2(dotMap[i].first, dotMap[i].second));
        auto sprite = new Sprite();
        sprite->setPhysicsBody(seg);
        _wallEdges.push_back(sprite);
    }

    delete m;
}


Sprite *EntityManager::createAsteroidAtPosition(cocos2d::Vec2 pos) {
    auto asteroid = Sprite::create("asteroid.png");
    asteroid->setPosition(pos);

    auto body = PhysicsBody::createBox(Size(asteroid->getContentSize().width - 30,
                                            asteroid->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    asteroid->setPhysicsBody(body);

    _entities.push_back(asteroid);
    return asteroid;
}

Ship *EntityManager::createShipAtPosition(cocos2d::Vec2 pos) {
    std::vector<GameComponent *> components = {
            new SimpleComponent(),
            new FireComponent(),
            new ShipKeyboardComponent()
    };
    _ship = Ship::create(components);
    _ship->setPosition(Point((float) (_start.first),
                             (float) (_start.second)));

    auto shipBody = PhysicsBody::createBox(_ship->getContentSize(), PhysicsMaterial(0.01, 0.5, 0));
    shipBody->setContactTestBitmask(0x12);

    _ship->setPhysicsBody(shipBody);
    _ship->getPhysicsBody()->setVelocityLimit(_ship->maxSpeed);
    _ship->getPhysicsBody()->setAngularVelocityLimit(_ship->maxAngularSpeed);

    _entities.push_back(_ship);
    return _ship;
}

Sprite *EntityManager::createEndPointAtPosition(cocos2d::Vec2 pos) {
    auto endPoint = Sprite::create("end_point2.png");
    endPoint->setPosition(Point((float) (_end.first + 7),
                                (float) (_end.second + 7)));

    auto body = PhysicsBody::createBox(Size(endPoint->getContentSize().width - 30,
                                            endPoint->getContentSize().height - 30),
                                       PhysicsMaterial(1, 0.5, 0));
    body->setContactTestBitmask(0x12);
    endPoint->setPhysicsBody(body);

    _entities.push_back(endPoint);
    return endPoint;
}

Sprite *EntityManager::createBulletAtPosition(cocos2d::Vec2 pos, float rot) {
    auto bulletSprite = Sprite::create();
    auto bullet = PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
    bullet->setContactTestBitmask(0x12);
    bulletSprite->addComponent(bullet);

    bulletSprite->setPosition(pos + Vec2(50, 0));

    bulletSprite->getPhysicsBody()->applyImpulse(Vec2(cosf(rot) * 10, sinf(-rot)));

    _entities.push_back(bulletSprite);
    return bulletSprite;
}

Node *EntityManager::createScreenBox() {
    auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(_visibleSize.width / 2 + _origin.x,
                                _visibleSize.height / 2 + _origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    _entities.push_back(edgeNode);
    return edgeNode;
}


EntityManager::~EntityManager() {
    // clean up
    // _entities, _ship, _wallEdges
}
