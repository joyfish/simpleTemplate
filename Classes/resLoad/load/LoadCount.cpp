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
	//���ﲻ��Create 
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
	
	//��������������û���Ƴ�
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
			//������һ��һ�����زſ�������������Ȼÿ����Դ��Ҫ��һ���������洢������
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
		//���������һ֡
		this->mIsNextStart = true;
		this->mIsDelayOneFrame = false;
		this->mOneByOneLoadCount--;
		//==========================
		//��������ļ��������ж���Ϸ�Ƿ��Ѿ�������һ֡
		this->mFrameCheckObj->retain();
		this->mFrameCheckObj->autorelease();
		//==========================
	}

	
	this->m_recyleManager->put(res->getUrl(), res);
	this->mLoadCount--;
	

	//end

	//������ɼ��ص��ڴ�����������һ��һ�����زſ���������
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

		//�Ƴ���ʱ��
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}
}

void LoadCount::onOnceLoadComplete(IRes *res)
{
	this->m_recyleManager->put(res->getUrl(),res);
	this->mLoadCount--;

	////���������һ֡
	//this->mIsNextStart = true;
	//this->mIsDelayOneFrame = false;

	////==========================
	////��������ļ��������ж���Ϸ�Ƿ��Ѿ�������һ֡
	//this->mFrameCheckObj->retain();
	//this->mFrameCheckObj->autorelease();
	////==========================

	//end

	//������ɼ��ص��ڴ�����������һ��һ�����زſ���������
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

		//�Ƴ���ʱ��
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}
}


//ͳ�ƽ���
float LoadCount::statisticsProgress()
{
		//=============================
		//ͳ�ƽ���
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

//����Ҫ���ص���Դ
void LoadCount::loadRes(LoadCount* res)
{
	this->mOneByOneLoadResArray->pushBack(*res->mOneByOneLoadResArray);
	this->mOnceLoadResArray->pushBack(*res->mOnceLoadResArray);
	this->mResArray->pushBack(*res->mResArray);
}

//��ʼ���첽����
void LoadCount::startSynLoad()
{
	if(this->mIsStart == true)
	{
		return;
	}

	this->mIsStart = true;
	//��ʼʱ�������ڴ�
	mCurrLoadResMemory = 0;//��0
	mResTotalMemory = 0;//��0
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
	//��ʼʱ��û֪ͨ0���ȣ�Ҳû�жԼ�����Դ��<=0�����ж�
	this->mIsStart   = true;

	this->mLoadCount = mResArray->size();
	this->mLoadResTotalCount = mLoadCount;
	
	this->mOneByOneLoadCount = mOneByOneLoadResArray->size();
	this->mOneByOneLoadResTotalCount = mOneByOneLoadCount;

	this->mIsNextStart = true;
	this->mIsDelayOneFrame = true;

	//��ʼʱ�������ڴ�
	mCurrLoadResMemory = 0;//��0
	mResTotalMemory = 0;//��0
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

			//��Ӽ�ʱ��
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
	//��������,������һ�����һ֡���ټ���...
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
				//��������ļ��������ж���Ϸ�Ƿ��Ѿ�������һ֡
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