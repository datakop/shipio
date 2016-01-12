#include "MainMenuScene.h"
#include "AboutScene.h"
#include "Layers/MainLayer.h"
#include "Layers/BackgroudLayer.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("bg.jpg");
    backgroundSprite->setScale(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    this->addChild(backgroundSprite);

    auto label = Label::createWithTTF("The Shipio game", "fonts/Marker Felt.ttf", 32);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 5 / 6 + origin.y));
    this->addChild(label);
    
    auto aboutItem = MenuItemImage::create("about.jpg", "about.jpg", CC_CALLBACK_1(MainMenuScene::GoToAboutScene, this));
    float scale = 0.1;
    aboutItem->setScale(scale);
    aboutItem->setPosition(Point(visibleSize.width + origin.x - scale * aboutItem->getContentSize().width, origin.y + scale * aboutItem->getContentSize().width));

    auto playItem = MenuItemImage::create("play.jpg", "play_clicked.jpg", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    scale = 0.5;
    playItem->setScale(scale);
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    Vector<MenuItem *> items;
    items.pushBack(aboutItem);
    items.pushBack(playItem);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
    auto scene = Scene::createWithPhysics();
    auto physWorld = scene->getPhysicsWorld();
    physWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    physWorld->setGravity(Vec2(0, 0));

    auto layer = MainLayer::create();
    layer->setPhysicsWorld(physWorld);
    layer->setTag(MainLayer::TAG);

    scene->addChild(layer);

    auto bgLayer = BackgroudLayer::create();
    scene->addChild(bgLayer, -1);

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::GoToAboutScene(cocos2d::Ref *sender)
{
    auto scene = AboutScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

