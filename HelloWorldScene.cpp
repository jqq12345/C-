#include "HelloWorldScene.h"
#include "PrepareScene.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{

    CCScene *scene = CCScene::create();
    

    HelloWorld *layer = HelloWorld::create();


    scene->addChild(layer);


    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* pSprite = CCSprite::create("back.png");

    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
    
	this->scheduleOnce(schedule_selector(HelloWorld::loadScene),1.5f);
	this->setKeypadEnabled(true);
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCScene* scene = PrepareScene::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::loadScene(float dt)
{
    CCScene* scene = PrepareScene::scene();
	//CCTransitionCrossFade* pScene = CCTransitionCrossFade::create(0.1,scene);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void HelloWorld::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}
