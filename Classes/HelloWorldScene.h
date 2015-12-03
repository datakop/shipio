#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer, public b2ContactListener
{
public:
    static cocos2d::Scene* createScene();

    cocos2d::Sprite *spaceship;

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
