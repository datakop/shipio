#include "FireComponent.h"

#include "../Entities/EntityManager.h"


void FireComponent::update(Node *node, float delta) {
    auto sprite = static_cast<Sprite *>(node);

    auto rot = sprite->getRotation();
    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;

    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_T)) {
        this->_fire(sprite, rot);
    }
}


void FireComponent::_fire(Node *sender, float rot) {
    auto scene = cocos2d::Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(100);
    auto entityManager = EntityManager::getInstance();

    layer->addChild(entityManager->createBulletAtPosition(sender->getPosition(), rot));
}

