#include "endScene.h"

bool endScene::init()
{
	CCScene::init();
	
	devNameLayer* m_developer_name; //used on every scene
	m_developer_name = devNameLayer::create();
	addChild(m_developer_name); //adds our layer to our scene

	CCDirector::sharedDirector()->getRunningScene();
		return true;
}

cocos2d::CCScene* endScene::scene()
{
	CCScene *scene = CCScene::create(); //creates our scene.
	return scene;
}

void endScene::passScore(float score)
{
	m_score = score; //called from levelLAyer
					//passes through the score the player has gotten
	endLayer* m_background;
	m_background = endLayer::create();
	m_background->getScore(m_score); //stores in endLayer
	addChild(m_background); //adds new layer to background
}