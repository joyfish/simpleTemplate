#include "ArmatureRes.h"
#include "utils/MyLog.h"
#include "cocostudio\CCArmatureDataManager.h"
void ArmatureRes::releaseUrl(const std::string url)
{
	cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo(url);
	MyLog::debug("recycle ArmatureRes :%s", url.c_str());
}


ArmatureRes::ArmatureRes(const std::string armatureStr)
{
	
//一段骨骼动画对应多个PList文件
//一段骨骼动画对应多个材质

	mArmatureFileStr = new Value(armatureStr);
	mListener = NULL;
	mIsRecycle = true;
}

ArmatureRes::~ArmatureRes()
{
	delete mArmatureFileStr;
}

void ArmatureRes::loadArmatureCompleteCallback(float dt)
{
	mIsRecycle = false;
	mListener->onLoadProgressNotify(this,1.0f);
	mListener->onLoadComplete(this);
	mListener = NULL;

}

void ArmatureRes::loadResAsyn(OnResLoadListener *listener)
{
	MyLog::debug("res load ArmatureRes Asyn%s",mArmatureFileStr->asString().c_str());
	mListener = listener;
	mListener->onLoadStart(this);
	cocostudio::ArmatureDataManager::getInstance()
					->addArmatureFileInfoAsync(mArmatureFileStr->asString() ,
					this, schedule_selector(ArmatureRes::loadArmatureCompleteCallback));
}

void ArmatureRes::loadResSyn()
{
	MyLog::debug("res load ArmatureRes Syn%s", mArmatureFileStr->asString().c_str());
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(mArmatureFileStr->asString());
	mIsRecycle = false;
}

const std::string ArmatureRes::getUrl()
{
	return mArmatureFileStr->asString();
}

bool ArmatureRes::recycle()
{
	if(!mIsRecycle)
	{
		mIsRecycle  = true;
		//如果是android平台的Bitmap，可以直接回收Bimap ,但在Cocos中材质有自己的一套管理架构
		ArmatureRes::releaseUrl(mArmatureFileStr->asString());
	}
	return mIsRecycle;
}



bool ArmatureRes::isRecycled()
{
	return mIsRecycle;
}