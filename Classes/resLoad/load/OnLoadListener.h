#pragma once

#include "cocos2d.h"
#include "resLoad/res/OnResLoadListener.h"

USING_NS_CC;

class LoadCount;

class OnLoadListener 
{

public:

	virtual void OnLoadStart(LoadCount *loadCount) = 0;

	//加载进度，最大是1.0f,最小是0f，这个方法一定是在LoadStart和LoadComplete之间
	virtual void OnLoadProgress(LoadCount *loadCount,float progress) = 0;


	virtual void OnLoadComplete(LoadCount *loadCount) = 0;
	
};
