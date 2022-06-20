#include "hudLayer.h"

stringstream floatToInt; //converts from float/ints to strings
static bool runOnce = false; //ensure we run once.

bool hudLayer::init()
{
	runOnce = false; //default values
	m_paused = false;
	return true;
}

void hudLayer::setPlayer(playerClass* player)
{
	m_player = player; //stores levelLayers current player
	createHud(); //now we can create our hud, after storing our player
}

void hudLayer::createHud()
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //get current window size
	CCMenuItemImage* pPause = CCMenuItemImage::create("closeunselected.png","close.png",this, menu_selector(hudLayer::pauseGame));
	CCLabelTTF* pause = CCLabelTTF::create("Pause:","Impact",28);
	pause->setPosition(ccp(screensize.x - 100.0f,screensize.y - 25.0f));
	pause->setColor(ccc3(165,42,42));
	CCMenu* pMenu = CCMenu::create(pPause,NULL); //Adds our pause button
	pMenu->setPosition(screensize.x - 25.0f,screensize.y - 25.0f); //set at the top of the screen

	hud_layer_background = CCSprite::create("hud_layer_background.png");
	hud_layer_background->setAnchorPoint(ccp(0.1,-5.9));
	addChild(hud_layer_background,-10);
	addChild(pMenu,0); //adds our pause button to scene
	addChild(pause);
}

void hudLayer::pauseGame(CCObject* selector) //Called when pause button is pressed
{
	if(m_paused == false) //Are we paused?
	{
		m_paused = true; //No, set to pause
		CCDirector::sharedDirector()->pause(); //pauses scene
	}
	else //Yes
	{
		m_paused = false; //We're now not paused
		CCDirector::sharedDirector()->resume(); //resume our scene
	}
}

void hudLayer::updateHud() //We call players methods to update our HUD labels
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //gets current window size
	floatToInt << ceil(m_player->getScore()); //rounds up to nearest whole value, stores.
	string temp_display = "Highest Score: " + floatToInt.str() + " metres!"; //Create new string
	floatToInt.str(""); //clear stringstream

	floatToInt << ceil(m_player->getCurrentHeight()); //calls player method again
	string temp_display2 = "Current Height: " + floatToInt.str() + " metres!"; //adds string
	floatToInt.str(""); //clears

	if(runOnce == false) //Used on startup
	{					//This ensures we have labels on screen
		runOnce = true;
		m_player_score  = CCLabelTTF::create(temp_display.c_str(),"Impact",32);
		m_player_score->setPosition(ccp(150.0f,screensize.y - 25.0f));
		addChild(m_player_score); //Add our player score, based from stored string

		m_current_height = CCLabelTTF::create(temp_display2.c_str(),"Impact",32);
		m_current_height->setPosition(ccp(150.0f,screensize.y - 50.0f));
		addChild(m_current_height); //Add our current height, based from stored string
	}
	else
	{
		removeChild(m_player_score); //One frame passed, we remove our labels
		removeChild(m_current_height);
		m_player_score  = CCLabelTTF::create(temp_display.c_str(),"Impact",28);
		m_player_score->setPosition(ccp(160.0f,screensize.y - 25.0f));
		m_player_score->setColor(ccc3(165,42,42));
		addChild(m_player_score); //Now we update with newer values

		m_current_height = CCLabelTTF::create(temp_display2.c_str(),"Impact",28);
		m_current_height->setColor(ccc3(165,42,42));
		m_current_height->setPosition(ccp(160.0f,screensize.y - 50.0f));
		addChild(m_current_height); //Now we update with newer values
	}
	

}
