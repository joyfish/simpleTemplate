#pragma once 

#include "cocos2d.h"
#include "SmartMessageData.h"
#include "myMessageHander.h"
USING_NS_CC;


class myMessageManager :public Ref
{
private:
	myMessageManager();
	~myMessageManager();
public:

	static myMessageManager* getInstance();

	void rigeterMessageListener( int messageAction, myMessageHander *listener);
	void destroyrMessageListener( int messageAction, myMessageHander *listener);

	void postReceiveMessage(SmartMessageData * msgData);//从服务器收到消息，把它分发到对应的myMessageHander
	void sendMessage(SmartMessageData * msgData);//发送消息到服务器,最终是由mySocketUtil发送的

private:
	
	std::multimap< int, myMessageHander*>_listenerMap;

	static myMessageManager * _instance;
};