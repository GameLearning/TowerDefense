#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Tower.h"
#include "Waypoint.h"
#include "libs/pugixml/pugixml.hpp"
#include "Enemy.h"

struct Circle {
    cocos2d::Vec2 center;
    float radius;
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
    cocos2d::Vector<Waypoint*> getWaypoints();
    bool isCirclesCollide(Circle circle1, Circle circle2);
    cocos2d::Vector<Enemy*> getEnemies() {return enemies;};
    void enemyGotKilled();
private:
    cocos2d::Vector<cocos2d::Sprite*> towerBases;
    cocos2d::Vector<Tower*> towers;
    cocos2d::Vector<Waypoint*> waypoints;
    cocos2d::Vector<Enemy*> enemies;
    int wave,totalWaves,killedEnemies;
    pugi::xml_node wavesNode;
    
    void loadTowerPositions();
    void addWaypoints();
    bool canBuyTower();
    bool loadWaves();
};

#endif // __HELLOWORLD_SCENE_H__
