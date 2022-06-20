#pragma once
#include <iostream> 
#include "cocos2d.h"

using namespace cocos2d;

class endLayer : public CCLayer //this layer is called when player dies
{
public:
	virtual bool init();
	CREATE_FUNC(endLayer);
	CCSize screensize; //stores screensize
	virtual void ccTouchesBegan( CCSet * ptouches, cocos2d::CCEvent * pevent ); //overriden from cclayer
	void getScore(float score); //retrieves players previous score
protected:
	endLayer* m_background; //our background
	void close(CCObject*); //called when player closes scene
	void startGame(CCObject*); //called when player chooses menu
	void backToGame(CCObject*); // called when player chooses ty again
private:
	float m_score; //stores our score
	CCSprite* dead_background;
};

