#pragma once
#include "../head/head.h"
#include "SmartMessageData.h"

class myMessageHander
{
public:
	virtual void sendMessageToServer(int actionId) = 0;//根据不同的消息，发送的数据肯定也不一样
	virtual void receiveMessageFromServer(SmartMessageData * data) = 0;
	virtual void setActionMap() = 0;

	bool isContainAction(int action);

	

protected:
	void addToMap(int action);

private:
	std::map<int, int> _actionValueMap;

	
};