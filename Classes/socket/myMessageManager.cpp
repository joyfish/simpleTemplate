#include "myMessageManager.h"
#include "mySocketUtil.h"

myMessageManager * myMessageManager::_instance = nullptr;

myMessageManager::myMessageManager()
{

}

myMessageManager::~myMessageManager()
{

}

myMessageManager* myMessageManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new myMessageManager;
	}
	return _instance;
}

void myMessageManager::rigeterMessageListener(int messageAction, myMessageHander *listener)
{
	_listenerMap.insert(std::pair< int, myMessageHander*>(messageAction, listener));
	
}

void myMessageManager::destroyrMessageListener( int messageAction, myMessageHander *listener)
{
	std::multimap< int, myMessageHander*>::iterator itor = _listenerMap.begin();

	std::vector<std::multimap< int, myMessageHander *>::iterator> vec;
	for (; itor != _listenerMap.end(); itor++)
	{
		if (itor->first == messageAction&&itor->second == listener)
		{
			vec.push_back(itor);
			break;
		}
	}
	//直接在for循环里删除，好像会有问题，所以这样处理
	for (std::vector<std::multimap< int, myMessageHander *>::iterator>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		_listenerMap.erase(*it);
	}

}

void myMessageManager::postReceiveMessage(SmartMessageData * msgData)
{
	std::multimap< int, myMessageHander*>::iterator itor = _listenerMap.begin();
	for (; itor != _listenerMap.end(); itor++)
	{
		myMessageHander * hander = itor->second;
		if (hander->isContainAction(msgData->getAction()))
		{
			hander->receiveMessageFromServer(msgData);
		}
	}
}

void myMessageManager::sendMessage(SmartMessageData * msgData)
{
	mySocketUtil::getInstance()->sendToServer(msgData);
	CC_SAFE_RELEASE_NULL(msgData);
}