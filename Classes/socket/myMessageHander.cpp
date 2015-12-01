#include "myMessageHander.h"
#include "socket\myMessageManager.h"

void myMessageHander::registerListener(int actionId)
{
	myMessageManager::getInstance()->rigeterMessageListener(actionId, this);
	_actionValueMap.insert(std::pair<int, int>(actionId, actionId));
}

void myMessageHander::destoryListener(int actionId)
{
	myMessageManager::getInstance()->destroyrMessageListener(actionId, this);
}
