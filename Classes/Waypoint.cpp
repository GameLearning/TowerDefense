/* 
 * File:   Waypoint.cpp
 * Author: mohammedheader
 * 
 * Created on November 24, 2014, 2:22 PM
 */

#include "HelloWorldScene.h"
#include "Waypoint.h"
USING_NS_CC;
Waypoint* Waypoint::create(HelloWorld* game, cocos2d::Vec2 location) {
    Waypoint *wayPoint = new (std::nothrow) Waypoint();
    if (wayPoint && wayPoint->init(game,location))
    {
        wayPoint->autorelease();
        return wayPoint;
    }
    CC_SAFE_DELETE(wayPoint);
    return nullptr;
}

Waypoint* Waypoint::init(HelloWorld* game, cocos2d::Vec2 location) {
    myGame = game;
    myPosition = location;
    game->addChild(this);
    
    return this;
}

void Waypoint::draw(Renderer* renderer, const cocos2d::Mat4& transform, unsigned int flags) { 
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Waypoint::onDrawPrimitives, this, transform);
    renderer->addCommand(&_customCommand);
}

void Waypoint::onDrawPrimitives(const Mat4& transform) {
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    DrawPrimitives::setDrawColor4B(0, 255, 2, 255);
    DrawPrimitives::drawCircle(getMyPosition(), 6, 360, 30, false);
    DrawPrimitives::drawCircle(getMyPosition(), 2, 360, 30, false);
    
    if(nextWayPoint){
        DrawPrimitives::drawLine(getMyPosition(), nextWayPoint->getMyPosition());
    }
}

void Waypoint::setNextWayPoint(Waypoint* wayPoint){
    nextWayPoint = wayPoint;
}

Waypoint* Waypoint::getNextWayPoint() {
    return nextWayPoint;
}


Vec2 Waypoint::getMyPosition(){
    return myPosition;
}