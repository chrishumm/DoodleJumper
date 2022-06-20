#include "endLayer.h"
#include "endScene.h"
#include "menuScene.h"
#include "levelScene.h"

bool endLayer::init() //called when first run
{
	this->setTouchEnabled(true); //enabling touch input for menu
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //used for sizing
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("closeunselected.png","close.png",this, menu_selector(endLayer::close));
	dead_background = CCSprite::create("dead_background.png");
	dead_background->setAnchorPoint(ccp(0.1,0.1));
	addChild(dead_background);
	CCLabelTTF* tryAgain  = CCLabelTTF::create("Try Again","Impact",32); //menu selector label
	tryAgain->setPosition(ccp(0.0f, 0.0f));								//  restarts the game
	CCMenuItemLabel* startGameLabel = CCMenuItemLabel::create(tryAgain,this,menu_selector(endLayer::backToGame));
	tryAgain->setColor(ccc3(0,255,0)); //sets the colour

	CCLabelTTF* mainMenuLabel = CCLabelTTF::create("Back to main menu","Impact",32); //menu selector label
	mainMenuLabel->setPosition(ccp(0.0f, 0.0f));									//goes back to main menu
	CCMenuItemLabel* startMenuLabel = CCMenuItemLabel::create(mainMenuLabel,this,menu_selector(endLayer::startGame));
	mainMenuLabel->setColor(ccc3(255,255,0));

	CCMenu* titleMenu = CCMenu::create(startGameLabel,startMenuLabel,NULL); //put our labels into one menu
	titleMenu->alignItemsVertically(); //menu items are vertical
	titleMenu->setPosition(screensize.x*0.5,screensize.y*0.5); //set for middle of screen

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); //close button, aligns with bottom
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

	
	addChild(pMenu); //adds to cyrrebt rybbubg scebe
	addChild(titleMenu);
		return true;
}

void endLayer::ccTouchesBegan(CCSet * ptouches, CCEvent * pevent ) //default touches
{																 //still included in case
		screensize = CCDirector::sharedDirector()->getWinSize(); // needed for later
		CCSetIterator itr;
		CCTouch* touch;
		
		for(itr = ptouches->begin(); itr != ptouches->end(); itr++)
		{
			 touch = (CCTouch*) *itr;
		}
}

void endLayer::close(CCObject* Closeobject)
{
	CCDirector::sharedDirector()->end(); //closes program
}

void endLayer::startGame(CCObject* startGameObject)
{
	menuScene* menuStart; //create new menu scene.. we go back to menu
	menuStart = menuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuStart); //replace current with new
}

void endLayer::backToGame(CCObject* backToGame)
{
	levelScene* tryAgain; //create new menu scene.. we go back to menu
	tryAgain = levelScene::create();
	CCDirector::sharedDirector()->replaceScene(tryAgain);
}

void endLayer::getScore(float score) //this is where we store our score from our scene
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //get size
	m_score = score; //store score

	char buffer[64]; //buffer for sprintf
	sprintf( buffer, "Your score: %d", (int)m_score); //casting and storing m_score as a string
	CCLabelTTF* your_score = CCLabelTTF::create(buffer,"Impact",32); //creating label for our score

	your_score->setPosition(ccp(screensize.x * 0.5,screensize.y - 60.0f)); //setting it at the top
	addChild(your_score); //adding our label to the scene
} //score is passed from endScene, which in turn is from 