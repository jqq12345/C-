#ifndef _Entity_
#define _Entity_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
USING_NS_CC;

class Entity :public CCNode
{

public:
	 Entity();
	  ~Entity();

	 CCSprite* getSprite();
	
	 void bindSprite(CCSprite* sprite);
private:
	 CCSprite* m_sprite;
	 
};

#endif
