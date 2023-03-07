#ifndef _gamestart_
#define _gamestart_
#include "cocos2d.h"
#include "FruitManager.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
USING_NS_CC;
class GameStart: public CCLayer
{
public :
	GameStart();
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(GameStart);
	virtual bool ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);

    //CCPoint getPoint();
    //CCPoint pt;
	CCSize size;
	void keyBackClicked();

	//void  addfruit(float dt);

	CCPoint _point[2];
	int index;
	int num ;

	FruitManager* fruitmanager;
	CCParticleSystemQuad* knifecolor;
	CCMotionStreak* streak;

	void loadfruitmanager();
};
#endif