#include "levelLayer.h"

float levelLayer::xPTM = 1/300.0f; //for convert pixels to metres
float levelLayer::xMTP = 300.0f; // converting metres to pixels
const float levelLayer::platWidth = 69.0f; //As all platforms are one length
const float levelLayer::platHeight = 7.0f; //we can define them as const values
const int levelLayer::maxPlatforms = 15; //max amount we generate per stage

bool levelLayer::init() //called when level is created
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boing.wav"); //preload sounds
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("platform_break.wav");
	background = CCSprite::create("background.png"); //our background
	
	addChild(background); //adds to scene
	begin_game = CCLabelTTF::create("Press to start!","Impact",40.0f);
	this->setTouchEnabled(true); //allows player to touch
	this->setAccelerometerEnabled(true); //allows us to recieve acceleroameter input
	m_current_player = NULL; //set class to NULL (for checks later)
	currentlyEnding = false; //checks if game is ending..
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //grab screensize
	y_arena_height = screensize.y; //store in floats for later checks
	x_arena_width = screensize.x;
	begin_game->setPosition(ccp(x_arena_width * 0.5,y_arena_height * 0.5));
	background->setAnchorPoint(ccp(0.1,0.1));
	addChild(begin_game);
	player_hud = hudLayer::create(); //grab our hud
	addChild(player_hud); // add it to scene

	initPhysics(); //start box2d physics

	schedule( schedule_selector(levelLayer::update_physics) ); //make an updater for our physics
	return true;
}

void levelLayer::ccTouchesBegan(CCSet * ptouches, CCEvent * pevent ) 
{	//Called when player touches layer																
		CCSetIterator itr;
		CCTouch* touch;
		for(itr = ptouches->begin(); itr != ptouches->end(); itr++)
		{
			touch = (CCTouch*) *itr;
			startPlayer(touch->getLocation()); //spawns player
		}
}
float yOrigin = 0.0f; //sets origin to 0
void levelLayer::didAccelerate(CCAcceleration* pCCAccelerationValue)
{
	b2Body* b = m_world->GetBodyList(); //gets body 
		if(b->GetUserData()) //if body has user data
		{ //convert userdata to playClass
			playerClass* test = (playerClass*)b->GetUserData();
			if(test == NULL) //if NULL
				return; // return
			if(test->getName()== "Player_Object") //if player
			{ //Change gravity value according to acceleration value
				b2Vec2 gravity;
				gravity.Set( (pCCAccelerationValue->x * 10.0f), -10.0f );
				gravity.Normalize();
				gravity *= 5.0f;
				m_world->SetGravity( gravity ); //set our world gravity
			}
		}
		//yOrigin++;
}

void levelLayer::initPhysics()
{
	b2Vec2 gravityy; //create gravity
	gravityy.Set( 0.0f, -10.0f ); //set default crazy
	gravity *= 5.0f;
	m_world = new b2World(gravityy); //add gravity to world

	//B2DebugDrawLayer* mDebugLayer = B2DebugDrawLayer::create(m_world,xMTP);
	//addChild(mDebugLayer,9999); debug, do not include on build

	m_world->SetContactListener(this); //listen to box2d contactsd
	b2BodyDef groundBodyDef; //create information for our ground
	groundBodyDef.position = b2Vec2( 0.f, 0.f ); //set position
	groundBodyDef.type = b2_staticBody; //static, it cannot move
	b2Body* groundBody = m_world->CreateBody( &groundBodyDef );
	//add body  body and shaqpe to our ground
	b2EdgeShape edge;

	b2FixtureDef ground; //define information for our fixture
	ground.shape = &edge; //add edge shape to fixture

	//now we set out boundaries on our edges
	edge.Set( b2Vec2( 0.f, 0.0f ), b2Vec2( 0.f, 100000.0f * xPTM) );	
	groundBody->CreateFixture( &ground );
	edge.Set( b2Vec2( x_arena_width * xPTM, 0.0f ), b2Vec2( x_arena_width * xPTM, 100000.0f * xPTM) );	
	groundBody->CreateFixture( &ground );
	createPlatforms(); //call create platforms

}

void levelLayer::createPlatforms()
{
	srand(time(NULL)); //seed our random

	for(int i = 0; i < maxPlatforms;i++) //loops through our platforms
	{
		platPos[i].x = rand() %	(int)x_arena_width; //set a random x coordinate

		if(i == 0) //if first platform
		{
			platPos[i].y = 100;					//create in middle
			platPos[i].x = x_arena_width * 0.5; // of the screen
		}
		else // else, add new y position 300 pixels above previous
			platPos[i].y = platPos[i-1].y + 100;

		if(i == 0) //if first
		{ //ensure it's a normal platform
			platform_sprite[i] = CCSprite::create("platform.png"); //add sprite
			platform_pointers[i] = new platform_class("One Way Platform",platform_sprite[i],true);
			platToVoid[i] = platform_pointers[i];
			user_data_ptr[i] = platToVoid[i];
			
		}
		else if( i % 2 == 0)
		{ //every other platform will be a moving platform
			platform_sprite[i] = CCSprite::create("platform.png"); //add sprite
			platform_pointers[i] = new platform_class("Moving",platform_sprite[i],true);
			platToVoid[i] = platform_pointers[i];
			user_data_ptr[i] = platToVoid[i];
		}
		else // else
		{ //platform is breakable
			platform_sprite[i] = CCSprite::create("platformb.png"); //add sprite
			platform_pointers[i] = new breakablePlatforms("Breakable",platform_sprite[i],true);
			platToVoid[i] = platform_pointers[i]; 
			user_data_ptr[i] = platToVoid[i];
		}
		platform_sprite[i]->setPosition(platPos[i]); //add positions=
		//addChild(platform_sprite[i]); //add to scene
		platform_sprite[i]->retain();
		b2BodyDef platformDef[maxPlatforms]; //body def
		 //add body def position and body type
		platformDef[i].position.Set(platPos[i].x * xPTM, platPos[i].y* xPTM);
		platformDef[i].type = b2_staticBody;
		platform_pointers[i]->setPlatformNumber(i);
		platform_pointers[i]->setVisible(false);
		platformDef[i].userData = user_data_ptr[i]; //adds user data for our
													//platform class
		//add new body, shape ande fixture for our platform
		b2Body* plat = m_world->CreateBody( &platformDef[i] );
		b2PolygonShape  newrect; //shapedef

		b2FixtureDef platform;

		platform.restitution = 1.0f; //make them bouncy
		newrect.SetAsBox(platWidth* xPTM, platHeight* xPTM); //grab fixed sizes
		platform.shape = &newrect; //add shape

		annoyingPlatform[i] = plat->CreateFixture(&platform); //create fixture
	}
	addChild(platform_sprite[0]);
	platform_pointers[0]->setVisible(true);
		schedule( schedule_selector(levelLayer::updateLevel) ); //schedule for our platforms
}																//to update

void levelLayer::startPlayer(const CCPoint& pos) //called when player presses
{
	yOrigin = 0.0f; //set all origin to 0
	removeChild(begin_game);
	if(m_current_player != NULL) //if player is already created
		return; // return

		CCSprite* newsprite = CCSprite::create("monster.png"); //new sprite
		CCPoint monsterPos = pos; //get position

		float test2 = (monsterPos.y * xPTM) - yOrigin * xPTM;
		newsprite->setPositionY(y_arena_height * 0.5); //set sprite pos
		newsprite->setPositionX(x_arena_width * 0.5);
		addChild(newsprite); //add sprite to scene
		b2BodyDef ballDef; //create new body def
		ballDef.type = b2_dynamicBody; //allow body to move
		ballDef.position.Set((x_arena_width * 0.5) * xPTM,(y_arena_height * 0.5) * xPTM); //set position
		//create new player class for user data
		m_current_player = new playerClass("Player_Object",newsprite);
		voidToPlayer = m_current_player; // here foo is a local variable
		user_data_player = voidToPlayer;

		ballDef.userData = user_data_player; //add our player class

		b2CircleShape ballShape; //create shape for our ball
		ballShape.m_radius = 20.0f * xPTM; //define radius

		b2FixtureDef bouncy_ball; // define fixture
		bouncy_ball.userData = user_data_player;

		bouncy_ball.shape = &ballShape;
		//create body
		b2Body* ballBody = m_world->CreateBody(&ballDef);
		ballBody->CreateFixture(&bouncy_ball); //create fixture
		//send our player object to hud class.
		player_hud->setPlayer(m_current_player);

}



void levelLayer::update_physics( float dt ) //called every frame
{
	if(currentlyEnding == true || m_current_player == NULL)//has played failed?
		return; //don't update, return

	assert(m_world);
	m_world->Step( dt, 8, 1 ); 
	float yOrigin = 0.0f;//origin is 0
	//loop through all box2d bodies
	for( b2Body* b = m_world->GetBodyList(); b != NULL; b = b->GetNext() )
	{
		if( b->GetUserData() ) //get user data
		{ //convert to world object (all objects inherit from this..)
			world_object* test = (world_object*)b->GetUserData();
			if(test->getName() == "Player_Object") //are we the player?
			{//get current player position
				playerClass* player = (playerClass*)test;
				float current_y = player->getSprite()->getPositionY();
				if((current_y > y_arena_height * 0.5)) //are we above middle?
				{
					yOrigin = current_y - (y_arena_height*0.5); //set new origin
				}
				else if(current_y < 0.0f) //are we below the bottom?
				{
					currentlyEnding = true; //stops our update_physics
					endGame(); //calls our endGame method
					return;
				}
					yOrigin  = yOrigin * -1; //converts to position
					this->setPosition(ccp(this->getPositionX(),yOrigin)); //sets layer pos
					background->setPosition(ccp(this->getPositionX(),(yOrigin* -1)));
					player_hud->setPosition(ccp(this->getPositionX(),(yOrigin* -1)));//set hud
					m_current_player->setScore(yOrigin); //update player score
					player_hud->updateHud(); //update hud display
					player->setX(b->GetPosition().x * xMTP);
					player->setY(b->GetPosition().y * xMTP);
					if(player->getX() > x_arena_width - 30) //if player goes to right
					{
						player->setX(30.0f); //reset position to next side
						b2Vec2 physicsPosition = b->GetPosition();
						physicsPosition.x = (player->getX() * xPTM);
						b->SetTransform(physicsPosition,0.0f);
					}
					else if(player->getX() < 30.0f) //if player goes to left
					{
						player->setX(x_arena_width - 30.0f); //reset position to left side
						b2Vec2 physicsPosition = b->GetPosition();
						physicsPosition.x = (player->getX() * xPTM);
						b->SetTransform(physicsPosition,0.0f); //set box2d position
					}

				b2Vec2 physicsPosition = b->GetPosition(); //get box2d positions
				b->GetContactList();//
				if(player->getSprite()->getPositionX() >= 0)//are we above 0?
				{ //update positions for box2d and sprites
					player->getSprite()->setPosition( ccp( (player->getX()), (player->getY())));
					player->getSprite()->setRotation( CC_RADIANS_TO_DEGREES( -b->GetAngle() ) ); 
				}
			}
			else //else.. we are not the player
			{//convert userdata to platform
				platform_class* test_two = (platform_class*)b->GetUserData();
					float x = b->GetPosition().x * xMTP; //store x and y
					float y = (b->GetPosition().y * xMTP);
					if(m_current_player->getY()  > (y + y_arena_height))
					{
						test_two->setActive(true);
						float randomX = rand() % (int)x_arena_width;
						float randomY = rand() % 350 + 300;
						b->SetTransform(b2Vec2(randomX * xPTM,((m_current_player->getY() + (y_arena_height * 0.5)) + randomY) * xPTM),0.0f);
						if(test_two->getName() == "Breakable")
						{
							platform_sprite[test_two->getPlatformNumber()]->setVisible(true);
							platform_sprite[test_two->getPlatformNumber()]->setPosition(ccp(randomX,(m_current_player->getY() + (y_arena_height * 0.5) + randomY)));
							test_two->setVisible(true);
							test_two->setActive(true);
						}
						return;
					}
					else if(m_current_player->getY() + y_arena_height  > y && test_two->getVisible() == false && test_two->getStatus() == true)
					{
						addChild(platform_sprite[test_two->getPlatformNumber()]);
						test_two->setVisible(true);
					}

					if(test_two->getName() == "One Way Platform") 
					{//If we are a one way platform..
						b2Vec2 physicsPosition = b->GetPosition();
						b->GetContactList();
						if(test_two->getVisible() == true)
						{
							test_two->getSprite()->setPosition(ccp(x,y)); //update cocos2dx pos
							b->SetTransform(b2Vec2(x*xPTM,(y*xPTM)), b->GetAngle() ); //update box2d
							test_two->getSprite()->setRotation( CC_RADIANS_TO_DEGREES( -b->GetAngle() ) );
						}
					}
					else if(test_two->getName() == "Moving") //Are we a moving platform?
					{ // NOTE, same as normal platform, not a new class
						platformMove(test_two,b); //call method, pass through body and userdata
					}
				}
		}
	}
}

void levelLayer::updateLevel(float dt)
{
}

void levelLayer::BeginContact(b2Contact* contact) //called when player contacts platform
{ //preload sounds

	if(bang != NULL) //do we have a contact sprite on screen?
		removeChild(bang); // remove it

	bang = CCSprite::create("bang.png"); //add a sprite, signifying contact
	bang->setTag(1337); //set tag
	CCBlink * pop = CCBlink::create(1.0f,1); //make our sprite blink
	CCRotateBy* rotate = CCRotateBy::create(0.0f,180.0f,0.0f); //rotate sprite

	CCSequence * newsequence = CCSequence::create(pop,rotate,NULL);

	int numPoints = contact->GetManifold()->pointCount; //get number of contacts
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	b2Vec2* position;
	position =  worldManifold.points; //get contact points position
	bang->setPosition(ccp(position->x * xMTP,position->y * xMTP)); //set sprite pos
	addChild(bang); //add sprite on screen
}
//called when contact happens
void levelLayer::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
		b2Fixture* fixtureA = contact->GetFixtureA(); //get colliding
		b2Fixture* fixtureB = contact->GetFixtureB();//fixtures
		if(fixtureA == floor_ground || fixtureB == floor_ground) //are we sides?
			return; //if so, return
    b2Fixture* platformFixture = NULL; //two blank fixtures
    b2Fixture* otherFixture = NULL;
    
	int current_platform_colliding = 0;
    //check if the fixture is a one way platform and also which fixture of the two is it.
	for(int i = 0; i < maxPlatforms;i++) //loop through all
	{
		if ( fixtureA == annoyingPlatform[i] ) { //compare both 
			platformFixture = fixtureA;			 //fixtures
			otherFixture = fixtureB;			// and figure out
			current_platform_colliding = i;		//which are platforms
			break;								//and players
		}
		else if ( fixtureB == annoyingPlatform[i] ) {
			platformFixture = fixtureB;
			otherFixture = fixtureA;
			current_platform_colliding = i;
			break;
		}
	}
    if ( !platformFixture ) //if none found
        return; // return
	//get current body and retrieve userdata from that body
    b2Body* platform_body = annoyingPlatform[current_platform_colliding]->GetBody();
	platform_class* platform_type = (platform_class*)platform_body->GetUserData();
	if(platform_type->getStatus() == false)
		{//if platform is not active
			contact->SetEnabled(false);
			return;//return
		}
		
	//now we effect our player according to platform. Effect can be overriden by
	//platform child classes
	platform_type->effect(contact,platformFixture,otherFixture, m_current_player);

	if(platform_type->getStatus() == false)
	{//are we now false?
		//removeChild(platform_sprite[current_platform_colliding]); //remove
		platform_sprite[current_platform_colliding]->setVisible(false);
	} // add null

}
void levelLayer::EndContact(b2Contact* contact)
{
}

void levelLayer::deAlloc(int platform_no) //deallocates memory
{//delete current platform nuber and set pointers to NULL
	if(platform_pointers[platform_no] == NULL) //deleted already
		return;

		delete platform_pointers[platform_no];
		platform_pointers[platform_no] = NULL;
		platToVoid[platform_no] = NULL;
		user_data_ptr[platform_no] = NULL;
}

void levelLayer::endGame() //called when player is end
{
	endScene* endGameScreen; //prepare our end scene
	endGameScreen = endScene::create(); //create the scene
	endGameScreen->passScore(m_current_player->getScore()); //pass player score 
	//stop calling our update_physics every frae
	unschedule( schedule_selector(levelLayer::update_physics) );
	for(int i = 0; i < maxPlatforms;i++) //dealloc all platforms
		deAlloc(i);
	delete m_current_player; //dealloc player

	m_current_player = NULL; //set to NULL
	user_data_player = NULL;
	voidToPlayer = NULL;

	CCDirector::sharedDirector()->pushScene(endGameScreen); //push next scene
}

const int max_move = 300.0f;//max pixels move right
static bool moveRight = true; //set direction of move
static int moveCounter = 0;//set amoutn moved since last
void levelLayer::platformMove(platform_class* moving_platform, b2Body* b) 
{ //this method moves our platforms
	if(moving_platform->getVisible() == false)
		return;

	if(moveRight == true) //are we moving right?
		{
			float x = b->GetPosition().x * xMTP; //get box2d pos
					x = x + 1; //add 1 to our x
			float y = (b->GetPosition().y * xMTP);

			moving_platform->getSprite()->setPosition(ccp(x,y)); //set new cococs pos
			b->SetTransform(b2Vec2(x*xPTM,(y*xPTM)), b->GetAngle() ); //set new box2d
			moving_platform->getSprite()->setRotation( CC_RADIANS_TO_DEGREES( -b->GetAngle() ) );
			moveCounter++; //increment our moves
			if(moveCounter >= max_move)//check if we've moved max amount
				{
					moveCounter = 0; //reset to 0
					moveRight = false; // right is false, we're not false..
				}
		}
		if(moveRight == false) //we're moving left..
			{
				float x = b->GetPosition().x * xMTP; //get box2d pos
					x = x - 1; // deicrement
				float y = (b->GetPosition().y * xMTP);
				moving_platform->getSprite()->setPosition(ccp(x,y)); //set pos
				b->SetTransform(b2Vec2(x*xPTM,(y*xPTM)), b->GetAngle() ); //set box2d pos
				moving_platform->getSprite()->setRotation( CC_RADIANS_TO_DEGREES( -b->GetAngle() ) );
				moveCounter++; //increment
				if(moveCounter >= max_move) //check if we've moved max
					{
						moveCounter = 0; //reset 
						moveRight = true; //now moving right again
					}
				}
}