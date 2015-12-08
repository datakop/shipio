#ifndef __shipio__ChipmunkTestLayer__
#define __shipio__ChipmunkTestLayer__

#include "cocos2d.h"
#include "cocos-ext.h"


class ChipmunkTestLayer : public cocos2d::Layer {
private:
    cpSpace *_pSpace;
    cpShape *_pWalls[4];
    cocos2d::Texture2D *_pSpriteTexture;
    
    cocos2d::extension::PhysicsSprite *_shipio;
    
    virtual bool init();
    void update(float delta);
    
    void initPhysics();
    void initWall();
    
    void addEvents();
    
    void addNewSpriteAtPosition(cocos2d::Vec2 pos);
    
    void addShipio(cocos2d::Vec2 pos);

    cocos2d::extension::PhysicsSprite *newPhysicsSprite();
public:
    CREATE_FUNC(ChipmunkTestLayer);
    ChipmunkTestLayer();
    ~ChipmunkTestLayer();
};

#endif /* defined(__shipio__ChipmunkTestLayer__) */
