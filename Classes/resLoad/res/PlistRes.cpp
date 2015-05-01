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
	//Plist�Ͷ�Ӧ�Ĳ������ƿ��ܲ�һ������Ϊ����Ҫ���ղ��ʣ�����Ҫ�ر�֪��������
	//���������֪����Plist�Ͷ�Ӧ�Ĳ�������²���ʹ�ã�����һЩ����UI��Plist
	//����������ֶ�̬���صĹ����������Ͳ�֪����ô�����ˡ�
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

	//û�л���Plist������Dictionary��ÿ�ζ������½�����������Ż���
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
		//�����androidƽ̨��Bitmap������ֱ�ӻ���Bimap ,����Cocos�в������Լ���һ�׹���ܹ�
		PlistRes::releaseUrl(mPlistStr->asString(), mTextureStr->asString());
	}
	return mIsRecycle;
}

bool PlistRes::isRecycled()
{
	//CCTextureCache::sharedTextureCache()->textureForKey(mResStr->getCString()) == NULL;
	return mIsRecycle;
}