#pragma once
#include <iostream> 
#include "cocos2d.h"
#include "endLayer.h"
#include "devNameLayer.h" //used to display name

USING_NS_CC;

class endScene : public CCScene //inherits from CCScene
{
public:
	virtual bool init(); //overrided init
	static cocos2d::CCScene* scene();
	CREATE_FUNC(endScene);
	void passScore(float score); //used to retrieveScore from levelScene
protected:
private:
	float m_score; //store score temporarily, for endLayer scene to access
};

