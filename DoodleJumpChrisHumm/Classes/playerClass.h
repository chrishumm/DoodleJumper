#pragma once
#include <iostream>
#include <cocos2d.h>
#include "world_object.h"
#include <cmath>

USING_NS_CC;
// This class will be used by all players in our game.
class playerClass : public world_object //inherits from world object
{
public:
	playerClass(char* platform_name, CCSprite* platform_sprite);
	~playerClass();

	float getScore(); //gets current player score
	bool setScore(float score); //sets player score
	float getCurrentHeight(); //gets current height
	void setX(int x);
	void setY(int u);

	int getX();
	int getY();
	void jump(b2Body* player_body, float jump_value); //jumps our player
	void jump(b2Body* player_body, float jump_value, bool spring); //jumps our player
private:
	float m_current_score; //store highest score
	float m_current_height; //stores current height
	int m_x;
	int m_y;
};