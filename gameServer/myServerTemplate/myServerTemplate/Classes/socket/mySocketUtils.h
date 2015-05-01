#pragma once
#include "../head/head.h"
#include "SocketServer.h"
#include "SmartMessageData.h"



class mySocketUtils :public SocketServer::socketDegelate
{
public:
	mySocketUtils() :m_callback(nullptr)
	{}
	static mySocketUtils* getInstance();
	void destroyInstance();

	SocketServer * getSendSocket();

	bool startServer(std::function<void(bool)> callback = nullptr);

	void sendToServer(SmartMessageData * msg);
public:

	virtual void onStart(SocketServer* ws,const char* ip) ;
	virtual void onNewConnection(SocketServer* ws,HSocket socket) ;
	virtual void onRecv(SocketServer* ws, const char* data, int count) ;
	virtual void onDisconnect(SocketServer* ws,HSocket socket) ;

private:
	~mySocketUtils();

private:
	SocketServer* _wsiSendText;

	static mySocketUtils * _instance;

	std::function<void(bool)> m_callback;

};