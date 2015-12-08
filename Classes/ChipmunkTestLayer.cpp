#include "ChipmunkTestLayer.h"

#include "chipmunk.h"

enum {
    kTagParentNode = 1,
};

enum {
    Z_PHYSICS_DEBUG = 100,
};


ChipmunkTestLayer::ChipmunkTestLayer() {
};


bool ChipmunkTestLayer::init() {
    if(!cocos2d::Layer::init())
        return false;

    scheduleUpdate();

    initPhysics();


    // Use batch node. Faster
    cocos2d::SpriteBatchNode *parent = cocos2d::SpriteBatchNode::create("shipio.png", 100);
    _pSpriteTexture = parent->getTexture();

    this->addChild(parent, 10, kTagParentNode);

    this->addShipio(cocos2d::Vec2(200,200));

    addEvents();

    return true;
}

void ChipmunkTestLayer::update(float delta)
{
    int steps = 2;
    float dt = cocos2d::Director::getInstance()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(_pSpace, dt);
    }
}


void ChipmunkTestLayer::initPhysics() {
    // Set up Physics Space
    _pSpace = cpSpaceNew();
    _pSpace->gravity = cpv(0, 0);

    // Physics debug layer
    auto m_pDebugLayer = cocos2d::extension::PhysicsDebugNode::create(_pSpace);
    this->addChild(m_pDebugLayer, Z_PHYSICS_DEBUG);
}


void ChipmunkTestLayer::initWall() {
    // Set up walls
    _pWalls[0] = cpSegmentShapeNew(_pSpace->staticBody,
                                   cpv(0,0), cpv(480, 0), 0.0f); // bottom
    _pWalls[1] = cpSegmentShapeNew(_pSpace->staticBody,
                                   cpv(0, 320), cpv(480, 320), 0.0f); // top
    _pWalls[2] = cpSegmentShapeNew(_pSpace->staticBody,
                                   cpv(0,320), cpv(0,0), 0.0f); // left
    _pWalls[3] = cpSegmentShapeNew(_pSpace->staticBody,
                                   cpv(480, 320), cpv(480, 0), 0.0f); // right

    for( int i=0;i<4;i++) {
        _pWalls[i]->e = 1.0f; _pWalls[i]->u = 1.0f;
        cpSpaceAddStaticShape(_pSpace, _pWalls[i] );
    }

}

void ChipmunkTestLayer::addShipio(cocos2d::Vec2 pos) {
    auto parent = cocos2d::Node::getChildByTag(kTagParentNode);
    _shipio = newPhysicsSprite();

    parent->addChild(_shipio);
    _shipio->setPosition(pos);
    _shipio->getCPBody()->p = cpv(pos.x, pos.y);
}


cocos2d::extension::PhysicsSprite* ChipmunkTestLayer::newPhysicsSprite() {
    int num = 4;
    cpVect verts[] = {cpv(-24,-54), cpv(-24, 54), cpv( 24, 54), cpv( 24,-54),};

    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
    cpSpaceAddBody(_pSpace, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f; shape->u = 0.5f;
    cpSpaceAddShape(_pSpace, shape);

    auto sprite = cocos2d::extension::PhysicsSprite::createWithTexture(_pSpriteTexture);
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


void ChipmunkTestLayer::addEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *event) {
        return true;
    };

    touchListener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        addNewSpriteAtPosition(touch->getLocation());
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
        auto target = static_cast<cocos2d::extension::PhysicsSprite*>(event->getCurrentTarget());

        switch(keyCode){
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                cpBodyApplyImpulse(target->getCPBody(), cpv(-10.0, 0.0), cpv(12.0, 54.0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                cpBodyApplyImpulse(target->getCPBody(), cpv(10.0, 0), cpv(12.0, 54.0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                cpBodyApplyImpulse(target->getCPBody(), cpv(0.0, 20.0), cpv(0.0, 0.0));
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                cpBodyApplyImpulse(target->getCPBody(), cpv(0.0, -20.0), cpv(0.0, 0.0));
                break;
            default:
                break;

        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, _shipio);
}


ChipmunkTestLayer::~ChipmunkTestLayer() {
    for( int i=0;i<4;i++)
        cpShapeFree(_pWalls[i]);
    cpSpaceFree(_pSpace);

    this->getEventDispatcher()->removeAllEventListeners();
}
