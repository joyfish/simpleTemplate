#include "socket\myMessageHander.h"

class hello :public myMessageHander
{
public:
	virtual bool init();

	static hello * create();

	virtual void sendMessageToServer(int actionId);//根据不同的消息，发送的数据肯定也不一样
	virtual void receiveMessageFromServer(SmartMessageData * data);
	virtual void setActionMap();
};