//
//  Asteroid.h
//  shipio
//
//  Created by Bors Kopin on 16.12.15.
//
//

#ifndef __shipio__Asteroid__
#define __shipio__Asteroid__

#include "cocos2d.h"

class Asteroid : public cocos2d::Sprite {
public:
    static Asteroid *create();

    bool initOptions();
};

#endif /* defined(__shipio__Asteroid__) */
