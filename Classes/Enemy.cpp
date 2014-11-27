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
    
    if(theGame->isCirclesCollide(Circle{myPosition, 1}, Circle{destinationWaypoint->getMyPosition(), 1})){
        if(destinationWaypoint->getNextWayPoint()){
            destinationWaypoint = destinationWaypoint->getNextWayPoint();
        }else{
//            theGame->getHpDamage();
            remove();
        }
    }
    Vec2 targetPoint = destinationWaypoint->getMyPosition();
    Vec2 normalized = (targetPoint - myPosition).getNormalized(); //Vec2(targetPoint.x-myPosition.x,targetPoint.y-myPosition.y).getNormalized();
    normalized *= walkingSpeed;
    myPosition = myPosition + normalized;
    
    mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y,-normalized.x)));
    mySprite->setPosition(myPosition);
}

void Enemy::doActivate(float dt) {
    active = true;
}

void Enemy::remove() {
    theGame->getEnemies().eraseObject(this,false);
    removeFromParentAndCleanup(true);
    theGame->enemyGotKilled();
}
