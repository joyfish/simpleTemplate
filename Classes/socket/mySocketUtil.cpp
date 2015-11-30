#include "mySocketUtil.h"
#include "SmartMessageData.h"
#include "myMessageManager.h"
#include "WriteDataToBufferUtils.h"
#include "msgBody\msgBody.h"
mySocketUtil * mySocketUtil::_instance = nullptr;


mySocketUtil::~mySocketUtil()
{
	if (_wsiSendText)
	{
		delete _wsiSendText;
		_wsiSendText = nullptr;
	}
}

mySocketUtil* mySocketUtil::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new mySocketUtil();
	}

	return _instance;
}

void mySocketUtil::destroyInstance()
{
	delete _instance;
	_instance = 0;
}

SocketClient * mySocketUtil::getSendSocket()
{
	return _wsiSendText;
}

bool mySocketUtil::connectToServer(const char* serverIP, unsigned short port, std::function<void(bool)> callback)
{
	_wsiSendText = new SocketClient();
	_wsiSendText->setSocketDelete(this);

	_wsiSendText->connectServer(serverIP,port);

	m_callback = callback;
	return true;
}

void mySocketUtil::sendToServer(SmartMessageData * msg)
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

	delete[] str;
}

void mySocketUtil::onOpen(SocketClient* ws)
{
	if (ws == this->_wsiSendText)
	{
		if (m_callback!=nullptr)
			m_callback(true);
	}
}
void mySocketUtil::onMessage(SocketClient* ws,const char* data, int count)
{
	if (ws == this->_wsiSendText)
	{
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

			SmartMessageData * msgData = SmartMessageData::create();
			msgData->setAction(action);

			msgData->setDataLength(msgBodyLen);
			msgData->setData(msgBody, msgBodyLen);

			delete[] msgBody;

			myMessageManager::getInstance()->postReceiveMessage(msgData);
		}
	}
}

void mySocketUtil::onClose(SocketClient* ws)
{
	if (ws == this->_wsiSendText)
	{

	}
}
void mySocketUtil::onError(SocketClient* ws, const SocketClient::ErrorCode& error)
{
	if (ws == this->_wsiSendText)
	{
		switch (error)
		{
		case SocketClient::ErrorCode::CONNECT_ERROR:
			{
				if (m_callback)
					(m_callback)(false);
			}
			break;
		case SocketClient::ErrorCode::DISCONNECT_ERROR:
			{
			
			}
			break;
		default:
			break;
		}
		
	}
}