#pragma once
#include <iostream> 
#include "cocos2d.h"

#include <Box2D/Box2D.h> 
#include "B2DebugDrawLayer.h" //including our classes
#include "platformClass.h"  // for our objects in the game
#include "playerClass.h"
#include "world_object.h"
#include "hudLayer.h"
#include "endScene.h"
#include "SimpleAudioEngine.h"  //used for our audio
#include "items.h"


using namespace cocos2d;

class levelLayer : public CCLayer, b2ContactListener //inherits from two
{
public:
	virtual bool init();
	CREATE_FUNC(levelLayer);
	CCLabelTTF* Loc;
	CCSprite* City;

	static float xPTM; //pixels to metres
	static float xMTP; // metres to pixel convertion
	const static float platWidth; //out platform width
	const static float platHeight; // and height
	const static int maxPlatforms; //max amount allowed
	bool currentlyEnding; //if the level has ended

	CCSprite* newsprite; //temp sprite
	CCSprite* bang; // contact sprte
	CCSprite* platform_sprite[200]; //holds platform sprites
	CCPoint platPos[200]; //holds platform positions
	CCLabelTTF* begin_game;
	CCSprite* background;
	hudLayer* player_hud; //our hud layer

	void deAlloc(int platform_no); //called to dealloc
								 // platforms
	float y_arena_height; //sfcreen height
	float x_arena_width; // screen width
	virtual void ccTouchesBegan( CCSet * ptouches, cocos2d::CCEvent * pevent );
	virtual void didAccelerate(CCAcceleration* pCCAccelerationValue);

	virtual void BeginContact(b2Contact* contact); //overriden contacts
	virtual void EndContact(b2Contact* contact); // for player > platforms
	virtual	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	b2Fixture* floor_ground; //fixture for ground
	b2Fixture* annoyingPlatform[20]; // fixture for platform

	void* user_data_ptr[20];			 //Platform
	platform_class* platform_pointers[20];//Objects and Pointers
	platform_class* platToVoid[20];		 // Void is used for box2d user
										// data.
	void* user_data_player; //player object
	playerClass* voidToPlayer;
	playerClass* m_current_player;
protected:
	static B2DebugDrawLayer* create(b2World* pB2World, float pPTmratio); //debug
	levelLayer* m_background; //background layer
	b2Vec2 gravity; // gravity value
	b2World* m_world; //box2d world
	void initPhysics(); //starting physics
	void endGame(); //called when game ends
	void startPlayer(const CCPoint& startPoint); //called on player Start
	void platformMove(platform_class* moving_platform, b2Body* b);//Moves Platform
	void update_physics(float dt); //update box2d physics
	void createPlatforms();//called on game start
	void updateLevel(float dt);//Updates sprites every frame
};


