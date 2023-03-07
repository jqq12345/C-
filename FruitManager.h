#ifndef _fruitmanager_
#define _fruitmanager_
#include "cocos2d.h"
using namespace cocos2d;

class FruitManager : public CCNode
{
 public:
     FruitManager();

     CREATE_FUNC(FruitManager);
     virtual bool init();

     virtual void update(float dt);

	 CCAction* createAction(CCPoint point);

	 CCPoint pt;
	 float angel;
	 void setPt(CCPoint p);
	 void setAngel(float ang);
	 void createFruit(float dt);
	  CCArray* m_fruitArr;
	  CCArray* m_fruitBrokenArr;
	  CCArray* m_systemArr;
	  void actionEnd(CCNode* sender);	   
	  void CollisionWithPoint(int tag);
private:
	 int notCutNum;
	 void notCut();
	 void gameOver();
};
#endif