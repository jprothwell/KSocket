#ifndef _KWINSOCKETADAPTER_H_
#define _KWINSOCKETADAPTER_H_

#include "knp.h"

#if defined KWIN

#include "ksocketadapter.h"
#include <stdexcept>
using std::runtime_error;

namespace KSocket{
    
class WinSocketAdapter : public SocketAdapter {
public:
    WinSocketAdapter() : m_svsock(0)
    {
        WSADATA wsaData;
        int res = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (res != 0) 
            throw runtime_error("WSAStartup failed");

        ZeroMemory( &m_hints, sizeof(m_hints) );
        m_hints.ai_family = AF_UNSPEC;
        m_hints.ai_socktype = SOCK_STREAM;
        m_hints.ai_protocol = IPPROTO_TCP;
    }

    void connect(const char* addr, int port) 
    {
        assert(addr);
        assert(m_port);
        assert(port > PORT_LOWER_BOUND);

        _itoa_s(port, m_port, PORT_LEN+1, 10);
        int res = getaddrinfo(addr, m_port, &m_hints, &m_svaddr);
        if (res != 0) 
            throw runtime_error("Socket creation error");

        m_svsock = socket(m_svaddr->ai_family, m_svaddr->ai_socktype, 
                m_svaddr->ai_protocol);
        if (m_svsock == INVALID_SOCKET)
            throw runtime_error("Socket error");
        res = ::connect(m_svsock, m_svaddr->ai_addr, (int)m_svaddr->ai_addrlen);
        if (res == SOCKET_ERROR) 
            throw runtime_error("Connect error");
    }

    int send(byte* data, size_t len)
    {
        assert(data);
        
        size_t size = 0;
        if ((size = ::send(m_svsock, data, len, 0)) == KSOCKET_ERROR) 
            throw runtime_error("Send error");
        
        return size;
    }

    int receive(byte* data, size_t len)
    {
        assert(data);
        
        size_t size = 0;
        if ((size = recv(m_svsock, data, len , 0)) == KSOCKET_ERROR)
            throw runtime_error("Receive error");
        
        data[size] = 0;
        return size;
    }

    ~WinSocketAdapter()
    {
        WSACleanup();
        closesocket(m_svsock);
    }

private:
    SOCKET m_svsock;
    char m_port[PORT_LEN];
    addrinfo *m_svaddr;
    addrinfo m_hints;

};
    
}

#endif

#endif