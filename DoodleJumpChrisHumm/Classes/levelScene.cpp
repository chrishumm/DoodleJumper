#include "levelScene.h"

bool levelScene::init()
{
	CCScene::init(); //creates our scene
	
	devNameLayer* m_developer_name; //devNameLayer
	m_developer_name = devNameLayer::create();
	addChild(m_developer_name); //adds on top of our levelLayer scene

	levelLayer* running_game; //this is our main running_game
	running_game = levelLayer::create(); //creates the layer
	addChild(running_game); //adds after devNameLayer
	CCDirector::sharedDirector()->getRunningScene(); 
		return true;
}

cocos2d::CCScene* levelScene::scene()
{
	CCScene *scene = CCScene::create();
	return scene;
}