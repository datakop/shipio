#include <iostream>

#include "HelloWorldScene.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"

#define SCALE_RATIO 32.0f

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    _world = new b2World(gravity);

    //body definition
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    //shape definition
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;

    //create identical bodies in different positions
    float ctr_x = visibleSize.width / SCALE_RATIO / 2;
    float ctr_y = visibleSize.height / SCALE_RATIO / 2;
    for (int i = 0; i < 3; i++) {
        myBodyDef.position.Set((i + 1) * ctr_x / 2, (i + 1) * ctr_y / 2);
        _bodies[i] = _world->CreateBody(&myBodyDef);
        _bodies[i]->CreateFixture(&myFixtureDef);
    }

    //a static floor to drop things on
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    polygonShape.SetAsBox(visibleSize.width, 1, b2Vec2(visibleSize.width / 2, 0), 0);
    _world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    this->addChild(B2DebugDrawLayer::create(_world, SCALE_RATIO), 9999);


    scheduleUpdate();

    return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_Q:
            //apply gradual force upwards
            _bodies[0]->ApplyForce(b2Vec2(0, 50 * 61), _bodies[0]->GetWorldCenter(), true);
            break;
        case EventKeyboard::KeyCode::KEY_W:
            //apply immediate force upwards
            _bodies[1]->ApplyLinearImpulse(b2Vec2(0, 50), _bodies[1]->GetWorldCenter(), true);
            break;
        case EventKeyboard::KeyCode::KEY_E:
            //teleport or 'warp' to new location
            _bodies[2]->SetTransform(b2Vec2(10,20), 0);
            _bodies[2]->SetAwake(true);
            break;
        default:
            break;
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
//    log("Key with keycode %d released", keyCode);
}

void HelloWorld::update(float dt) {
    int positionIterations = 10;
    int velocityIterations = 10;

    _world->Step(dt, velocityIterations, positionIterations);

    _world->ClearForces();
    _world->DrawDebugData();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
