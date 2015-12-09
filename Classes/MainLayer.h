#ifndef SHIPIO_MAINLAYER_H
#define SHIPIO_MAINLAYER_H

#include "cocos2d.h"

class MainLayer : public cocos2d::Layer {
   private:
    virtual bool init();

   public:
    CREATE_FUNC(MainLayer);

    MainLayer();
    ~MainLayer();
};

#endif  // SHIPIO_MAINLAYER_H
