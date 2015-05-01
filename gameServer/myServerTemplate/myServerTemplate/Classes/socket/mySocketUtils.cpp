#include "mySocketUtils.h"
#include "SmartMessageData.h"
#include "myMessageManager.h"
#include "WriteDataToBufferUtils.h"

mySocketUtils * mySocketUtils::_instance = nullptr;


mySocketUtils::~mySocketUtils()
{
	if (_wsiSendText)
	{
		delete _wsiSendText;
		_wsiSendText = nullptr;
	}
}

mySocketUtils* mySocketUtils::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new mySocketUtils();
	}

	return _instance;
}

void mySocketUtils::destroyInstance()
{
	delete _instance;
	_instance = 0;
}

SocketServer * mySocketUtils::getSendSocket()
{
	return _wsiSendText;
}

bool mySocketUtils::startServer(std::function<void(bool)> callback)
{
	_wsiSendText = new SocketServer();
	_wsiSendText->setSocketDegelate(this);

	_wsiSendText->startServer();

	m_callback = callback;
	return true;
}

void mySocketUtils::sendToServer(SmartMessageData * msg)
{
	int messageLen = msg->getDataLength();
	int action = msg->getAction();

	std::vector<unsigned char>* data = msg->getData();

	char *str = new char[messageLen+4];
	memcpy(str,&action,4);

	for (unsigned int i = 0; i < messageLen; i++)
	{
		str[i+4] = (*data)[i];
	}


	_wsiSendText->sendMessage(str,messageLen+4);

}

void mySocketUtils::onStart(SocketServer* ws,const char* ip)
{
	if (ws == this->_wsiSendText)
	{
		if (m_callback!=nullptr)
			m_callback(true);
	}
}

void mySocketUtils::onNewConnection(SocketServer* ws,HSocket socket)
{

}

void mySocketUtils::onRecv(SocketServer* ws,const char* data, int count)
{
	if (ws == this->_wsiSendText)
	{
		
		int action;//÷∏¡Ó∫≈
	
		memcpy(&action,data,4);

		int msgBodyLen = count - 4;

		char * msgBody = new char[msgBodyLen+1];
		for (int i = 4; i < count; i++)
		{
			msgBody[i - 4] = data[i];
		}
		msgBody[msgBodyLen] = '\0';

		SmartMessageData * msgData = SmartMessageData::create(action);

		msgData->setDataLength(msgBodyLen);
		msgData->setData(msgBody, msgBodyLen);

		delete[] msgBody;

		myMessageManager::getInstance()->postReceiveMessage(msgData);
	
	}
}

void mySocketUtils::onDisconnect(SocketServer* ws,HSocket socket)
{
	if (ws == this->_wsiSendText)
	{

	}
}
