#pragma once
#include "cocos2d.h"
#include "IRes.h"

using namespace std;
using namespace cocos2d;

class TextureRes  : public IRes
{
public:

	TextureRes(const std::string resPath);
	~TextureRes();

	static TextureRes* create(const std::string resPath, int useMemory=1);

	virtual bool init(int useMemory){ m_usedMemory = useMemory; return true; }
   virtual void loadResAsyn(OnResLoadListener *listener);

   virtual void loadResSyn();

	virtual const std::string getUrl();

	virtual bool  recycle();

	virtual bool isRecycled();

private:
	void loadImgCallBack(Ref* object);
	static void releaseUrl(const std::string ur);
	
private :
	Value *mResStr;
	OnResLoadListener *mListener;
	bool mIsRecycle;
};