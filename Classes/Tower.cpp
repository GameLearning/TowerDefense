/* 
 * File:   Tower.cpp
 * Author: mohammedheader
 * 
 * Created on November 23, 2014, 6:01 PM
 */

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

void Tower::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, unsigned int flags) {
    
}

void Tower::update(float dt) {

}
