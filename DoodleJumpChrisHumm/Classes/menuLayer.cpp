#include "menuLayer.h"
#include "menuScene.h"
#include "levelScene.h" //for 

bool menuLayer::init() //first layer player will see
{
	this->setTouchEnabled(true); //allows for touch input from the 
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("closeunselected.png","close.png",this, menu_selector(menuLayer::close));
	//Now we create our label and position it
	CCLabelTTF* startGameLabel  = CCLabelTTF::create("Start Game!","Impact",32);
	startGameLabel->setPosition(ccp(0.0f, 0.0f));
	//We now convert our label to a menu label, adding a menu selector when it's pressed.
	CCMenuItemLabel* startMenuLabel = CCMenuItemLabel::create(startGameLabel,this,menu_selector(menuLayer::startGame));
	startGameLabel->setColor(ccc3(0,255,0));
	//We now combine our label to a menu. this is important if newer labels were added later.
	CCMenu* titleMenu = CCMenu::create(startMenuLabel,NULL);
	titleMenu->alignItemsVertically(); //aligns our menu vertically
	titleMenu->setPosition(screensize.x*0.5,screensize.y*0.5); //position in centre

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20)); //position

	bounce_start  = CCLabelTTF::create("Doodle Jump!","Impact",32);

	bounce_start->setPosition(ccp(screensize.x*0.5,screensize.y - 40));
	CCJumpBy* jump_screen_jump = CCJumpBy::create(5000.0f,bounce_start->getPosition(),10.0f,10000);
	addChild(pMenu); //This adds this to our current running scene and displays
	addChild(titleMenu);
	addChild(bounce_start);

	bounce_start->runAction(jump_screen_jump);

		return true;
}

void menuLayer::ccTouchesBegan(CCSet * ptouches, CCEvent * pevent ) //default touch
{																	//still included if we need
		screensize = CCDirector::sharedDirector()->getWinSize();	//to use later
		CCSetIterator itr;											//Overrided from CCLayer
		CCTouch* touch;
		
		for(itr = ptouches->begin(); itr != ptouches->end(); itr++)
		{
			 touch = (CCTouch*) *itr;
			 CCPoint LeftorRight = touch->getLocation();
		}
}

void menuLayer::close(CCObject* Closeobject)
{
	CCDirector::sharedDirector()->end(); //closes our game
}

void menuLayer::startGame(CCObject* startGameObject)
{
	levelScene* gameStart; //create a new levelScene
	gameStart = levelScene::create(); //Init the level scene
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}
