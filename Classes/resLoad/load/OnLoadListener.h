#pragma once

#include "cocos2d.h"
#include "resLoad/res/OnResLoadListener.h"

USING_NS_CC;

class LoadCount;

class OnLoadListener 
{

public:

	virtual void OnLoadStart(LoadCount *loadCount) = 0;

	//���ؽ��ȣ������1.0f,��С��0f���������һ������LoadStart��LoadComplete֮��
	virtual void OnLoadProgress(LoadCount *loadCount,float progress) = 0;


	virtual void OnLoadComplete(LoadCount *loadCount) = 0;
	
};
