/* 
 * File:   Tower.cpp
 * Author: mohammedheader
 * 
 * Created on November 23, 2014, 6:01 PM
 */
#include "HelloWorldScene.h"
#include "Tower.h"
USING_NS_CC;
Tower* Tower::create(HelloWorld* game, cocos2d::Vec2 location) {
    Tower *tower = new (std::nothrow) Tower();
    if (tower && tower->init(game,location))
    {
        tower->autorelease();
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return nullptr;
}

Tower* Tower::init(HelloWorld* game, cocos2d::Vec2 location) {
    theGame = game;
    attackRange = 70;
    damage = 10;
    fireRate = 1;
    
    mySprite = Sprite::create("tower.png");
    addChild(mySprite);
    mySprite->setPosition(location);

    theGame->addChild(this);

    scheduleUpdate();
    
    return this;
}

void Tower::draw(Renderer* renderer, const cocos2d::Mat4& transform, unsigned int flags) {
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Tower::onDrawPrimitives, this, transform);
    renderer->addCommand(&_customCommand);
}

void Tower::update(float dt) {

}

void Tower::onDrawPrimitives(const Mat4& transform) {
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
    DrawPrimitives::drawCircle(mySprite->getPosition(), attackRange, 360, 30, false);
}
