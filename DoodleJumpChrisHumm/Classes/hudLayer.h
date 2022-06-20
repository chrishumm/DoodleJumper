#pragma once
#include <iostream> 
#include "cocos2d.h"
#include <Box2D/Box2D.h> 
#include "playerClass.h"
#include <sstream>

using namespace cocos2d;

class hudLayer : public CCLayer, b2ContactListener //inherit from two parent classes
{
public:
	virtual bool init(); //overrided init
	CREATE_FUNC(hudLayer);
	void setPlayer(playerClass* player); //init our variable, so we can access methods
	void pauseGame(CCObject* ); //pause button method menu selector
	void createHud(); //used to create our hud on startUp
	void updateHud(); //updates our hud, calling our player methods
private:
	CCLabelTTF* m_player_score; //Stores our highest score
	CCLabelTTF* m_current_height;// Stores current score (height)
	CCSprite* hud_layer_background;
	playerClass* m_player; //Holds our player, so we can access it
	bool m_paused; //Checks if we're current paused or not

};


