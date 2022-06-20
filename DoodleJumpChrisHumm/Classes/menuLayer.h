#pragma once
#include <iostream> 
#include "cocos2d.h"

using namespace cocos2d;

class menuLayer : public CCLayer //creates our menu background and objects
{
public:
	virtual bool init();
	CREATE_FUNC(menuLayer);
	CCLabelTTF* Loc;
	CCLabelTTF* bounce_start;
	CCSize screensize; //stores screensize
	virtual void ccTouchesBegan( CCSet * ptouches, cocos2d::CCEvent * pevent );
protected:
	menuLayer* m_background; //our layer
	void close(CCObject*); //close method
	void startGame(CCObject*); //starts our levelScene
};

