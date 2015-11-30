#include "myMessageHander.h"
#include "socket\myMessageManager.h"

void myMessageHander::registerListener(int actionId)
{
	myMessageManager::getInstance()->rigeterMessageListener(actionId, this);
}

void myMessageHander::destoryListener(int actionId)
{
	myMessageManager::getInstance()->destroyrMessageListener(actionId, this);
}
