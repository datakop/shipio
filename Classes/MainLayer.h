#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MainLayer : public cocos2d::Layer {
public:
    CREATE_FUNC(MainLayer);

    virtual bool init();
};

#endif //SHIPIO_MAINLAYER_H
