#pragma once
#include <iostream>
#include <cocos2d.h>
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"  

USING_NS_CC;

class world_object //All objects within our game inherit from this parent class
{				   //Basic methods such as set/get names+sprites are included
public:
	world_object(char* m_name, CCSprite* object_sprite); //We need a name and a sprite
	~world_object();

	char* getName(); //returns the objects name
	CCSprite* getSprite(); //returns object sprite

	void setName(char* name); //sets name
	void setSprite(CCSprite*); //sets sprite
protected:
	char* m_name; //we store our m_name for our child classes
	CCSprite* m_platform_sprite;//stores sprite for child classes
};