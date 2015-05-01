#include "jishiqi.h"

jishiqi * jishiqi::instance = nullptr;

void jishiqi::createForverJishiqi( std::function<void(jishiqi*, jishiqi_type)> callback,int fen, int miao)
{
	if (instance == nullptr)
	{
		instance = new jishiqi;
		if (instance->initJishiqi(callback, fen, miao, true))
		{
			instance->autorelease();
			instance->retain();
		}
		else
			return;
	}
	else
	{
		instance->m_callback = callback;

		if (fen != UNVALID_FEN||miao != UNVALID_MIAO)
			instance->resetTime(fen, miao);
	}

	return ;
}

void jishiqi::destroyInstance()
{
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(jishiqi::timeUpdate), instance);
	CC_SAFE_DELETE(instance);
}

jishiqi* jishiqi::create(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao)
{
	jishiqi *g_jishiqi = new jishiqi;
	if (g_jishiqi->initJishiqi(callback, fen, miao,false))
	{
		g_jishiqi->autorelease();
		return g_jishiqi;
	}

	delete g_jishiqi;
	return NULL;
}

void jishiqi::resetTime(int fen, int miao)
{
	this->fen = fen;
	this->miao = miao;

	this->schedule(schedule_selector(jishiqi::timeUpdate), 1);

	this->firstTimeUpdate();
}

bool jishiqi::initJishiqi(std::function<void(jishiqi*, jishiqi_type)> callback, int fen, int miao, bool isForever)
{
	this->fen = fen;
	this->miao = miao;
	this->m_callback = callback;

	if (isForever)
		Director::getInstance()->getScheduler()->schedule(schedule_selector(jishiqi::timeUpdate), this, 1, 1);
	else
		this->schedule(schedule_selector(jishiqi::timeUpdate), 1);

	this->firstTimeUpdate();

	return true;
}

void jishiqi::timeUpdate(float f)
{
	
	if(this->miao==0)
	{
		if(fen>0)
		{
			this->fen--;
		    this->miao=59;
		}
		else
        {
			m_callback(this,jishiqi_type::jishiqi_end);
			this->unschedule(schedule_selector(jishiqi::timeUpdate));
			return;
	    }
	}
	else
		this->miao--;

	m_callback(this, jishiqi_type::jishiqi_ing);
}

void jishiqi::firstTimeUpdate()
{
	m_callback(this, jishiqi_type::jishiqi_start);
}

