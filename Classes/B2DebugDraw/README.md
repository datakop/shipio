B2DebugDraw
===========

Box2d debug draw for cocos2d-x.

We created a CCLayer to wrap debug drawing. By putting this layer on top, debug
drawing won't be overlaid by other CCNode.

#### Usage 
    this->addChild(B2DebugDrawLayer::create(world, PTM_RATIO), 9999);
