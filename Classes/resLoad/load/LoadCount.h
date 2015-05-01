#pragma once

#include "cocos2d.h"
#include "resLoad/res/OnResLoadListener.h"
#include "OnLoadListener.h"
#include "resLoad/res/IRes.h"
#include "recyleManager.h"
USING_NS_CC;

class LoadCount : public Ref,public OnResLoadListener
{

public:
	LoadCount();
	~LoadCount();
	static LoadCount *create();

	virtual void onLoadStart(IRes *res);
	virtual void onLoadProgressNotify(IRes *res,float progress);
	virtual void onLoadComplete(IRes *res);
	virtual void onOnceLoadComplete(IRes *res);

	//返回所有资源的大小
	int getResSize();
	//返回所有资源的数量
	int getResCount();

	//返回资源数组
	Vector<IRes*>* getResArray();

	//载入要加载的资源,isLoadOneByOne表示是否挨个加载
	void loadRes(IRes* res,bool isLoadOneByOne= true);

	//载入要加载的资源
	void loadRes(LoadCount* res);

	//开始加载
	void start(OnLoadListener *listener);
	//开始非异步加载
	void startSynLoad();

	void update(float dt);

	void removeLoadListener();

private:

	//统计进度
	float statisticsProgress();
	
	CC_SYNTHESIZE_READONLY(recyleManager *, m_recyleManager, RecyleManager);
	;
private:
	//当前剩余未加载的资源数
	int mLoadCount;
	//总资源数
	int mLoadResTotalCount;
	//是否开始
	bool mIsStart;

	//当前加载的资源内存
	int mCurrLoadResMemory;
	//资源总内存
	int mResTotalMemory;

	//资源数组
	Vector<IRes*> *mResArray;
	 //挨个并隔一帧加载，开关
	 bool mIsNextStart;
	 //挨个并隔一帧加载，是否隔了一帧
	 bool mIsDelayOneFrame;
	
	 //帧检测对象
	 __Integer  *mFrameCheckObj;

	 //挨个并隔一帧加载资源数组
	 Vector<IRes*> *mOneByOneLoadResArray;
	 //一次性加载资源数组
	 Vector<IRes*> *mOnceLoadResArray;
	 //加载进度保存容器,key 对应Res的唯一标识，Value表示
	 std::map<int,Value*> *mLoadProgressDic;

	int mOneByOneLoadCount;
	int mOneByOneLoadResTotalCount;

	OnLoadListener *mListener;
	
};
