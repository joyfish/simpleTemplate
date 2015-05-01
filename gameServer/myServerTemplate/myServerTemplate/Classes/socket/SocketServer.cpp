#include "SocketServer.h"
 
SocketServer* SocketServer::create()
{
    auto server = new SocketServer;
 
    return server;
}
 
SocketServer::SocketServer() :
    _socketServer(0),
    _socketDelete(nullptr)
{

	_bInitSuccess = false;
#if defined(_WIN32)
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
 
SocketServer::~SocketServer()
{
    _clientSockets.clear();
 
    if (_socketServer)
    {
        this->closeConnect(_socketServer);
    }

#if defined(_WIN32)  
    if (_bInitSuccess)  
    {  
        WSACleanup();  
    }  
#endif  
};

void SocketServer::closeConnect(HSocket socket)  
{  
	//_socketDelete->onClose(this);

#if defined(LINUX)
    close(socket);  
#elif defined(_WIN32)
    closesocket(socket);  
#endif  

}

bool SocketServer::error(HSocket socket)  
{  
#if defined(_WIN32)
    return socket == SOCKET_ERROR;  
#elif defined(LINUX) 
    return socket < 0;  
#endif  
}
 
 
bool SocketServer::startServer()
{
    if (!initServer())
    {
        return false;
    }
 
    return true;
}
 
bool SocketServer::initServer()
{
    if (_socketServer != 0)
    {
        this->closeConnect(_socketServer);
    }
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (error(_socketServer))
    {
        _socketServer = 0;
        return false;
    }
    do 
    {
        struct sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));
 
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_port = htons(20000);
        sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        int ret = 0;
        ret = bind(_socketServer, (const sockaddr*)&sockAddr, sizeof(sockAddr));
        if (ret < 0)
        {
            log("bind error!");
            break;
        }
     
        ret = listen(_socketServer, 5);
        if (ret < 0)
        {
            log("listen error!");
            break;
        }
        // start 
        char hostName[256];
        gethostname(hostName, sizeof(hostName));
        struct hostent* hostInfo = gethostbyname(hostName);
        char* ip = inet_ntoa(*(struct in_addr *)*hostInfo->h_addr_list);
        this->acceptClient();
 
        if (_socketDelete != nullptr)
        {
            log("start server!");
            _socketDelete->onStart(this,ip);
        }
 
        return true;
 
    } while (false);
     
    this->closeConnect(_socketServer);
    _socketServer = 0;
    return false;
}
 
void SocketServer::acceptClient()
{
    std::thread th(&SocketServer::acceptFunc, this);
    th.join();
}
 
void SocketServer::acceptFunc()
{
    int len = sizeof(sockaddr);
    struct sockaddr_in sockAddr;
    while (true)
    {   
        HSocket clientSock = accept(_socketServer, (sockaddr*)&sockAddr, &len);
        if (error(clientSock))
        {
            log("accept error!");
            break;
        }
 
        this->newClientConnected(clientSock);
    }
}
 
void SocketServer::newClientConnected(HSocket socket)
{
    log("new connect!");
 
    _clientSockets.push_back(socket);
    std::thread th(&SocketServer::recvMessage, this, socket);
    th.detach();
 
    if (_socketDelete != nullptr)
    {
        _socketDelete->onNewConnection(this,socket);
    }
}
 
void SocketServer::recvMessage(HSocket socket)
{
    char buff[1024];
    int ret = 0;
 
    while (true)
    {
        ret = recv(socket, buff, sizeof(buff), 0);
        if (ret < 0)
        {
            log("recv(%d) error!", socket);
            _mutex.lock();
            this->closeConnect(socket);
            _clientSockets.remove(socket);
            if (_socketDelete != nullptr)
            {
                _socketDelete->onDisconnect(this,socket);
            }
            _mutex.unlock();
 
            break;
        }
        else
        {
            buff[ret] = 0;
            log("recv msg : %s", buff);
            if (ret > 0 && _socketDelete != nullptr)
            {
                _socketDelete->onRecv(this,buff, ret);
            }
        }
    }
}
 
void SocketServer::sendMessage(HSocket socket, const char* data, int count)
{
    for (auto& sock : _clientSockets)
    {
        if (sock == socket)
        {
            int ret = send(socket, data, count, 0);
            if (ret < 0)
            {
                log("send error!");
            }
            break;
        }
    }
 
}
 
void SocketServer::sendMessage(const char* data, int count)
{
    for (auto& socket : _clientSockets)
    {
        int ret = send(socket, data, count, 0);
        if (ret < 0)
        {
            log("send error!");
        }
 
    }
 
}