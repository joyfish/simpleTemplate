
#include "BaseSceneLayer.h"

void sceneMaker::makeAndRunToScene(BaseSceneLayer * layer)
{
	Scene * scene = Scene::create();
	scene->addChild(layer);

	if(Director::getInstance()->getRunningScene())
		Director::getInstance()->replaceScene(layer->getTransitionType(scene));
	else
		Director::getInstance()->runWithScene(layer->getTransitionType(scene));
}

void sceneMaker::exitGame()
{
	ConfigManager::getInstance()->recycle();
	Director::getInstance()->end();
}


BaseSceneLayer * BaseSceneLayer::sCurrTopLayer = nullptr;

Scene * BaseSceneLayer::getTransitionType(Scene * scene)
{
	//return TransitionFade::create(0.0f,scene);
	return scene;
}

void BaseSceneLayer::initData()
{
	BaseLayer::initData();
	
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseSceneLayer::keyboardPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseSceneLayer::keyboardReleased, this);

}

void BaseSceneLayer::initView()
{
	BaseLayer::initView();
	sCurrTopLayer = this;
}

void BaseSceneLayer::keyboardPressed(EventKeyboard::KeyCode code, Event* event)
{
	static const int DIALOG_TAG = 1234;
	if (this->mIsShowExitDialog)
	{
		Scene *scene = Director::getInstance()->getRunningScene();
		scene->removeChildByTag(DIALOG_TAG);
		mIsShowExitDialog = false;
		return;
	}
	mIsShowExitDialog = true;
	//CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	//SimpleDialog *dialog = SimpleDialog::create(
	//	ConfigUtils::getLanguagebyId(ConfigConstant::LANGUAGE_EXIT_GAME_HINT_ID)
	//	, true);
	//dialog->setCancelCallback(this, callfuncO_selector(TopLayer::exitDialogCancelCallback), NULL);
	//dialog->setOkCallback(this, callfuncO_selector(TopLayer::exitDialogCallback), NULL);
	//dialog->setLayerPriority(-128);
	//dialog->setTag(DIALOG_TAG);
	//scene->addChild(dialog);
	//CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void BaseSceneLayer::keyboardReleased(EventKeyboard::KeyCode code, Event* event)
{

}

void BaseSceneLayer::onEnter()
{
	BaseLayer::onEnter();
	sCurrTopLayer = this;
}

void BaseSceneLayer::onExit()
{
	BaseLayer::onExit();
	sCurrTopLayer = nullptr;
}

void BaseSceneLayer::exitDialogCancelCallback(Ref *obj)
{
	mIsShowExitDialog = false;
}

void BaseSceneLayer::exitDialogCallback(Ref *obj)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}