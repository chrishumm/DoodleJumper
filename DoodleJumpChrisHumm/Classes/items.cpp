#include "items.h"

items::items(char* item_name, CCSprite* item_sprite, bool active) : world_object(m_name,m_platform_sprite)
{
	setName(item_name); //sets our names and sprite
	setSprite(item_sprite);
	m_active = active; //sets if platform is current active or not
}

spring::spring(char* item_name, CCSprite* item_sprite, bool active,float spring_pwer) : items(m_name,m_platform_sprite,active)
{
	m_spring_power = spring_pwer;
	setName(item_name); //sets name
	setSprite(item_sprite);
	m_active = active; //sets if platform is current active or not
}

items::~items()
{
}
spring::~spring()
{
}

void items::setActive(bool active)
{
	m_active = active; //sets active variable
}

bool items::getStatus()
{
	return m_active; //is platform active? returns variable.
}

void items::effect(b2Contact* contact, b2Fixture* platform, b2Fixture* player,  playerClass* m_player)
{
}

void spring::effect(b2Contact* contact, b2Fixture* platform, b2Fixture* player, playerClass* m_player)
{
    b2Body* otherBody = player->GetBody();
	contact->SetEnabled(false);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("platform_break.wav"); //play sound
	m_player->jump(otherBody,m_spring_power,true); //cause player to jump
}