//
// Created by ospanoff on 21.12.15.
//

#ifndef __shipio__ENDPOINT_H__
#define __shipio__ENDPOINT_H__


#include "cocos2d.h"

class EndPoint : public cocos2d::Sprite{
public:
    static EndPoint *create();
    bool initOptions();

};

#endif //SHIPIO_ENDPOINT_H
