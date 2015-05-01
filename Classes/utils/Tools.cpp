#include "Tools.h"
#include <string>
#include "cocos2d.h"
#include "MyLog.h"
#include "myStringUtils.h"

using namespace std;
USING_NS_CC;

 bool Tools::hasSeed = false;


int Tools::random(int min,int max){
	if(!hasSeed) {
		 std::srand((unsigned int)time(NULL));//随机数种子
		 hasSeed = true;
	} 
   
    return std::rand() % (max - min) + min;
}

int Tools::randomInt()
{
	if(!hasSeed) {
		 std::srand((unsigned int)time(NULL));//随机数种子
		 hasSeed = true;
	} 
      return std::rand() ;
}

 
 
float Tools::getPercentProgressFloat(int progress,int max) {
	if(progress >= max) {
		return 100;
	} else if(max <= 0 || progress <= 0) {
		return 0;
	} else {
		float percent = progress * 100 / max;
		return percent;
	}
 }


//返回小数进度，也就是最大是1.0f
float Tools::getProgress(float progress, float max)
{
	if (progress >= max) {
		return 1.0f;
	}
	else if (max <= 0 || progress <= 0) {
		return 0;
	}
	else {
		float percent = progress / max;
		return percent;
	}
}