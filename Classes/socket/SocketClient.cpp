#include "SocketClient.h"
 
 
SocketClient::SocketClient(void) :
    _socketDelete(nullptr),
    _socektClient(0)
{
	_bInitSuccess = false;
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 0);
    WSADATA wsaData;
    int nRet = WSAStartup(wVersionRequested, &wsaData);
    if (nRet != 0) 
    {
        fprintf(stderr, "Initilize Error!\n");
        return;
    }
    _bInitSuccess = true;
    #endif
  
}
 
 
SocketClient::~SocketClient(void)
{
    if (_socektClient != 0)
    {
        _mutex.lock();
        this->closeConnect(_socektClient);
        _mutex.unlock();
    }

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
    if (_bInitSuccess)  
    {  
        WSACleanup();  
    }  
    #endif   
}

void SocketClient::closeConnect(HSocket socket)  
{  
	_socketDelete->onClose(this);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
    close(socket);  
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
    closesocket(socket);  
    #endif  

}

bool SocketClient::error(HSocket socket)  
{  
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
    return socket == SOCKET_ERROR;  
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
    return socket < 0;  
    #endif  
}
 
bool SocketClient::initClient()
{
    if (_socektClient != 0)
    {
        _mutex.lock();
        this->closeConnect(_socektClient);
        _mutex.unlock();
    }
 
    _socektClient = socket(AF_INET, SOCK_STREAM, 0);
    if (error(_socketServer))
    {
        log("init client error!");
        _socektClient = 0;
        return false;
    }
 
    return true;
}
 
void SocketClient::connectServer(const char* serverIP, unsigned short port)
{
	std::thread connectThread(&SocketClient::connectProc,this,serverIP,port);
	connectThread.detach();
}

void SocketClient::connectProc(const char* serverIP, unsigned short port)
{
	if (!this->initClient())
    {
        return;
    }
 
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
 
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
 
    int ret = 0;
    ret = connect(_socektClient, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        this->closeConnect(_socektClient);
        _socektClient = 0;
		if(_socketDelete)
			_socketDelete->onError(this,ErrorCode::CONNECT_ERROR);
        return;
    }
	else
	{
		_socketDelete->onOpen(this);
	}
 
    std::thread recvThread(&SocketClient::recvMessage, this);
    recvThread.detach();
    return;
}
 
void SocketClient::recvMessage()
{
    char recvBuf[1024];
    int ret = 0;
    while (true)
    {
        ret = recv(_socektClient, recvBuf, sizeof(recvBuf), 0);
        if (ret < 0)
        {
            log("recv error");
            break;
        }
        if (ret > 0 && _socketDelete != nullptr)
        {
			_socketDelete->onMessage(this,recvBuf, ret);
        }
    }
    _mutex.lock();
    this->closeConnect(_socektClient);
    if (_socketDelete != nullptr)
    {
		_socketDelete->onError(this,ErrorCode::DISCONNECT_ERROR);
    }
    _socektClient = 0;
    _mutex.unlock();
}
 
void SocketClient::sendMessage(const char* data, int count)
{
    if (_socektClient != 0)
    {
        int ret = send(_socektClient, data, count, 0);
        if (ret < 0)
        {
            log("send error!");
        }
    }
}