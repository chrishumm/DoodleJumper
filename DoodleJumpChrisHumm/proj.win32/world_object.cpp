#include "platformClass.h"

world_object::world_object()
{
	m_name = "One Way Platform";
}

world_object::~world_object()
{

}

char* world_object::getName()
{
	return m_name;
}

void world_object::setName(char* name)
{
	m_name = name;
}

CCSprite* world_object::getSprite()
{
	return m_platform_sprite;
}

void world_object::setSprite(CCSprite* sprite)
{
	m_platform_sprite = sprite;
}