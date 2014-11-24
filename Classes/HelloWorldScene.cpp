#include "HelloWorldScene.h"
#include "libs/pugixml/pugixml.hpp"

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
            if( tb->getBoundingBox().containsPoint(touch->getLocation()) && !tb->getUserData()){
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
