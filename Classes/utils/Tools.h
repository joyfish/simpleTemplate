#pragma once

#include "cocos2d.h"


class Tools 
{
	
private:
	static bool hasSeed;
public :

	//����� min �� max-1 ��Χ����
	static int random(int min,int max);
	static int randomInt();

	//����С�����ȣ�Ҳ���������1.0f
	static  float getPercentProgressFloat(int progress,int max);
	
	static  float getProgress(float progress, float max);
};


