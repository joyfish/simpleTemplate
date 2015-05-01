#include "LoadCount.h"
#include "utils/MyLog.h"
#include "utils/Tools.h"

LoadCount::LoadCount()
{
	mIsStart  = false;
	mLoadCount = 0;
	mLoadResTotalCount = 0;
	mResTotalMemory = 0;
	mCurrLoadResMemory = 0;

	mOneByOneLoadCount = 0;
	mOneByOneLoadResTotalCount = 0;

	this->m_recyleManager = new recyleManager;


	this->mResArray = new Vector<IRes*>;
	
	this->mOneByOneLoadResArray = new Vector<IRes*>;
	
	this->mOnceLoadResArray = new Vector<IRes*>;

	//==============================
	//这里不用Create 
	this->mFrameCheckObj = new  __Integer(0);
	//==============================

	this->mIsNextStart = false;
	this->mIsDelayOneFrame = false;

	this->mLoadProgressDic = new std::map<int, Value*>;
}

LoadCount::~LoadCount()
{
	delete mResArray;
	mResArray = NULL;
	CC_SAFE_RELEASE_NULL(mFrameCheckObj);
	
	delete mOneByOneLoadResArray;
	mOneByOneLoadResArray = NULL;
	delete mOnceLoadResArray;
	mOnceLoadResArray = NULL;

	delete m_recyleManager;
	m_recyleManager = NULL;

	for (auto iter = mLoadProgressDic->cbegin(); iter != mLoadProgressDic->cend(); ++iter)
	{
		delete iter->second;
	}
	mLoadProgressDic->clear();
	delete mLoadProgressDic;
	
	//保险做法，避免没有移除
	CCDirector::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	//end
}

LoadCount * LoadCount::create()
{
	LoadCount *loadCount   = new LoadCount();
   loadCount->autorelease(); 
   return loadCount;
}


void LoadCount::onLoadStart(IRes *res)
{

}

void LoadCount::onLoadProgressNotify(IRes *res,float progress)
{
	if(mIsStart )
	{
		if( mListener != NULL)
		{
			int resMemory = res->getUsedMemory();
			//由于是一个一个加载才可以这样做，不然每个资源都要用一个变量来存储加载量
			//float tempProgress = 	Tools::getProgress(	mCurrLoadResMemory + resMemory * progress,
			//mResTotalMemory);
			
			int resAddress = (int)res;
			this->mLoadProgressDic->insert(pair<int,Value*>(resAddress,new Value(resMemory * progress)));

			float tempProgress = statisticsProgress();

			mListener->OnLoadProgress(this,tempProgress);
		}

	}
}

void LoadCount::onLoadComplete(IRes *res)
{
	Vector<IRes*>::iterator itor = mOneByOneLoadResArray->find(res);
	if (itor != mOneByOneLoadResArray->end())
	{
		//激活加载下一帧
		this->mIsNextStart = true;
		this->mIsDelayOneFrame = false;
		this->mOneByOneLoadCount--;
		//==========================
		//依靠引擎的计数功能判断游戏是否已经运行了一帧
		this->mFrameCheckObj->retain();
		this->mFrameCheckObj->autorelease();
		//==========================
	}

	
	this->m_recyleManager->put(res->getUrl(), res);
	this->mLoadCount--;
	

	//end

	//加上完成加载的内存量，由于是一个一个加载才可以这样做
	if(mIsStart)
	{
		int resMemory = res->getUsedMemory();
		mCurrLoadResMemory +=  resMemory;
		if( mListener != NULL)
		{
			int resAddress = (int)res;
			this->mLoadProgressDic->insert(pair<int, Value*>(resAddress,new Value(resMemory)));

			float tempProgress = statisticsProgress();
			//float tempProgress = 	Tools::getProgress(	mCurrLoadResMemory ,
			//		mResTotalMemory);
			mListener->OnLoadProgress(this,tempProgress);
		}
	}
	//end


	//MyLog::debug("loadCount : total =  %d;remain= %d",mLoadResTotalCount,mLoadCount);

	if(mLoadCount <= 0  && mIsStart && mListener != NULL)
	{
		mListener->OnLoadComplete(this);
		mListener = NULL;

		//移除计时器
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}
}

void LoadCount::onOnceLoadComplete(IRes *res)
{
	this->m_recyleManager->put(res->getUrl(),res);
	this->mLoadCount--;

	////激活加载下一帧
	//this->mIsNextStart = true;
	//this->mIsDelayOneFrame = false;

	////==========================
	////依靠引擎的计数功能判断游戏是否已经运行了一帧
	//this->mFrameCheckObj->retain();
	//this->mFrameCheckObj->autorelease();
	////==========================

	//end

	//加上完成加载的内存量，由于是一个一个加载才可以这样做
	if(mIsStart)
	{
		int resMemory = res->getUsedMemory();
		mCurrLoadResMemory +=  resMemory;
		if( mListener != NULL)
		{
			int resAddress = (int)res;
			this->mLoadProgressDic->insert(pair<int, Value*>(resAddress,new Value(resMemory)));

			float tempProgress = statisticsProgress();
			//float tempProgress = 	Tools::getProgress(	mCurrLoadResMemory ,
			//		mResTotalMemory);
			mListener->OnLoadProgress(this,tempProgress);
		}
	}
	//end


	//MyLog::debug("loadCount : total =  %d;remain= %d",mLoadResTotalCount,mLoadCount);

	if(mLoadCount <= 0  && mIsStart && mListener != NULL)
	{
		mListener->OnLoadComplete(this);
		mListener = NULL;

		//移除计时器
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}
}


//统计进度
float LoadCount::statisticsProgress()
{
		//=============================
		//统计进度
		int tempCurrLoadResMemory = 0;
		Value *tempValue = NULL;
		std::map<int, Value*>::iterator itor = mLoadProgressDic->begin();
		for (; itor != mLoadProgressDic->end();itor++)
		{
			auto element = *itor;
			tempValue = element.second;
			tempCurrLoadResMemory += tempValue->asInt();
		}
		float tempProgress =  Tools::getProgress(tempCurrLoadResMemory ,
			mResTotalMemory);
		//=============================
		return tempProgress;
}

void LoadCount::loadRes(IRes* res,bool isLoadOneByOne)
{
	if(isLoadOneByOne)
	{
		mOneByOneLoadResArray->pushBack(res);
	} else 
	{
		mOnceLoadResArray->pushBack(res);
	}
	this->mResArray->pushBack(res);
}

//载入要加载的资源
void LoadCount::loadRes(LoadCount* res)
{
	this->mOneByOneLoadResArray->pushBack(*res->mOneByOneLoadResArray);
	this->mOnceLoadResArray->pushBack(*res->mOnceLoadResArray);
	this->mResArray->pushBack(*res->mResArray);
}

//开始非异步加载
void LoadCount::startSynLoad()
{
	if(this->mIsStart == true)
	{
		return;
	}

	this->mIsStart = true;
	//开始时计算总内存
	mCurrLoadResMemory = 0;//归0
	mResTotalMemory = 0;//归0
	Ref *tempObj = NULL;
	Vector<IRes*>::iterator itor = mResArray->begin();
	for (; itor != mResArray->end();itor++)
	{
		auto tempObj = *itor;
		IRes *res = dynamic_cast<IRes*>(tempObj);
		mResTotalMemory += res->getUsedMemory();
	}
	//end 

	Ref *tempResObject = NULL;
	IRes *tempRes = NULL;
	itor = mResArray->begin();
	for (; itor != mResArray->end(); itor++)
	{
		auto tempResObject = *itor;
		tempRes = dynamic_cast<IRes*>(tempResObject);
		tempRes->loadResSyn();
		
		this->m_recyleManager->put(tempRes->getUrl(), tempRes);
	}
}

void LoadCount::start(OnLoadListener *listener)
{
	if(this->mIsStart == true)
	{
		return;
	}

	this->mListener = listener;
	//开始时就没通知0进度，也没有对加载资源数<=0进行判断
	this->mIsStart   = true;

	this->mLoadCount = mResArray->size();
	this->mLoadResTotalCount = mLoadCount;
	
	this->mOneByOneLoadCount = mOneByOneLoadResArray->size();
	this->mOneByOneLoadResTotalCount = mOneByOneLoadCount;

	this->mIsNextStart = true;
	this->mIsDelayOneFrame = true;

	//开始时计算总内存
	mCurrLoadResMemory = 0;//归0
	mResTotalMemory = 0;//归0
	Ref *tempObj = NULL;
	Vector<IRes*>::iterator itor = mResArray->begin();
	for (; itor != mResArray->end(); itor++)
	{
		auto tempObj = *itor;
		IRes *res = dynamic_cast<IRes*>(tempObj);
		mResTotalMemory += res->getUsedMemory();
	}
	//end 
	
	if(mListener != NULL)
	{
		mListener->OnLoadStart(this);
	}

	if(this->mLoadResTotalCount <= 0)
	{
		mListener->OnLoadComplete(this);
		mListener = NULL;
	} else 
	{
		Ref *tempResObject = NULL;
		IRes *tempRes = NULL;
		itor = mOnceLoadResArray->begin();
		for (; itor != mOnceLoadResArray->end(); itor++)
		{
			auto tempResObject = *itor;
			tempRes = dynamic_cast<IRes*>(tempResObject);
			tempRes->loadResAsyn(this);
		}

			//添加计时器
		Director::getInstance()->getScheduler()->Scheduler::schedule(schedule_selector(LoadCount::update),
		this, 1.0f /120.0f,   false);
	}


}


int LoadCount::getResSize()
{
	return mResArray->size();
}

int LoadCount::getResCount()
{
	return mResArray->size();
}

void LoadCount::update(float dt)
{
	//挨个加载,加载完一个后隔一帧后再加载...
	//if(this->mLoadCount >0 )
	//{
	//	if(this->mIsNextStart)
	//	{
	//		if(this->mIsDelayOneFrame)
	//		{
	//			this->mIsNextStart = false;
	//			this->mIsDelayOneFrame = false;

	//			CCArray *tempResArray = this->mResArray;
	//			int currLoadIndex = this->mLoadResTotalCount - this->mLoadCount;
	//			IRes* tempRes= dynamic_cast<IRes*>(tempResArray->objectAtIndex(currLoadIndex));
	//			tempRes->loadResAsyn(this);
	//		} else 
	//		{
	//				this->mIsDelayOneFrame = true;
	//		}
	//	} 
	//
	//}
	Vector<IRes*> *tempOneByOneLoadResArray = this->mOneByOneLoadResArray;
	if(mOneByOneLoadCount > 0 )
	{
		if(this->mIsNextStart)
		{
				//==========================
				//依靠引擎的计数功能判断游戏是否已经运行了一帧
			if (this->mFrameCheckObj->getReferenceCount()==1)
				{
					this->mIsNextStart = false;

					
					int currLoadIndex = this->mOneByOneLoadResTotalCount - this->mOneByOneLoadCount;
					IRes* tempRes= dynamic_cast<IRes*>(tempOneByOneLoadResArray->at(currLoadIndex));
					tempRes->loadResAsyn(this);
				}
				//==========================
		}
	
	}

}

Vector<IRes*>* LoadCount::getResArray()
{
	return mResArray;
}

void LoadCount::removeLoadListener()
{
	this->mListener = NULL;
}