#include <iostream>

#include "Ship.h"


using namespace cocos2d;

Ship *Ship::create(vector<GameComponent *> components) {
    Ship *ship = new Ship(components);
    if (ship->initWithFile("shipio.png")) {
        ship->autorelease();
        ship->initOptions();
        return ship;
    }
    CC_SAFE_DELETE(ship);
    return nullptr;
}


void Ship::initOptions() {
    this->scheduleUpdate();

    for (auto component : _components) {
        component->init(this);
    }
}


void Ship::update(float delta) {
    for (auto component : _components) {
        component->update(this, delta);
    }
}


Ship::~Ship() {
    this->getEventDispatcher()->removeAllEventListeners();

    while (!_components.empty()) delete _components.back(), _components.pop_back();
}
