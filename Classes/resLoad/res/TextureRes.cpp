#include "TextureRes.h"
#include "utils/MyLog.h"


void TextureRes::releaseUrl(const std::string url)
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(url);
	MyLog::debug("recycle TextureRes :%s", url.c_str());
}


TextureRes* TextureRes::create(const std::string resPath, int useMemory)
{
	TextureRes *pRet = new TextureRes(resPath);
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

TextureRes::TextureRes(const std::string resPath)
{
	mResStr = new Value(resPath);
	mListener = NULL;
	mIsRecycle = true;
}

TextureRes::~TextureRes()
{
	delete mResStr;
}

void TextureRes::loadImgCallBack(Ref* object)
{
	mIsRecycle = false;
	mListener->onLoadProgressNotify(this,1.0f);
	mListener->onLoadComplete(this);
	mListener = NULL;

	MyLog::debug("load TextureRes Asyn:%s", mResStr->asString().c_str());

}

void TextureRes::loadResAsyn(OnResLoadListener *listener)
{
	//do nothing 

	mListener = listener ;
	listener->onLoadStart(this);
	Director::getInstance()->getTextureCache()->addImageAsync(mResStr->asString(), 
		CC_CALLBACK_1(TextureRes::loadImgCallBack, this));
}

void TextureRes::loadResSyn()
{
	Director::getInstance()->getTextureCache()->addImage(mResStr->asString());
	MyLog::debug("load TextureRes Syn:%s", mResStr->asString().c_str());
	mIsRecycle = false;
}


const std::string TextureRes::getUrl()
{
	string  str = mResStr->asString();
	return str;
}

bool  TextureRes::recycle()
{
	if(!mIsRecycle)
	{
		mIsRecycle  = true;
		TextureRes::releaseUrl(mResStr->asString());
	}
	return mIsRecycle;
}

bool TextureRes::isRecycled()
{
	return mIsRecycle;
}