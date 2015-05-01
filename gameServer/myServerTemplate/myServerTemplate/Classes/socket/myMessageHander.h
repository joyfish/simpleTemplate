#pragma once
#include "../head/head.h"
#include "SmartMessageData.h"

class myMessageHander
{
public:
	virtual void sendMessageToServer(int actionId) = 0;//���ݲ�ͬ����Ϣ�����͵����ݿ϶�Ҳ��һ��
	virtual void receiveMessageFromServer(SmartMessageData * data) = 0;
	virtual void setActionMap() = 0;

	bool isContainAction(int action);

	

protected:
	void addToMap(int action);

private:
	std::map<int, int> _actionValueMap;

	
};