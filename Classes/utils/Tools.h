#pragma once

#include "cocos2d.h"


class Tools 
{
	
private:
	static bool hasSeed;
public :

	//可随机 min 到 max-1 范围数字
	static int random(int min,int max);
	static int randomInt();

	//返回小数进度，也就是最大是1.0f
	static  float getPercentProgressFloat(int progress,int max);
	
	static  float getProgress(float progress, float max);
};


