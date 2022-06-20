#pragma once
#include <iostream> 
#include "cocos2d.h"
#include "devNameLayer.h" //need to include on all scene
#include "levelLayer.h" //this is our main layer for our level

USING_NS_CC; //uses namespace cocos2d, so we can use cocos2dx

class levelScene : public CCScene //This is our scene that holds our level
{
public:
	virtual bool init(); //overriden and called whgen scene is created
	static cocos2d::CCScene* scene();
	CREATE_FUNC(levelScene);
protected:
};

