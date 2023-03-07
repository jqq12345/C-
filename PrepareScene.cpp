#include "PrepareScene.h"
#include "HelloWorldScene.h"
#include "GameStart.h"
#include "math.h"
float ti = 0;


PrepareScene::PrepareScene()
{
	 index = 0;
	 angel = 0;
	 ifstart = false;
	 pt=ccp(500,500);
	 streak = CCMotionStreak::create(0.5f,4.0f,10.0f,ccc3(251,4,207),"knife2.png");
	 this->addChild(streak,2);
}
CCScene* PrepareScene::scene()
{
	CCScene *scene = CCScene::create();
    
	PrepareScene *layer = PrepareScene::create();

    scene->addChild(layer);

    return scene;
}

bool PrepareScene::init()
{ 
	m_fruitBrokArr = CCArray::create();
	m_fruitBrokArr->retain();
	size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* backsp = CCSprite::create("background.jpg");
	backsp->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(backsp,-1);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	this->setKeypadEnabled(true);
	loadlogo();
	this->scheduleUpdate();
	
	return true;
}

bool PrepareScene::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{ 
	CCPoint point = pTouches->getLocation();
	_point[index++] = point;
	streak->setPosition(point);
	return true;
}

void PrepareScene::ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent)
{
	
	CCPoint point = pTouches->getLocation();
	streak->setPosition(point);
	pt = point;
	if(index>1) 
	{
	   index = 0;

	}
	_point[index++] = point;
	angel = atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;

}

void PrepareScene::ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent)
{
	pt = ccp(500,500);
}

void PrepareScene::draw()
{

}

void PrepareScene::loadlogo()
{
	CCActionInterval* move = CCMoveTo::create(0.4f,ccp(size.width/2,387.5));
	CCActionInterval* action = CCEaseOut::create(move,2.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::loadtitle));
	CCSequence* seque = CCSequence::create(action,callfun,NULL);
	CCSprite* sprite = CCSprite::create("home-mask.png");
	sprite->setPosition(ccp(size.width/2,550));
	this->addChild(sprite);
	sprite->runAction(seque);

	CCSprite* splgo = CCSprite::create("logo.png");
	splgo->setPosition(ccp(150,550));
	this->addChild(splgo);
	CCActionInterval* move2 = CCMoveTo::create(0.4f,ccp(160,410));
	CCActionInterval* action2 = CCEaseOut::create(move2,3.0f);
	splgo->runAction(action2);
}

void PrepareScene::loadtitle()
{
	CCSprite* title = CCSprite::create("ninja.png");
	title->setPosition(ccp(480,400));
	this->addChild(title);
	CCActionInterval* jump = CCJumpTo::create(0.8f,ccp(480,400),20.0f,2);
	CCActionInterval* action = CCEaseIn::create(jump,2.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::loadmenu));
	CCSequence* squen = CCSequence::create(action,callfun,NULL);
	title->runAction(squen);


	CCSprite* title2 = CCSprite::create("home-desc.png");
	title2->setPosition(ccp(-80,300));
	this->addChild(title2);

	CCActionInterval* action2 = CCMoveTo::create(0.5f,ccp(100,300));
	title2->runAction(action2);
}

void PrepareScene::loadmenu()
{
	CCSprite* scle1_dojo = CCSprite::create("dojo.png");
	CCSprite* scle2_new = CCSprite::create("new-game.png");
	CCSprite* scle3_quit = CCSprite::create("quit.png");
	CCSprite* peach = CCSprite::create("peach.png");
	CCSprite* sandia = CCSprite::create("sandia.png");
	CCSprite* boom = CCSprite::create("boom.png");

	scle1_dojo->setPosition(ccp(120,180));
	scle1_dojo->setTag(1);
	scle2_new->setPosition(ccp(350,180));
	scle2_new->setTag(2);
	scle3_quit->setPosition(ccp(550,130));
	scle3_quit->setTag(3);
	peach->setPosition(ccp(120,180));
	peach->setTag(4);
	sandia->setPosition(ccp(350,180));
	sandia->setTag(5);
	boom->setPosition(ccp(550,130));
	boom->setTag(6);

	this->addChild(scle1_dojo);
	this->addChild(scle2_new);
	this->addChild(scle3_quit);
	this->addChild(peach);
	this->addChild(sandia);
	this->addChild(boom);


	//旋转效果
	scle1_rotate();
	scle2_rotate();
	scle3_rotate();
	peach_rotate();
	sandia_rotate();
	boom_rotate();

	ifstart = true;
}

void PrepareScene::keyBackClicked()
{
	CCScene* scene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void PrepareScene::update(float delta)
{
	ti += delta;
	if(ifstart&&ifColli(5,pt)) Colli(5);
	for(int i=0;i<m_fruitBrokArr->count();i++)
	{
		CCSprite* sp = (CCSprite*)m_fruitBrokArr->objectAtIndex(i);
		if(sp->getTag()==7)
		{
		   sp->setPositionX(sp->getPositionX()-3);
		   sp->setPositionY(sp->getPositionY()-(15*ti+10*ti*ti));
		}
		if(sp->getTag()==8)
		{
		   sp->setPositionX(sp->getPositionX()+3);
		   sp->setPositionY(sp->getPositionY()-(15*ti+10*ti*ti));
		}
	}


}

void PrepareScene::scle1_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(9.0f,360.0f,360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::scle1_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(1)->runAction(seque);
}
void PrepareScene::scle2_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(12.0f,-360.0f,-360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::scle2_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(2)->runAction(seque);
}
void PrepareScene::scle3_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(15.0f,360.0f,360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::scle3_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(3)->runAction(seque);
}
void PrepareScene::peach_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(12.0f,-360.0f,-360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::peach_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(4)->runAction(seque);
}
void PrepareScene::sandia_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(7.0f,360.0f,360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::sandia_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(5)->runAction(seque);
}
void PrepareScene::boom_rotate()
{
	CCRotateBy* rotate = CCRotateBy::create(12.0f,-360.0f,-360.0f);
	CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::boom_rotate));
	CCSequence* seque = CCSequence::create(rotate,callfun,NULL);
	this->getChildByTag(6)->runAction(seque);
}


void PrepareScene::loadGame()
{
	  this->unscheduleUpdate();
	  this->cleanup();
	  CCScene * scene = GameStart::scene();
      CCTransitionCrossFade* pTranslateScene = CCTransitionCrossFade::create(0.5f,scene);
	  CCDirector::sharedDirector()->replaceScene(pTranslateScene);
}


bool PrepareScene::ifColli(int tag,CCPoint point)
{
	CCSize spriteSize = this->getChildByTag(tag)->getContentSize();
	CCPoint entityPos = this->getChildByTag(tag)->getPosition();
	
	CCRect rec = CCRectMake(
        entityPos.x - spriteSize.width / 2, 
        entityPos.y - spriteSize.height / 2,    
        spriteSize.width, 
        spriteSize.height);

	return rec.containsPoint(point);
}

void PrepareScene::Colli(int tag)
{
	    ifstart = false;
		this->removeChild(this->getChildByTag(tag));
		CCSprite* sp1 = CCSprite::create("51.png");
		CCSprite* sp2 = CCSprite::create("52.png");
		CCSprite* sp3 = CCSprite::create("flash.png");
		
		sp1->setPosition(ccp(350,180));
		sp1->setRotation(angel);
		sp2->setPosition(ccp(350,180));
		sp2->setRotation(angel);
		sp3->setPosition(ccp(350,180));
		sp3->setRotation(180-angel);

		sp1->setTag(7);
		sp2->setTag(8);
		sp3->setTag(9);
		this->addChild(sp1);		
		this->addChild(sp2);
		this->addChild(sp3);
     
		//刀光消失动画
	 CCActionInterval* rotate = CCRotateBy::create(0.5f,90.0f,0);
	 CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(PrepareScene::loadGame));
	 CCSequence* action = CCSequence::create(rotate,callfun,NULL);
	 sp3->runAction(action);

		m_fruitBrokArr->addObject(sp1);
		m_fruitBrokArr->addObject(sp2);
		ti = 0;
		//this->scheduleOnce(schedule_selector(PrepareScene::loadGame),1.0f);
}




