#include "FireComponent.h"

void FireComponent::update(Node *node, float delta) {
    auto sprite = static_cast<Sprite *>(node);

    auto rot = sprite->getRotation();
    rot = fmodf(rot, 360.0f) / 180.0f * (float) M_PI;

    if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_T)) {
        this->_fire(sprite, rot);
    }
}


void FireComponent::_fire(Node *sender, float rot) {

    cocos2d::Scene *scene = cocos2d::Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(100);

    auto bulletSprite = Sprite::create();
    auto bullet = PhysicsBody::createCircle(4, PhysicsMaterial(0.001, 1, 0));
    bullet->setContactTestBitmask(0xFFFFFFFF);
    bulletSprite->addComponent(bullet);

    bulletSprite->setPosition(sender->getPosition() + Vec2(50, 0));
    layer->addChild(bulletSprite);

    bulletSprite->getPhysicsBody()->applyImpulse(Vec2(cosf(rot) * 10, sinf(-rot)));
}

