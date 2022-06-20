#include "platformClass.h"

world_object::world_object(char* m_name, CCSprite* object_sprite)
{
	setName(m_name); //calls our methods to store
	setSprite(object_sprite); // passed in values
}

world_object::~world_object()
{
}

char* world_object::getName()
{
	return m_name; //stores our name
}

void world_object::setName(char* name)
{
	m_name = name; //sets our name
}

CCSprite* world_object::getSprite()
{
	return m_platform_sprite; //stores our sprite
}

void world_object::setSprite(CCSprite* sprite)
{
	m_platform_sprite = sprite; //sets our sprite
}