#include "Fruit.h"
#include "math.h"


bool Fruit::init()
{
	return true;
}

bool Fruit::IsCollideWithPoint(CCPoint point)
{
	CCSize spriteSize = getSprite()->getContentSize();
	CCPoint entityPos = getPosition();
	
	CCRect rec = CCRectMake(
        entityPos.x - spriteSize.width / 2, 
        entityPos.y - spriteSize.height / 2,    
        spriteSize.width, 
        spriteSize.height);

	return rec.containsPoint(point);
	
}