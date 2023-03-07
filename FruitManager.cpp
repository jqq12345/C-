#include "FruitManager.h"
#include "Fruit.h"
#include "GameStart.h"
#include "PrepareScene.h"
float t = 0;

char* m1 = "/sound/menu.mp3";
char* m2 = "/sound/over.mp3";
char* m3 = "/sound/start.mp3";
char* m4 = "/sound/throw.mp3";
char* m5 = "/sound/splatter.mp3";

FruitManager::FruitManager()
{
	pt = ccp(500,500);
	angel = 0;
	notCutNum = 0;
	

}

bool FruitManager::init()
{

	CCSpriteFrameCache* framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
	framecache->addSpriteFramesWithFile("fruit.plist","fruit.png");
	m_fruitArr = CCArray::create();
	m_fruitArr->retain();
	m_fruitBrokenArr = CCArray::create();
	m_fruitBrokenArr->retain();

	this->scheduleOnce(schedule_selector(FruitManager::createFruit),2.0f);
	
	this->scheduleUpdate();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(m1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(m2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(m3);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(m4);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(m5);
	return true ;
}

void FruitManager::createFruit(float dt)
{
	if(notCutNum>=3) return;
	Fruit* fruit = NULL;

	for(int i=0;i<=rand()%3;i++)
	{
		int index =  rand()%5+1;
		fruit = Fruit::create();
		fruit->bindSprite(CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%d.png",index)->getCString()));
		fruit->setTag(index);						  
		CCPoint p = ccp(rand()%640,-50);
		fruit->setPosition(p);	
		this->addChild(fruit);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m4);
		m_fruitArr->addObject(fruit);
		fruit->runAction(createAction(p));
	}

}

void FruitManager::update(float delta)
{
	t+=delta;
    CCObject* obj = NULL;
	Fruit* fruit = NULL;
	for(int i=0;i<m_fruitArr->count();i++)
	{
		fruit = (Fruit*)m_fruitArr->objectAtIndex(i);
		if(fruit->IsCollideWithPoint(pt)) //是否有被刀切到
		{	
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m5);
			m_fruitArr->removeObject(fruit);
			CollisionWithPoint(fruit->getTag());
			this->removeChild(fruit);						
		}
	}	


	for(int i=0;i<m_fruitBrokenArr->count();i++)
	{
		CCSprite* sp = (CCSprite*)m_fruitBrokenArr->objectAtIndex(i); 
		if(sp->getPositionY()<0)
		{
		   	m_fruitBrokenArr->removeObject(sp);
			this->removeChild(sp);
			continue;
		}
		if(sp->getTag()==6)
		{
		   sp->setPositionX(sp->getPositionX()-2);
		   sp->setPositionY(sp->getPositionY()-20*t*t);
		}
		if(sp->getTag()==7)
		{
		   sp->setPositionX(sp->getPositionX()+2);
		   sp->setPositionY(sp->getPositionY()-20*t*t);
		}
	
	}
}

CCAction* FruitManager::createAction(CCPoint point)
{
	
	if(point.x<=320)
	{
	   CCActionInterval* jump = CCJumpTo::create(2.0f,ccp(rand()%200+400,-20),380.0f,1);
	   CCActionInterval* rotate = CCRotateBy::create(2.0f,180.f,180.f);
	   CCSpawn* jumpandrota = CCSpawn::create(jump,rotate,NULL);
	   CCCallFuncN* callfun = CCCallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
	   CCSequence* action = CCSequence::create(jumpandrota,callfun,NULL);	 
	   return  action;
	}

	if(point.x>320)
	{
		CCActionInterval* jump = CCJumpTo::create(2.0f,ccp(rand()%100,-20),380.0f,1);
	    CCCallFuncN* callfun = CCCallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
	    CCActionInterval* rotate = CCRotateBy::create(2.0f,180.f,180.f);
		CCSpawn* jumpandrota = CCSpawn::create(jump,rotate,NULL);
	    CCSequence* action = CCSequence::create(jumpandrota,callfun,NULL);
	    return  action;
	}

}

void FruitManager::setPt(CCPoint P)
{
	pt = P;
}

void FruitManager::setAngel(float ang)
{
	angel = ang;
}

void FruitManager::actionEnd(CCNode* sender)
{
	
	CCSprite* sprite = (CCSprite*) sender ; 
	if(sprite->getTag()==10)
	{
		CCScene* scene = PrepareScene::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	this->removeChild(sprite);
	if(sprite->getTag()<6)
	{
		notCut();
	    m_fruitArr->removeObject(sprite);
	    if(m_fruitArr->count()==0)
		createFruit(0.0f);
	}
	else this->removeChild(this->getChildByTag(9));
    	
}

void FruitManager::CollisionWithPoint(int tag)
{
	t = 0;
	CCSprite* broken1 = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%d1.png",tag)->getCString());
	CCSprite* broken2 = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%d2.png",tag)->getCString());
	CCSprite* flash = CCSprite::createWithSpriteFrameName("flash.png");
	flash->setPosition(pt);
	flash->setRotation(180-angel);
	flash->setTag(8);
	broken1->setPosition(pt);
	broken1->setTag(6);
	broken1->setRotation(-angel);
	broken2->setPosition(pt);
	broken2->setTag(7);
	broken2->setRotation(-angel);
	this->addChild(broken1);
	this->addChild(broken2);
	this->addChild(flash);

	CCActionInterval* rotate = CCRotateBy::create(0.3f,90.0f,0);
	 CCCallFuncN* callfun = CCCallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
	 CCSequence* action = CCSequence::create(rotate,callfun,NULL);
	 flash->runAction(action);

	m_fruitBrokenArr->addObject(broken1);
	m_fruitBrokenArr->addObject(broken2);

	//添加果汁效果
   CCParticleSystemQuad *system = new CCParticleSystemQuad();
   system->initWithFile("water.plist");
   system->setTexture(CCTextureCache::sharedTextureCache()->addImage("LavaFlow.plist.png"));
   system->setPosition(pt);
   system->setTag(9);
   this->addChild(system);
   if(m_fruitArr->count()==0)
		this->scheduleOnce(schedule_selector(FruitManager::createFruit),2.0f);

}

void FruitManager::notCut()
{
	    notCutNum++;
		if(notCutNum==1)
		{
		   CCSprite* xf = CCSprite::create("xf.png");
		   xf->setPosition(ccp(560,455));
		   this->addChild(xf);
		}
		if(notCutNum==2)
		{
		   CCSprite* xf = CCSprite::create("xf.png");
		   CCSprite* xxf = CCSprite::create("xxf.png");
		   xf->setPosition(ccp(560,455));		  
		   xxf->setPosition(ccp(590,455));
		   this->addChild(xf);
		   this->addChild(xxf);
		}
		if(notCutNum==3)
		{
		   CCSprite* xf = CCSprite::create("xf.png");
		   CCSprite* xxf = CCSprite::create("xxf.png");
		   CCSprite* xxxf = CCSprite::create("xxf.png");
		   xf->setPosition(ccp(560,455));		  
		   xxf->setPosition(ccp(590,455));
		   xxxf->setPosition(ccp(590,455));
		   this->addChild(xf);
		   this->addChild(xxf);
		   this->addChild(xxxf);
		   gameOver();
		}	
		    
}

void FruitManager::gameOver()
{
	//this->removeAllChildren();
	//CCDirector::sharedDirector()->pause();
	CCSprite* gameover = CCSprite::create("game-over.png");
	gameover->setPosition(ccp(320,240));
	gameover->setTag(10);
	this->addChild(gameover);

	CCActionInterval* scaleLarge = CCScaleTo::create(1.0f, 1.5f, 1.5f);
	CCActionInterval* scaleSmall = CCScaleTo::create(1.0f, 0.5f, 0.5f);

	CCCallFuncN* callFunc = CCCallFuncN::create(this, callfuncN_selector(FruitManager::actionEnd));

	CCActionInterval* actions = CCSequence::create(scaleLarge, scaleSmall, callFunc, NULL);

	gameover->runAction(actions);

}