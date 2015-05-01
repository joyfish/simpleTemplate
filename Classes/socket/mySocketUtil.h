#pragma once
#include "cocos2d.h"
#include "SocketClient.h"
#include "SmartMessageData.h"

USING_NS_CC;


class mySocketUtil :public Ref,public SocketClient::socketDelete
{
public:
	mySocketUtil() :m_callback(nullptr)
	{}
	static mySocketUtil* getInstance();
	void destroyInstance();

	SocketClient * getSendSocket();

	bool connectToServer(const char* serverIP, unsigned short port, std::function<void(bool)> callback);

	void sendToServer(SmartMessageData * msg);
public:

	virtual void onOpen(SocketClient* ws);
	virtual void onMessage(SocketClient* ws,const char* data, int count);
	virtual void onClose(SocketClient* ws);
	virtual void onError(SocketClient* ws, const SocketClient::ErrorCode& error);
private:
	~mySocketUtil();

private:
	SocketClient* _wsiSendText;

	static mySocketUtil * _instance;

	std::function<void(bool)> m_callback;

};