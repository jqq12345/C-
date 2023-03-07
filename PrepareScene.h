#ifndef _preparescene_
#define _preparescene_
#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;
class PrepareScene : public CCLayer
{
public:
	PrepareScene();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PrepareScene);
	virtual bool ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);
	void loadlogo();
	void loadtitle();
	void loadmenu();

	void keyBackClicked();

	void update(float delta);

	void loadGame();
	CCArray* m_fruitBrokArr;

	void scle1_rotate();
	void scle2_rotate();
	void scle3_rotate();
	void peach_rotate();
	void sandia_rotate();
	void boom_rotate();

    int index;
private:
	virtual void draw();
	CCSprite* _background;
	CCArray* _arry;
	CCPoint endpoint; 
	CCPoint _point[2];
	CCSize size;
	CCPoint pt;
	float angel;
	bool ifColli(int tag,CCPoint point);
	bool ifstart;
	void Colli(int tag);

	CCMotionStreak* streak;

};
#endif 