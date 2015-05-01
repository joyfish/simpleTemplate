#include "PlistRes.h"
#include "utils\myStringUtils.h"
#include "utils/MyLog.h"

void PlistRes::releaseUrl(const std::string plistStr, const std::string textureStr)
{
	MyLog::debug("recycle PlistRes :%s", plistStr.c_str());
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistStr);
	Director::getInstance()->getTextureCache()->removeTextureForKey(textureStr);
}


PlistRes::PlistRes(const std::string plistPath, const std::string texturePath)
{
	//Plist和对应的材质名称可能不一样，因为我们要回收材质，故需要特别知道材质名
	//这个类是在知道了Plist和对应的材质情况下才能使用，比如一些界面UI的Plist
	//如果像技能那种动态加载的骨骼动画，就不知道怎么加载了。
	mPlistStr = new Value(plistPath);
	mTextureStr = new Value(texturePath);
	mListener = NULL;
	mIsRecycle = true;
}

PlistRes::~PlistRes()
{
	delete mTextureStr;
	delete mPlistStr;
}

void PlistRes::loadImgCallBack(Ref* object)
{
	mIsRecycle = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		mPlistStr->asString(),mTextureStr->asString());
	mListener->onLoadProgressNotify(this,1.0f);
	mListener->onLoadComplete(this);
	mListener = NULL;
	MyLog::debug("load PlistRes Asyn:%s", mPlistStr->asString().c_str());
}

void PlistRes::loadResAsyn(OnResLoadListener *listener)
{
	//do nothing 
	MyLog::debug("load PlistRes Syn:%s", mPlistStr->asString().c_str());
	mListener = listener ;
	listener->onLoadStart(this);
	Director::getInstance()->getTextureCache()->addImageAsync(mTextureStr->asString(), 
			CC_CALLBACK_1(PlistRes::loadImgCallBack,this)); 
}

void PlistRes::loadResSyn()
{
	Director::getInstance()->getTextureCache()->addImage(mTextureStr->asString());

	//没有缓存Plist解析后Dictionary，每次都会重新解析，这块能优化吗
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		mPlistStr->asString(),mTextureStr->asString());
	//end


	mIsRecycle = false;
}

const std::string PlistRes::getUrl()
{
	std::string str = mPlistStr->asString();
	return str;
}

//bool  TextureRes::recycle()
//{
//	CCTextureCache::sharedTextureCache()->removeTextureForKey(mResStr->getCString());
//	return CCTextureCache::sharedTextureCache()->textureForKey(mResStr->getCString()) == NULL;
//}

bool  PlistRes::recycle()
{
	if(!mIsRecycle)
	{
		mIsRecycle  = true;
		//如果是android平台的Bitmap，可以直接回收Bimap ,但在Cocos中材质有自己的一套管理架构
		PlistRes::releaseUrl(mPlistStr->asString(), mTextureStr->asString());
	}
	return mIsRecycle;
}

bool PlistRes::isRecycled()
{
	//CCTextureCache::sharedTextureCache()->textureForKey(mResStr->getCString()) == NULL;
	return mIsRecycle;
}