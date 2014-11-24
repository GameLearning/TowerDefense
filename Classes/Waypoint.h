/* 
 * File:   Waypoint.h
 * Author: mohammedheader
 *
 * Created on November 24, 2014, 2:22 PM
 */

#ifndef WAYPOINT_H
#define	WAYPOINT_H

#include "cocos2d.h"
class HelloWorld;
class Waypoint : public cocos2d::Node{
public:
    static Waypoint* create(HelloWorld* game, cocos2d::Vec2 location);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, unsigned int flags);
    void setNextWayPoint(Waypoint* wayPoint);
    cocos2d::Vec2 getMyPosition();
   
    cocos2d::CustomCommand _customCommand;
private:
    Waypoint* init(HelloWorld* game, cocos2d::Vec2 location);
    void onDrawPrimitives(const cocos2d::Mat4 &transform);
    
    HelloWorld* myGame;
    cocos2d::Vec2 myPosition;
    Waypoint* nextWayPoint;
};

#endif	/* WAYPOINT_H */

