//
// Created by ospanoff on 04.12.15.
//

#include "MainLayer.h"

bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
        return false;

    scheduleUpdate();

    return true;
}

void MainLayer::update(float deltaTime)
{

}