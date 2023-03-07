#ifndef _fruit_
#define _fruit_
#include "cocos2d.h"
#include "Entity.h"

class Fruit: public Entity
{
public:
	 // Fruit();
	 CREATE_FUNC(Fruit);
	 virtual bool init();
	 bool IsCollideWithPoint(CCPoint point);

private:


};
#endif