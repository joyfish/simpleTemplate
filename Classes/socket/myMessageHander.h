#pragma once
#include "cocos2d.h"
#include "SmartMessageData.h"
#include "socket\mySocketUtil.h"
USING_NS_CC;

template <class T>
void SEND_MSGBODY_TO_SERVER(T msgBody)
{
	SmartMessageData * data = SmartMessageData::create();
	data->retain();
	data << msgBody;
	data->setAction(msgBody.CMD_ID);
	mySocketUtil::getInstance()->sendToServer(data);
	CC_SAFE_RELEASE_NULL(data);
}

class myMessageHander
{
public:
	virtual void sendMessageToServer(int actionId) = 0;//根据不同的消息，发送的数据肯定也不一样
	virtual void receiveMessageFromServer(SmartMessageData * data) = 0;

protected:
	void registerListener(int actionId);
	void destoryListener(int actionId);
private:

	
};