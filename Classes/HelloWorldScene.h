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

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void update(float) override;

private:
    Sprite *spaceship;

    b2World *world;
    float deltaTime;

    Sprite *ball;
    bool existBall;
    float ballX;
    float ballY;
    int dragOffsetStartX;
    int dragOffsetEndX;
    int dragOffsetStartY;
    int dragOffsetEndY;
    float powerMultiplier;
    b2Body *ballBody;
    b2CircleShape ballShape;
    b2BodyDef ballBodyDef;
    void defineBall();

    Sprite *points[32];

    void addWall(float w,float h,float px,float py);
    void simulateTrajectory(b2Vec2 coord);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
