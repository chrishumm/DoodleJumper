#include "playerClass.h"

playerClass::playerClass(char* platform_name, CCSprite* platform_sprite) : world_object(m_name,m_platform_sprite)
{
	setName(platform_name); //sets name and sprite
	setSprite(platform_sprite);

	m_current_score = 0.0f; //default value for our score
	m_current_height = 0.0f;
	m_x = 0;
	m_y = 0;
}

playerClass::~playerClass()
{
}

float playerClass::getScore()
{
	return m_current_score; //returns highest score
}

bool playerClass::setScore(float score) //
{
	score = score * -1; //converts to positive

	if(score <= 0.0f) //if below 0, don't store
		return false; //exits

	if(score > m_current_score) //higher than max?
	{
		m_current_score = score; //set new current high score
		return true; //returns true, telling levelLayer we have new
	}				// highewst score
	else //if it isn't higher than max...
	{
		m_current_height = score; //Store as current height
		return false;
	}
	return false;
}
 //This method is called from our platform class, to make the player jhump.
void playerClass::jump(b2Body* player_body, float jump_value)
{ //First we apply a linear impusle, based on our jump value at the player
	player_body->ApplyLinearImpulse(b2Vec2(0.0f,jump_value),player_body->GetWorldCenter());
	b2Vec2 test = player_body->GetLinearVelocity(); //Store current velocity

		if(test.y > 5.0f || test.y <= 0.0f) //Now we set a speed limit
			player_body->SetLinearVelocity(b2Vec2(0.0f,3.0f));
		//If the player is higher than speed limit, we reset to max
}

void playerClass::jump(b2Body* player_body, float jump_value, bool spring)
{ //First we apply a linear impusle, based on our jump value at the player
	player_body->ApplyLinearImpulse(b2Vec2(0.0f,jump_value),player_body->GetWorldCenter());
}
float playerClass::getCurrentHeight()
{
	return m_current_height; //returns current height of the player
}

int playerClass::getX()
{
	return m_x;
}

void playerClass::setX(int x)
{
	m_x = x;
}

int playerClass::getY()
{
	return m_y;
}

void playerClass::setY(int y)
{
	m_y = y;
}