#pragma once
#include "cocos2d.h"
#include "IRes.h"

using namespace std;
using namespace cocos2d;

class ArmatureRes  : public IRes
{
public:

	ArmatureRes(const std::string armatureStr);
	~ArmatureRes();

	static ArmatureRes* create(const std::string armatureStr, int useMemory = 1)
	{ 
		ArmatureRes *pRet = new ArmatureRes(armatureStr); 
		if (pRet && pRet->init(useMemory))
		{ 
			//pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}

	virtual bool init(int useMemory){ m_usedMemory = useMemory; return true; }

   virtual void loadResAsyn(OnResLoadListener *listener);

   virtual void loadResSyn();

	virtual const std::string getUrl();

	virtual bool  recycle();

	virtual bool isRecycled();

private:

	void loadArmatureCompleteCallback(float dt);
	static void releaseUrl(const std::string ur);
	
private:

	OnResLoadListener *mListener;
	Value *mArmatureFileStr;
	bool mIsRecycle;
};