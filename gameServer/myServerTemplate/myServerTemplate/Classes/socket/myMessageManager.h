#pragma once 

#include "../head/head.h"
#include "SmartMessageData.h"
#include "myMessageHander.h"


class myMessageManager 
{
private:
	myMessageManager();
	~myMessageManager();
public:

	static myMessageManager* getInstance();

	void rigeterMessageListener(int messageAction, myMessageHander *listener);
	void destroyrMessageListener( int messageAction, myMessageHander *listener);

	void postReceiveMessage(SmartMessageData * msgData);//�ӷ������յ���Ϣ�������ַ�����Ӧ��myMessageHander
	void sendMessage(SmartMessageData * msgData);//������Ϣ��������,��������mySocketUtils���͵�

private:
	
	std::multimap< int, myMessageHander*>_listenerMap;

	static myMessageManager * _instance;
};