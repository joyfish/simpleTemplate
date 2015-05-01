#pragma once
#include "cocos2d.h"
#include "IRes.h"

using namespace std;
using namespace cocos2d;

class PlistRes  : public IRes
{
public:


	PlistRes(const std::string resPath, const std::string texturePath);
	~PlistRes();

	static PlistRes* create(const std::string resPath, const std::string texturePath, int useMemory = 1)
	{ 
		PlistRes *pRet = new PlistRes(resPath,texturePath); 
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
	void loadImgCallBack(Ref* object);
	static void releaseUrl(const std::string plistStr, const std::string textureStr);
private :
	Value *mPlistStr;
	Value *mTextureStr;
	OnResLoadListener *mListener;
	bool mIsRecycle;
};