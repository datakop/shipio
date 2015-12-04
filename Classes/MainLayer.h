#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class MainLayer : public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(MainLayer);

    void update(float) override;
};


#endif //SHIPIO_MAINLAYER_H
