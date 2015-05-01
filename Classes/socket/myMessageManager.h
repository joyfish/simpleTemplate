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

	void postReceiveMessage(SmartMessageData * msgData);//�ӷ������յ���Ϣ�������ַ�����Ӧ��myMessageHander
	void sendMessage(SmartMessageData * msgData);//������Ϣ��������,��������mySocketUtil���͵�

private:
	
	std::multimap< int, myMessageHander*>_listenerMap;

	static myMessageManager * _instance;
};