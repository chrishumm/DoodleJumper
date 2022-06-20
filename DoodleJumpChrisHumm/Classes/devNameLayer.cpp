#include "devNameLayer.h"

bool devNameLayer::init()
{
		m_dev_name = "Chris Humm - Developer"; //Store a c_style string
		displayName(); // call method to add our name to screen

		return true;
}

void devNameLayer::displayName() //displays and creates name
{
	CCPoint current_screen_dimensions = CCDirector::sharedDirector()->getWinSize(); //get window size

	CCLabelTTF* devName = CCLabelTTF::create(m_dev_name,"Impact",20); //create the label for the name
	devName->setPosition(ccp(current_screen_dimensions.x * 0.5, 0.0f + 25.0f)); //set position from winsize
	addChild(devName); //add to our layer
}