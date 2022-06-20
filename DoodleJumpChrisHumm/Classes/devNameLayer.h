#pragma once
#include <iostream> 
#include "cocos2d.h"

using namespace cocos2d;

class devNameLayer : public CCLayer //include in ALL Scenes..
{
public:
	virtual bool init();
	CREATE_FUNC(devNameLayer);
private:
	char* m_dev_name; //stores our developer name
	void displayName(); //display name we've stored
};

