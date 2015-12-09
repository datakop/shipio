#include <cmath>

#include "ChipmunkTestLayer.h"
#include "chipmunk.h"
#include "physics/CCPhysicsHelper.h"

enum {
    kTagParentNode = 1,
};

enum {
    Z_PHYSICS_DEBUG = 100,
};

ChipmunkTestLayer::ChipmunkTestLayer(){};

bool ChipmunkTestLayer::init() {
    if (!cocos2d::Layer::init()) return false;

    scheduleUpdate();

    initPhysics();

    // Use batch node. Faster
    cocos2d::SpriteBatchNode *parent =
        cocos2d::SpriteBatchNode::create("shipio.png", 100);
    _pSpriteTexture = parent->getTexture();

    this->addChild(parent, 10, kTagParentNode);

    this->addShipio(cocos2d::Vec2(200, 200));

    addEvents();

    return true;
}

void ChipmunkTestLayer::update(float delta) {
    int steps = 2;
    float dt =
        cocos2d::Director::getInstance()->getAnimationInterval() / (float)steps;

    //    CCLOG("%f %f", cpBodyGetRot(_shipio->getCPBody()).x,
    //    cpBodyGetRot(_shipio->getCPBody()).y);
    //    CCLOG("%f %f", _shipio->getCPBody()->v.x, _shipio->getCPBody()->v.y);

    for (int i = 0; i < steps; i++) {
        cpSpaceStep(_pSpace, dt);
    }
}

void ChipmunkTestLayer::initPhysics() {
    // Set up Physics Space
    _pSpace = cpSpaceNew();
    _pSpace->gravity = cpv(0, 0);

    initWall();

    // Physics debug layer
    auto m_pDebugLayer = cocos2d::extension::PhysicsDebugNode::create(_pSpace);
    this->addChild(m_pDebugLayer, Z_PHYSICS_DEBUG);
}

void ChipmunkTestLayer::initWall() {
    // Set up walls
    _pWalls[0] = cpSegmentShapeNew(_pSpace->staticBody, cpv(0, 0), cpv(1000, 0),
                                   0.0f);  // bottom
    _pWalls[1] = cpSegmentShapeNew(_pSpace->staticBody, cpv(0, 500),
                                   cpv(1000, 500), 0.0f);  // top
    _pWalls[2] = cpSegmentShapeNew(_pSpace->staticBody, cpv(0, 500), cpv(0, 0),
                                   0.0f);  // left
    _pWalls[3] = cpSegmentShapeNew(_pSpace->staticBody, cpv(1000, 500),
                                   cpv(1000, 0), 0.0f);  // right

    for (int i = 0; i < 4; i++) {
        _pWalls[i]->e = 1.0f;
        _pWalls[i]->u = 1.0f;
        cpSpaceAddStaticShape(_pSpace, _pWalls[i]);
    }
}

void ChipmunkTestLayer::addShipio(cocos2d::Vec2 pos) {
    auto parent = cocos2d::Node::getChildByTag(kTagParentNode);
    _shipio = newPhysicsSprite();

    parent->addChild(_shipio);
    _shipio->setPosition(pos);
    _shipio->getCPBody()->p = cpv(pos.x, pos.y);
}

cocos2d::extension::PhysicsSprite *ChipmunkTestLayer::newPhysicsSprite() {
    int num = 4;
    cpVect verts[] = {
        cpv(-54, -24),  // bottom right
        cpv(-54, 24),   // bottom left
        cpv(54, 24),    // top left
        cpv(54, -24),   // top right
    };

    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
    cpSpaceAddBody(_pSpace, body);

    cpShape *shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f;
    shape->u = 0.5f;
    cpSpaceAddShape(_pSpace, shape);

    cpShape *shape2 = cpCircleShapeNew(body, 5.0, cpv(54, -24));
    cpSpaceAddShape(_pSpace, shape2);

    auto sprite =
        cocos2d::extension::PhysicsSprite::createWithTexture(_pSpriteTexture);
    sprite->setCPBody(body);

    return sprite;
}

void ChipmunkTestLayer::addNewSpriteAtPosition(cocos2d::Vec2 pos) {
    auto parent = cocos2d::Node::getChildByTag(kTagParentNode);
    auto sprite = newPhysicsSprite();

    parent->addChild(sprite);
    sprite->setPosition(pos);
    sprite->getCPBody()->p = cpv(pos.x, pos.y);
}

void ChipmunkTestLayer::addNewBallAtPosition(cocos2d::Vec2 pos) {
    cpBody *body = cpBodyNew(0.01f, cpMomentForCircle(0.01f, 0, 1, cpvzero));
    cpSpaceAddBody(_pSpace, body);

    cpShape *shape = cpCircleShapeNew(body, 1.0, cpvzero);
    shape->e = 1.0f;
    cpSpaceAddShape(_pSpace, shape);

    auto sprite = cocos2d::extension::PhysicsSprite::create();
    sprite->setCPBody(body);

    this->addChild(sprite);

    sprite->setPosition(pos);
    sprite->getCPBody()->p = cpv(pos.x, pos.y);
}

cpVect perp(cpVect vect, float F, int p) {
    float x = vect.x, y = vect.y;
    float x1, y1;

    if (x == 0) {
        y1 = 0;
        x1 = F;
    } else {
        float tmp = sqrt(pow(F, 2) / (pow(y / x, 2) + 1));
        x1 = -(y * tmp) / x;
        y1 = tmp;
    }

    if (p * (x1 * y - x * y1) < 0) {
        x1 *= -1;
        y1 *= -1;
    }

    return cpv(x1, y1);
}

void ChipmunkTestLayer::addEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [&](cocos2d::Touch *touch,
                                      cocos2d::Event *event) { return true; };

    touchListener->onTouchEnded = [=](cocos2d::Touch *touch,
                                      cocos2d::Event *event) {
        //        addNewSpriteAtPosition(touch->getLocation());
        addNewBallAtPosition(touch->getLocation());
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        touchListener, this);

    auto keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode keyCode,
                                        cocos2d::Event *event) {
        auto target = static_cast<cocos2d::extension::PhysicsSprite *>(
            event->getCurrentTarget());
        auto rot = cpBodyGetRot(target->getCPBody());

        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                cpBodyApplyImpulse(target->getCPBody(), cpv(0, 10),
                                   cpv(54, 24));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_Q:
                cpBodySetAngle(target->getCPBody(),
                               target->getCPBody()->a - 0.2);
                CCLOG("LOG");
                CCLOG("%f %f", rot.x, rot.y);
                CCLOG("%f %f", perp(rot, 20, -1).x, perp(rot, 20, -1).y);
                break;

            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:

                cpBodyApplyImpulse(target->getCPBody(), cpv(0, -10),
                                   cpv(54, -24));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_E:
                cpBodySetAngle(target->getCPBody(),
                               target->getCPBody()->a + 0.2);
                break;

            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                cpBodyApplyImpulse(target->getCPBody(),
                                   cpv(50 * rot.x, 50 * rot.y), cpv(0.0, 0.0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                cpBodyApplyImpulse(target->getCPBody(),
                                   cpv(-50 * rot.x, -50 * rot.y),
                                   cpv(0.0, 0.0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
                cpBodySetTorque(target->getCPBody(), 0.0);
                cpBodySetVel(target->getCPBody(), cpvzero);
                cpBodySetAngVel(target->getCPBody(), 0.0);
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        keyboardListener, _shipio);
}

void ChipmunkTestLayer::draw(cocos2d::Renderer *renderer,
                             const cocos2d::Mat4 &transform, uint32_t flags) {
    cocos2d::DrawPrimitives::setDrawColor4B(255, 0, 128, 128);

    //    cocos2d::DrawPrimitives::drawLine(_shipio->getPosition(),
    //                                      cocos2d::PhysicsHelper::cpv2point(perp(_shipio->getCPBody()->rot,
    //                                      20, -1))
    //                                      );

    cocos2d::DrawPrimitives::drawLine(
        _shipio->getPosition(),
        cocos2d::PhysicsHelper::cpv2point(cpBodyLocal2World(
            _shipio->getCPBody(), perp(_shipio->getCPBody()->rot, 100, -1))));

    cocos2d::DrawPrimitives::drawLine(
        _shipio->getPosition(),
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(100, 0))));

    cocos2d::DrawPrimitives::drawLine(
        _shipio->getPosition(),
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(0, 100))));

    cocos2d::DrawPrimitives::setDrawColor4B(0, 255, 255, 128);
    cocos2d::DrawPrimitives::drawLine(
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(54, -20 - 24))),
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(54, -24))));

    cocos2d::DrawPrimitives::drawLine(
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(54, 20 + 24))),
        cocos2d::PhysicsHelper::cpv2point(
            cpBodyLocal2World(_shipio->getCPBody(), cpv(54, 24))));

    cocos2d::Vec2 p = cocos2d::PhysicsHelper::cpv2point(cpBodyLocal2World(
        _shipio->getCPBody(), perp(_shipio->getCPBody()->rot, 100, -1)));
    //    CCLOG("%f %f", p.x, p.y);
}

ChipmunkTestLayer::~ChipmunkTestLayer() {
    for (int i = 0; i < 4; i++) cpShapeFree(_pWalls[i]);
    cpSpaceFree(_pSpace);

    this->getEventDispatcher()->removeAllEventListeners();
}
