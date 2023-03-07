#include "GameStart.h"
#include "PrepareScene.h"
#include "math.h"


GameStart::GameStart()
{
	index = 0;
	num = 0;
	streak = CCMotionStreak::create(0.5f,4.0f,10.0f,ccc3(251,4,207),"knife.png");
	this->addChild(streak,2);
	knifecolor = new CCParticleSystemQuad();
    knifecolor->initWithFile("knifecolor.plist");
    knifecolor->setTexture(CCTextureCache::sharedTextureCache()->addImage("5color.plist.png"));
	this->addChild(knifecolor,2);
	knifecolor->setVisible(false);
}

CCScene* GameStart::scene()
{
	CCScene *scene = CCScene::create();
    
	GameStart *layer = GameStart::create();

    scene->addChild(layer);

    return scene;
}

bool GameStart::init()
{
	size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("background.jpg");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background);

	CCSprite* x = CCSprite::create("x.png");
	CCSprite* xx = CCSprite::create("xx.png");
	CCSprite* xxx = CCSprite::create("xxx.png");

	x->setPosition(ccp(560,455));
	xx->setPosition(ccp(590,455));
	xxx->setPosition(ccp(620,455));

	this->addChild(x);
	this->addChild(xx);
	this->addChild(xxx);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true); 
	this->setKeypadEnabled(true);

	loadfruitmanager();
	
	return true;
}

bool GameStart::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
	
	CCPoint point = pTouches->getLocation();
	//streak->setPosition(point);
	//streak->setVisible(true);
	knifecolor->setPosition(point);
	knifecolor->setVisible(true);
	

	_point[index++]=point;
	return true ;
}

void GameStart::ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent)
{
	
	CCPoint point = pTouches->getLocation();
	streak->setPosition(point);
	knifecolor->setPosition(point);
	fruitmanager->setPt(point);
	if(index>1) 
	{
	   index = 0;

	}
	_point[index++] = point;
	float ang = atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;
	fruitmanager->setAngel(ang);
}

void GameStart::ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent)
{
	//this->removeAllChildrenWithCleanup(knifecolor);
	//this->removeChild(knifecolor);
	knifecolor->setVisible(false);
	knifecolor->setPosition(ccp(500,500));
	fruitmanager->setPt(ccp(500,500));
	//streak->setVisible(false);
	index=0;
}


void GameStart::keyBackClicked()
{
	this->cleanup();
	CCScene* scene = PrepareScene::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}


void GameStart::loadfruitmanager()
{
	fruitmanager = FruitManager::create();
	this->addChild(fruitmanager);
}


