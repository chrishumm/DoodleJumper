#pragma once
#include <iostream>				// These two classes hold all
#include <cocos2d.h>			// information for our platforms
#include "world_object.h"		// The first being the default parent
#include "playerClass.h"		// and breakable as a child.

USING_NS_CC;

class platform_class : public world_object //still inherits from world_object
{
public:
	platform_class(char* platform_name, CCSprite* platform_sprite, bool active);
	~platform_class();

	void setActive(bool active); //Is the platform active?
	bool getStatus(); //get status of the platformz

	int getPlatformNumber();
	void setPlatformNumber(int plat_no);

	void setVisible(bool);
	bool getVisible();
	//this method is overriden by child classes, tells what the platform does.
	virtual void effect(b2Contact* contact,b2Fixture* platform, b2Fixture* player,playerClass* m_player);
protected:
	bool m_active; //stores if platform is active
	int m_plat_no;
	bool m_visible;
};

class breakablePlatforms : public platform_class //inherits from above
{//this class overrides the effect method and adds a new effect
public: // to the platforms, whilst keeping same properties
	breakablePlatforms(char* platform_name, CCSprite* platform_sprite, bool active);
	~breakablePlatforms();
	virtual void effect(b2Contact* contact,b2Fixture* platform, b2Fixture* player, playerClass* m_player);
};