//
//  Ship.h
//  shipio
//
//  Created by Bors Kopin on 05.12.15.
//
//

#ifndef __shipio__Ship__
#define __shipio__Ship__

#include "cocos2d.h"

class MySprite : public cocos2d::Sprite
{
public:
    MySprite();
    ~MySprite();
    static MySprite* create();
    
    void initOptions();
    
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
    
private:
    
};

#endif /* defined(__shipio__Ship__) */
