#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "cocos2d.h"
#include <list>
#include <thread>
USING_NS_CC;
// 对于windows平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#define HSocket SOCKET
// 对于android平台
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <arpa/inet.h>   // for inet_**
#include <netdb.h>   // for gethost**
#include <netinet/in.h>  // for sockaddr_in
#include <sys/types.h>   // for socket
#include <sys/socket.h>  // for socket
#include <unistd.h>
#include <stdio.h>        // for printf
#include <stdlib.h>  // for exit
#include <string.h>  // for bzero
#define HSocket int
#endif 

class SocketClient 
{
public:
	enum class ErrorCode
	{
		CONNECT_ERROR,//没连上
		DISCONNECT_ERROR//断开连接
	};

	class socketDelete
	{
	public:
		
		virtual void onOpen(SocketClient* ws) = 0;
		virtual void onMessage(SocketClient* ws, const char* data, int count) = 0;
		virtual void onClose(SocketClient* ws) = 0;
		virtual void onError(SocketClient* ws, const SocketClient::ErrorCode& error) = 0;
	};
public:
    SocketClient(void);
    ~SocketClient(void);

	virtual void setSocketDelete(socketDelete * g_delete){_socketDelete = g_delete;};
protected:
        void closeConnect(HSocket socket);
        bool error(HSocket socket);
      
protected:
        std::mutex _mutex;
      
private:
        bool _bInitSuccess;
public:
 
    void connectServer(const char* serverIP, unsigned short port);
    void sendMessage(const char* data, int count);
 
private:
    bool initClient();
    void recvMessage();
	void connectProc(const char* serverIP, unsigned short port);
 
private:
    HSocket _socketServer;
    HSocket _socektClient;

	socketDelete * _socketDelete;
};
 
#endif