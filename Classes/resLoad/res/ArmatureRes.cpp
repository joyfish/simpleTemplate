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
	
//һ�ι���������Ӧ���PList�ļ�
//һ�ι���������Ӧ�������

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
		//�����androidƽ̨��Bitmap������ֱ�ӻ���Bimap ,����Cocos�в������Լ���һ�׹���ܹ�
		ArmatureRes::releaseUrl(mArmatureFileStr->asString());
	}
	return mIsRecycle;
}



bool ArmatureRes::isRecycled()
{
	return mIsRecycle;
}