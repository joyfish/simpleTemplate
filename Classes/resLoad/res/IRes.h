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

	//������Դռ�õ��ڴ�
	int getUsedMemory()
	{
		return m_usedMemory;
	}

	//�첽������Դ
   virtual void loadResAsyn(OnResLoadListener *listener)=0;

   //ͬ��������Դ
   virtual void loadResSyn() = 0;

	//������Դ��Ψһ��ʶ��
	virtual const std::string getUrl() = 0;

	//����
	virtual bool  recycle() = 0;

	//�Ƿ����
	virtual bool isRecycled() = 0;

	
public:
	void setResRefrenceCount(bool isAdd)//trueΪ���ü���+1��falseΪ���ü���-1
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