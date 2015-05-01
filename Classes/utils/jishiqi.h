#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class jishiqi_type
{
	jishiqi_start = 0,//计时器开始
	jishiqi_ing,//正在计时，每秒刷新
	jishiqi_end//计时器时间到了
};

static const int UNVALID_FEN = -1;
static const int UNVALID_MIAO = -1;

class jishiqi:public Node
{
public:
	//全局计时器，计时方法可以根据需求在修改
	static void createForverJishiqi(std::function<void(jishiqi*, jishiqi_type)> callback, int fen = UNVALID_FEN, int miao = UNVALID_MIAO);
	static void destroyInstance();
public:
	static jishiqi* create(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao);
	
	void resetTime(int fen,int miao);
private:
	bool initJishiqi(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao, bool isForever = false);
    void timeUpdate(float f);
    void firstTimeUpdate();//第一次计时器响应，用于初始化显示
private:
	CC_SYNTHESIZE_READONLY(int ,fen,Fen);
	CC_SYNTHESIZE_READONLY(int ,miao,Miao);
	
	std::function<void(jishiqi*, jishiqi_type)> m_callback;
private:
	static jishiqi * instance;
	bool isForever;
};