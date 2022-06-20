#pragma once
#include <iostream> 
#include "cocos2d.h"
#include "MenuLayer.h"
#include "devNameLayer.h"

USING_NS_CC;

class menuScene : public CCScene 
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(menuScene);
protected:
};

