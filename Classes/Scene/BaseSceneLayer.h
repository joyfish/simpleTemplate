#pragma once

#include "Dialog/BaseLayer.h"

class BaseSceneLayer;
class sceneMaker
{
public:
	static void makeAndRunToScene(BaseSceneLayer * layer);
	static void exitGame();
};

//��Щ��Ϊscene���ֵ�layer���̳���BaseSceneLayer����Ϊ�Ի�����ֵ�layer���̳���BaseLayer
class BaseSceneLayer :public BaseLayer
{
public:
	virtual Scene * getTransitionType(Scene * scene);//������Ҫ����һ��TransitionScene���ͷ���ֵ��

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


