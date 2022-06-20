#include "platformClass.h"

platform_class::platform_class(char* platform_name, CCSprite* platform_sprite, bool active) : world_object(m_name,m_platform_sprite)
{
	setName(platform_name); //sets our names and sprite
	setSprite(platform_sprite);
	m_active = active; //sets if platform is current active or not
}

breakablePlatforms::breakablePlatforms(char* platform_name, CCSprite* platform_sprite, bool active) : platform_class(m_name,m_platform_sprite,active)
{
	setName(platform_name); //sets name
	setSprite(platform_sprite);
	m_active = active; //sets if platform is current active or not
}

platform_class::~platform_class()
{
}
breakablePlatforms::~breakablePlatforms()
{
}

void platform_class::setActive(bool active)
{
	m_active = active; //sets active variable
}

bool platform_class::getStatus()
{
	return m_active; //is platform active? returns variable.
}

void platform_class::effect(b2Contact* contact, b2Fixture* platform, b2Fixture* player,  playerClass* m_player)
{
    b2Body* platformBody = platform->GetBody(); //get our bo2dx body
    b2Body* otherBody = player->GetBody();

    b2WorldManifold worldManifold; //get our box2d world

    contact->GetWorldManifold(&worldManifold); 
    worldManifold.points; //get points where we are contacting
    b2Vec2 point = worldManifold.points[0]; //store one point
    b2Vec2 vA = otherBody->GetLinearVelocityFromWorldPoint(point);

	b2Vec2 vB = platformBody->GetLinearVelocityFromWorldPoint( worldManifold.points[0] );
	b2Vec2 relativeVel = platformBody->GetLocalVector( vA - vB );

	relativeVel.Normalize();

	float32 object_radius = player->GetShape()->m_radius;
	float32 player_pos = player->GetBody()->GetPosition().y;
	float32 platform_pos = platform->GetBody()->GetPosition().y;

	player_pos -= object_radius; //get the players real position

	if(player_pos < platform_pos) //if player is below platform
	{
		contact->SetEnabled(false); //platform is not solid
	}
	else //else player is higher
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boing.wav"); //play sound
		m_player->jump(otherBody,15.0f); //call jump method, 15.0f being the force
		contact->SetEnabled(true); //platform is solid
	}
}

void breakablePlatforms::effect(b2Contact* contact, b2Fixture* platform, b2Fixture* player, playerClass* m_player)
{
    b2Body* platformBody = platform->GetBody(); //get box2d body 
    b2Body* otherBody = player->GetBody();

    b2WorldManifold worldManifold; //get our box2d world

    contact->GetWorldManifold(&worldManifold); //get points where we are contacting
    worldManifold.points; 
    b2Vec2 point = worldManifold.points[0]; //store one point
    b2Vec2 vA = otherBody->GetLinearVelocityFromWorldPoint(point);

	b2Vec2 vB = platformBody->GetLinearVelocityFromWorldPoint( worldManifold.points[0] );
	b2Vec2 relativeVel = platformBody->GetLocalVector( vA - vB );

	relativeVel.Normalize();

	float32 object_radius = player->GetShape()->m_radius;
	float32 player_pos = player->GetBody()->GetPosition().y;
	float32 platform_pos = platform->GetBody()->GetPosition().y;

	player_pos -= object_radius;

	if(player_pos < platform_pos) //we check if the player is above the platform
	{
		contact->SetEnabled(false); //if below, platform is not solid
	}
	else //else player is above
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("platform_break.wav"); //play sound
		m_player->jump(otherBody,15.0f); //cause player to jump
		contact->SetEnabled(true); //platform is solid
		setActive(false); //platform is now not active and will be removed from the layer
		m_platform_sprite = NULL; //current sprite is now null.
	}


}

int platform_class::getPlatformNumber()
{
	return m_plat_no;
}

void platform_class::setPlatformNumber(int no)
{
	m_plat_no = no;
}

bool platform_class::getVisible()
{
	return m_visible;
}

void platform_class::setVisible(bool no)
{
	m_visible = no;
}