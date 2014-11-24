/* 
 * File:   Enemey.cpp
 * Author: mohammedheader
 * 
 * Created on November 24, 2014, 4:32 PM
 */

#include "HelloWorldScene.h"
#include "Enemy.h"

USING_NS_CC;
Enemy* Enemy::create(HelloWorld* game) {
    Enemy *enemy = new (std::nothrow) Enemy();
    if (enemy && enemy->init(game))
    {
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

Enemy* Enemy::init(HelloWorld* game) {
    maxHp = 40;
    currentHp = maxHp;
    active = false;
    walkingSpeed = 0.5;

    mySprite = Sprite::create("enemy.png");
    addChild(mySprite);
    theGame = game;
    
    Waypoint* waypoint = game->getWaypoints().back();
    destinationWaypoint = waypoint->getNextWayPoint();
    myPosition = waypoint->getMyPosition();
    mySprite->setPosition(myPosition);
    
    game->addChild(this);
    scheduleUpdate();
    return this;
}

void Enemy::update(float dt) {
    if(!active) return;
    
    
}
