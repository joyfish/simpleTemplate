#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__
#include "../head/head.h"
#include <list>
#include <thread>
#include <mutex>
// 对于windows平台
#if defined(_WIN32)
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#define HSocket SOCKET
// 对于android平台
#elif defined(LINUX)
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
class SocketServer
{
public:
	class socketDegelate
	{
	public:
		
		virtual void onStart(SocketServer* ws,const char* ip) = 0;
		virtual void onNewConnection(SocketServer* ws,HSocket socket) = 0;
		virtual void onRecv(SocketServer* ws, const char* data, int count) = 0;
		virtual void onDisconnect(SocketServer* ws,HSocket socket) = 0;
	};
public:
    static SocketServer* create();
 
    SocketServer();
    ~SocketServer();
 
    bool startServer();
    void sendMessage(HSocket socket, const char* data, int count);
    void sendMessage(const char* data, int count);

	void setSocketDegelate(socketDegelate * g_degelate){_socketDelete = g_degelate;};

protected:
    void closeConnect(HSocket socket);
    bool error(HSocket socket);
protected:
        std::mutex _mutex;
      
private:
        bool _bInitSuccess;
private:
    bool initServer();
    void acceptClient();
    void acceptFunc();
    void newClientConnected(HSocket socket);
    void recvMessage(HSocket socket);
     
private:
    HSocket _socketServer;
 
private:
    std::list<HSocket> _clientSockets;
 
	socketDegelate * _socketDelete;
};
 
#endif