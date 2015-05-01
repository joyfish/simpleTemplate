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

	//����������Դ�Ĵ�С
	int getResSize();
	//����������Դ������
	int getResCount();

	//������Դ����
	Vector<IRes*>* getResArray();

	//����Ҫ���ص���Դ,isLoadOneByOne��ʾ�Ƿ񰤸�����
	void loadRes(IRes* res,bool isLoadOneByOne= true);

	//����Ҫ���ص���Դ
	void loadRes(LoadCount* res);

	//��ʼ����
	void start(OnLoadListener *listener);
	//��ʼ���첽����
	void startSynLoad();

	void update(float dt);

	void removeLoadListener();

private:

	//ͳ�ƽ���
	float statisticsProgress();
	
	CC_SYNTHESIZE_READONLY(recyleManager *, m_recyleManager, RecyleManager);
	;
private:
	//��ǰʣ��δ���ص���Դ��
	int mLoadCount;
	//����Դ��
	int mLoadResTotalCount;
	//�Ƿ�ʼ
	bool mIsStart;

	//��ǰ���ص���Դ�ڴ�
	int mCurrLoadResMemory;
	//��Դ���ڴ�
	int mResTotalMemory;

	//��Դ����
	Vector<IRes*> *mResArray;
	 //��������һ֡���أ�����
	 bool mIsNextStart;
	 //��������һ֡���أ��Ƿ����һ֡
	 bool mIsDelayOneFrame;
	
	 //֡������
	 __Integer  *mFrameCheckObj;

	 //��������һ֡������Դ����
	 Vector<IRes*> *mOneByOneLoadResArray;
	 //һ���Լ�����Դ����
	 Vector<IRes*> *mOnceLoadResArray;
	 //���ؽ��ȱ�������,key ��ӦRes��Ψһ��ʶ��Value��ʾ
	 std::map<int,Value*> *mLoadProgressDic;

	int mOneByOneLoadCount;
	int mOneByOneLoadResTotalCount;

	OnLoadListener *mListener;
	
};
