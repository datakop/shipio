#include <iostream>

#include "SimpleComponent.h"

#include "../Entities/Ship.h"

bool SimpleComponent::init(cocos2d::Node *node) {
    auto ship = static_cast<Ship *>(node);
    std::cout << "SimpleComponent::init" << ship->forwardPower << std::endl;

    return true;
}


void SimpleComponent::update(cocos2d::Node *node, float delta) {
    auto ship = static_cast<Ship *>(node);
}
