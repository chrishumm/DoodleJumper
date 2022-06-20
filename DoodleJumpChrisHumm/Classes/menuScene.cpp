#include "menuScene.h"

bool menuScene::init()
{
	CCScene::init();
	
	devNameLayer* m_developer_name;
	m_developer_name = devNameLayer::create();
	addChild(m_developer_name);

	menuLayer* m_background;
	m_background = menuLayer::create();
	addChild(m_background);
	CCDirector::sharedDirector()->getRunningScene();
		return true;
}

cocos2d::CCScene* menuScene::scene()
{
	CCScene *scene = CCScene::create();
	return scene;
}