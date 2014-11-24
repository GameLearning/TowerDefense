/* 
 * File:   Enemey.h
 * Author: mohammedheader
 *
 * Created on November 24, 2014, 4:32 PM
 */

#ifndef ENEMEY_H
#define	ENEMEY_H

#include "cocos2d.h"
#include "Waypoint.h"

class HelloWorld;
class Enemy : public cocos2d::Node {
public:
    static Enemy* create(HelloWorld* game);
    virtual void update(float dt);
private:
    Enemy* init(HelloWorld* game);
    
    cocos2d::Vec2 myPosition;
    int maxHp;
    int currentHp;
    float walkingSpeed;
    Waypoint *destinationWaypoint;
    bool active;
    
    HelloWorld *theGame;
    cocos2d::Sprite *mySprite;
};

#endif	/* ENEMEY_H */

