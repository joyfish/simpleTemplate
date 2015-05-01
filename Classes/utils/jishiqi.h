#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class jishiqi_type
{
	jishiqi_start = 0,//��ʱ����ʼ
	jishiqi_ing,//���ڼ�ʱ��ÿ��ˢ��
	jishiqi_end//��ʱ��ʱ�䵽��
};

static const int UNVALID_FEN = -1;
static const int UNVALID_MIAO = -1;

class jishiqi:public Node
{
public:
	//ȫ�ּ�ʱ������ʱ�������Ը����������޸�
	static void createForverJishiqi(std::function<void(jishiqi*, jishiqi_type)> callback, int fen = UNVALID_FEN, int miao = UNVALID_MIAO);
	static void destroyInstance();
public:
	static jishiqi* create(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao);
	
	void resetTime(int fen,int miao);
private:
	bool initJishiqi(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao, bool isForever = false);
    void timeUpdate(float f);
    void firstTimeUpdate();//��һ�μ�ʱ����Ӧ�����ڳ�ʼ����ʾ
private:
	CC_SYNTHESIZE_READONLY(int ,fen,Fen);
	CC_SYNTHESIZE_READONLY(int ,miao,Miao);
	
	std::function<void(jishiqi*, jishiqi_type)> m_callback;
private:
	static jishiqi * instance;
	bool isForever;
};