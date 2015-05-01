#pragma once

#include "Dialog/BaseLayer.h"

class BaseSceneLayer;
class sceneMaker
{
public:
	static void makeAndRunToScene(BaseSceneLayer * layer);
	static void exitGame();
};

//那些作为scene出现的layer，继承自BaseSceneLayer，作为对话框出现的layer，继承自BaseLayer
class BaseSceneLayer :public BaseLayer
{
public:
	virtual Scene * getTransitionType(Scene * scene);//这里是要重载一个TransitionScene类型返回值，

protected:

	bool mIsShowExitDialog;
public:
	static BaseSceneLayer *sCurrTopLayer;

protected:
	virtual void initData();
	virtual void initView();

	virtual void onEnter();
	virtual void onExit();
private:
	void exitDialogCancelCallback(Ref *obj);
	void exitDialogCallback(Ref *obj);

	void keyboardPressed(EventKeyboard::KeyCode code, Event* event);
	void keyboardReleased(EventKeyboard::KeyCode code, Event* event);
};


