#include "hello.h"
#include "socket\myMessageManager.h"
#include "head\msgBody.h"
bool hello::init()
{
	myMessageManager::getInstance()->rigeterMessageListener(CMD_Constant::ACTION_TEST1, this);

	this->addToMap(CMD_Constant::ACTION_TEST1);
	return true;
}

hello * hello::create()
{
	hello *hh = new hello;
	hh->init();
	return hh;
}

void hello::sendMessageToServer(int actionId)
{

}
void hello::receiveMessageFromServer(SmartMessageData * data)
{
	int actionId = data->getAction();
	switch (actionId)
	{
	case CMD_Constant::ACTION_TEST1:
	{
		msgBody_sample_1 msg;
		data >> msg;
		int i = 0;
		msg.setBBB("i have received");
		SEND_MSGBODY_TO_SERVER(msg);
	}
	default:
		break;
	}
}
void hello::setActionMap()
{

}