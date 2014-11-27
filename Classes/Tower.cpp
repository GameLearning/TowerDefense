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
    if (chosenEnemy){
        //We make it turn to target the enemy chosen
        Vec2 normalized = ccpNormalize(Vec2(chosenEnemy->getSpritePosition().x-mySprite->getPositionX(),
                                              chosenEnemy->getSpritePosition().y-mySprite->getPositionY()));
        mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y,-normalized.x))+90);
 
        if(! theGame->isCirclesCollide(Circle{mySprite->getPosition(),attackRange},Circle{chosenEnemy->getSpritePosition(),1}))
        {
            //lostSightOfEnemy();
            chosenEnemy =nullptr;
            unschedule(schedule_selector(Tower::shootWeapon));
        }
    } else {
        for(auto enemy : theGame->getEnemies())
        {
            if(theGame->isCirclesCollide(Circle{mySprite->getPosition(),attackRange},Circle{enemy->getSpritePosition(),1}))
            {
                chosenEnemy = enemy;
                schedule(schedule_selector(Tower::shootWeapon),fireRate);
                break;
            }
        }
    }
}

void Tower::onDrawPrimitives(const Mat4& transform) {
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
//    DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
//    DrawPrimitives::drawCircle(mySprite->getPosition(), attackRange, 360, 30, false);
}

void Tower::shootWeapon(float dt) {
    auto bullet = Sprite::create("bullet.png");
    bullet->setPosition(mySprite->getPosition());
    theGame->addChild(bullet);
    
    bullet->runAction(Sequence::create(
            MoveTo::create(0.1,chosenEnemy->getSpritePosition()),
            CallFunc::create(bullet, callfunc_selector(Sprite::removeFromParent)),
            CallFunc::create(this, callfunc_selector(Tower::damageEnemy)),
            NULL
    ));
}

void Tower::targetKilled() {
    chosenEnemy = nullptr;
    unschedule(schedule_selector(Tower::shootWeapon));
}

void Tower::damageEnemy() {

}
