/*
 *  kwinserversocketadapter.h
 *  ksocket
 *
 *  Created by Kewei He on 12/19/10.
 *  Copyright 2010 newsloch. All rights reserved.
 *
 */
#include "knp.h"
#include "kserversocketadapter.h"
#include <stdexcept>
using std::runtime_error;

class KWinServerAdapter : public KServerSocketAdapter {
public:
    KWinServerAdapter(int port = 22222)
            : m_svsock(INVALID_SOCKET)
            , m_clsock(INVALID_SOCKET)
            , m_svaddr(0)
            , m_backlog(0)
    {
        _itoa_s(port, m_port, 5, 10);
        init();
    }

    int accept()
    {
        m_clsock = ::accept(m_svsock, (struct sockaddr*)0, (int*)0);
        if (m_clsock == INVALID_SOCKET) 
            throw runtime_error("Accept error");
        
        return 1;
    }

    int send(byte* data, size_t len)
    {
        size_t size;
        if ((size = ::send(m_clsock, data, len, 0)) == -1) 
            throw runtime_error("send error");
        
        return size;
    }

    int receive(byte* data, size_t len)
    {
        size_t size;
        if ((size = recv(m_clsock, data, len , 0)) == -1)
            throw runtime_error("receive error");
        
        data[size] = 0;
        return size;
    }



private:
    char m_port[5];
    SOCKET m_svsock;
    SOCKET m_clsock;
    int m_backlog;
    addrinfo* m_svaddr;
	addrinfo m_hints;
    
    void init();
};

void KWinServerAdapter::init()
{
    WSADATA wsaData;

    int res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (res != 0) 
        throw runtime_error("WSAStartup failed");

    ZeroMemory(&m_hints, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;
    m_hints.ai_flags = AI_PASSIVE;

    res = getaddrinfo(NULL, m_port, &m_hints, &m_svaddr);
    if (res != 0)
        throw runtime_error("getaddrinfo failed");

    m_svsock = socket(m_svaddr->ai_family, m_svaddr->ai_socktype, 
                          m_svaddr->ai_protocol);
    if (m_svsock == INVALID_SOCKET)
        throw runtime_error("socket failed");

    res = bind(m_svsock, m_svaddr->ai_addr, (int)m_svaddr->ai_addrlen);
    if (res == SOCKET_ERROR)
        throw runtime_error("bind error");

    freeaddrinfo(m_svaddr);

    res = listen(m_svsock, m_backlog);
    if (res == SOCKET_ERROR)
        throw runtime_error("listen error");

}

