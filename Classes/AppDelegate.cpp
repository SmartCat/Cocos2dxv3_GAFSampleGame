#include "AppDelegate.h"
#include "MainMenuScene.h"

USING_NS_CC;
//using namespace gaf;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

#ifdef _DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::FIXED_HEIGHT);

    Size winSize = director->getVisibleSize();
    if (winSize.height > 768)
    {
        director->setContentScaleFactor(2.0);
    }
    else
    {
        director->setContentScaleFactor(1.0);
    }

    glClearColor(1, 1, 1, 1.0);

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
