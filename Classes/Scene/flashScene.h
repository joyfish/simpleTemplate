#pragma once
#include "BaseSceneLayer.h"
#include "resLoad\load\OnLoadListener.h"
#include "resLoad\FriendRes.h"
#include "resLoad/ResSingleton.h"
#include "utils\jishiqi.h"

//�����࣬��ʼ���ݼ��ء���ʼ��Դ���ء�websocket�������ӣ���Ӧ�����������
class flashScene : public BaseSceneLayer, OnLoadListener
{
public :
	flashScene();
	~flashScene();

	static flashScene * createScene();

private:
	
	virtual void initData();
	virtual void initView();

	void connectCallBack(bool flag);//true ���ӳɹ���false ����ʧ��

	virtual void OnLoadStart(LoadCount *loadCount) ;

	//���ؽ��ȣ������1.0f,��С��0f���������һ������LoadStart��LoadComplete֮��
	virtual void OnLoadProgress(LoadCount *loadCount, float progress);


	virtual void OnLoadComplete(LoadCount *loadCount);

	void updateFlashOver();
private:
	bool isConnectSuccess;
	bool isLoadStartResCompete;
	bool isLoadStartConfigCompete;

	CC_SYNTHESIZE_RETAIN(FriendRes *, mFriendRes, FriendRes);

	void jishicallback(jishiqi * g_jishiqi, jishiqi_type type)
	{}
};