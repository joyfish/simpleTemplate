#include "socket\myMessageHander.h"

class hello :public myMessageHander
{
public:
	virtual bool init();

	static hello * create();

	virtual void sendMessageToServer(int actionId);//���ݲ�ͬ����Ϣ�����͵����ݿ϶�Ҳ��һ��
	virtual void receiveMessageFromServer(SmartMessageData * data);
	virtual void setActionMap();
};