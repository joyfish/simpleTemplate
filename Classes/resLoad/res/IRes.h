#pragma once
#include "cocos2d.h"
#include  "OnResLoadListener.h"

using namespace std;
using namespace cocos2d;

class IRes  : public cocos2d::Ref
{
public:
	IRes() :m_ResRefrenceCount(0), m_usedMemory(1)
	{
	}

public:

	//返回资源占用的内存
	int getUsedMemory()
	{
		return m_usedMemory;
	}

	//异步加载资源
   virtual void loadResAsyn(OnResLoadListener *listener)=0;

   //同步加载资源
   virtual void loadResSyn() = 0;

	//返回资源的唯一标识符
	virtual const std::string getUrl() = 0;

	//回收
	virtual bool  recycle() = 0;

	//是否回收
	virtual bool isRecycled() = 0;

	
public:
	void setResRefrenceCount(bool isAdd)//true为引用计数+1，false为引用计数-1
	{
		if (isAdd)
		{
			++m_ResRefrenceCount;
		}
		else
		{
			--m_ResRefrenceCount;
		}
	}
	int getResRefrenceCount()
	{
		return m_ResRefrenceCount;
	}
protected:
	int m_ResRefrenceCount;
	int m_usedMemory;

	
};