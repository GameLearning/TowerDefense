/* 
 * File:   Tower.h
 * Author: mohammedheader
 *
 * Created on November 23, 2014, 6:01 PM
 */

#ifndef TOWER_H
#define	TOWER_H

#include "cocos2d.h"

class HelloWorld;
class Tower : public cocos2d::Node {
public:
    static Tower* create(HelloWorld* game, cocos2d::Vec2 location);
    virtual void update(float dt);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, unsigned int flags);
private:
    Tower* init(HelloWorld* game, cocos2d::Vec2 location);
    
    int attackRange;
    int damage;
    float fireRate;
    
    HelloWorld *theGame;
    cocos2d::Sprite *mySprite;
};

#endif	/* TOWER_H */

