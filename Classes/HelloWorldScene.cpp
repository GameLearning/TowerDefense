#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("bg.png");
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    loadTowerPositions();
    addWaypoints();
    
    loadWaves();
    return true;
}

void HelloWorld::loadTowerPositions() {
    std::string file_path = FileUtils::getInstance()->fullPathForFilename("TowerPosition.xml");
    pugi::xml_document _levelData;
    _levelData.load_file(file_path.c_str());
    
    auto positions =  _levelData.child("positions").children();
    for (pugi::xml_node position: positions){
        auto x = position.attribute("x").as_float();
        auto y = position.attribute("y").as_float();
        
        Sprite * towerBase = Sprite::create("open_spot.png");
        towerBase->setPosition(Vec2(x,y));
        this->addChild(towerBase);
        towerBases.pushBack(towerBase);
    }
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
    for(Sprite * tb : towerBases){
            if( tb->getBoundingBox().containsPoint(touch->getLocation())
                    && canBuyTower() && !tb->getUserData()){
                     //We will spend our gold later.

                    Tower * tower = Tower::create(this,tb->getPosition());
                    towers.pushBack(tower);
                    tb->setUserData(tower);
            }
    }
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event) {

}

void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event) {

}

bool HelloWorld::canBuyTower() {
    return true;
}

void HelloWorld::addWaypoints() {
    Waypoint * waypoint1 = Waypoint::create(this, Vec2(420,35));
    waypoints.pushBack(waypoint1);
    
    Waypoint * waypoint2 = Waypoint::create(this, Vec2(35,35));
    waypoints.pushBack(waypoint2);
    waypoint2->setNextWayPoint(waypoint1);
 
    Waypoint * waypoint3 = Waypoint::create(this, Vec2(35,130));
    waypoints.pushBack(waypoint3);
    waypoint3->setNextWayPoint(waypoint2);
    
    Waypoint * waypoint4 = Waypoint::create(this, Vec2(445,130));
    waypoints.pushBack(waypoint4);
    waypoint4->setNextWayPoint(waypoint3);
 
 
    Waypoint * waypoint5 = Waypoint::create(this, Vec2(445,220));
    waypoints.pushBack(waypoint5);
    waypoint5->setNextWayPoint(waypoint4);
 
    Waypoint * waypoint6 = Waypoint::create(this, Vec2(-40,220));
    waypoints.pushBack(waypoint6);
    waypoint6->setNextWayPoint(waypoint5);

}

bool HelloWorld::isCirclesCollide(Circle circle1, Circle circle2) {
    float xdif = circle1.center.x - circle2.center.x;
    float ydif = circle1.center.y - circle2.center.y;
 
    float distance = sqrt(xdif*xdif+ydif*ydif);
 
    if(distance <= circle1.radius+circle2.radius)
        return true;
 
    return false;
}

cocos2d::Vector<Waypoint*> HelloWorld::getWaypoints() {
    return waypoints;
}

bool HelloWorld::loadWaves() {
    CCLOG("loadWaves");
    std::string file_path = FileUtils::getInstance()->fullPathForFilename("Waves.xml");
    pugi::xml_document _levelData;
    _levelData.load_file(file_path.c_str());
    
//    if (wavesNode){
//        CCLOG("wavesNode in if");
////        wavesNode =  wavesNode.r
//        _levelData.child("waves").remove_child(wavesNode);
//        wavesNode =  _levelData.child("waves").first_child();
//        //if (wavesNode == _levelData.child("waves").first_child() ) return false;
//    }else {
//        CCLOG("wavesNode in else");
        wavesNode =  _levelData.child("waves").first_child();
//    }
    CCLOG("wavesNode before loop");
    for (pugi::xml_node wave : wavesNode){
        auto spawnTime = wave.attribute("spawnTime").as_float();
        
        Enemy * enemy = Enemy::create(this);
        enemy->scheduleOnce(schedule_selector(Enemy::doActivate),spawnTime);
        CCLOG("1");
        enemies.pushBack(enemy);
        CCLOG("2");
    }
    CCLOG("wavesNode after loop");
    return true;
}

void HelloWorld::enemyGotKilled() {
//    if (++killedEnemies == enemies.size()){
//        killedEnemies = 0;
//        enemies.clear();
//        loadWaves();
//    }
}
