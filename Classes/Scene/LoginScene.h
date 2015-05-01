#pragma once
#include "socket\myMessageHander.h"
#include "BaseSceneLayer.h"
#include "utils\jishiqi.h"
class LoginScene : public BaseSceneLayer, public myMessageHander
{
public:
	LoginScene();
	~LoginScene();
	static LoginScene* createScene();

private:
	void initData();
	void initView();

	void buttonclick(Ref*target, Ref * data);

	void onEnter();
	void onExit();

	void sendMessageToServer(int actionId);
	void receiveMessageFromServer(SmartMessageData * data);
	void setActionMap();

	void jishicallback(jishiqi * g_jishiqi, jishiqi_type type);

	void timeUpdate(float f);
};