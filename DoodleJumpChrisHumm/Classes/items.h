#pragma once
#include <iostream>				// These two classes hold all
#include <cocos2d.h>			// information for our platforms
#include "world_object.h"		// The first being the default parent
#include "playerClass.h"		// and breakable as a child.

USING_NS_CC;

class items : public world_object //still inherits from world_object
{
public:
	items(char* item_nme, CCSprite* platform_sprite, bool active);
	~items();

	void setActive(bool active); //Is the platform active?
	bool getStatus(); //get status of the platformz

	//this method is overriden by child classes, tells what the platform does.
	virtual void effect(b2Contact* contact,b2Fixture* platform, b2Fixture* player,playerClass* m_player);
protected:
	float m_spring_power;
	bool m_active;
};

class spring : public items //inherits from above
{//this class overrides the effect method and adds a new effect
public: // to the platforms, whilst keeping same properties
	spring(char* platform_name, CCSprite* platform_sprite, bool active,  float m_spring_power);
	~spring();
	virtual void effect(b2Contact* contact,b2Fixture* platform, b2Fixture* player, playerClass* m_player);
};