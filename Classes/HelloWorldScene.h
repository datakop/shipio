#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);

    void onKeyPressed(EventKeyboard::KeyCode, Event*);
    void onKeyReleased(EventKeyboard::KeyCode, Event*);

    void update(float) override;

private:
    b2World *_world;
    b2Body *_bodies[3];
};

#endif // __HELLOWORLD_SCENE_H__
