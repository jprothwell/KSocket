/*
 *  kunixsocketadapter.h
 *  ksocket
 *
 *  Created by Kewei He on 12/19/10.
 *  Copyright 2010 newsloch. All rights reserved.
 *
 */
#ifndef _KUNIXSOCKETADAPTER_H_
#define _KUNIXSOCKETADAPTER_H_

#include "knp.h"
#include "ksocketadapter.h"
#include <stdexcept>
using std::runtime_error;

class KUnixSocketAdapter : public KSocketAdapter {
public:
    KUnixSocketAdapter() : m_sock(0)
    {
        if ((m_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
            throw runtime_error("Socket creation");
    }
    
    void connect(const char* addr, int port)
    {
        m_svaddr.sin_family = AF_INET;
        m_svaddr.sin_port   = htons(port);
        m_svaddr.sin_addr.s_addr = inet_addr(addr);
        memset(&(m_svaddr.sin_zero), 0, 8);
        
        if (::connect(m_sock, (sockaddr*)&m_svaddr, sizeof(sockaddr)) == -1)
            throw runtime_error("Connect");
    }
    
    int send(byte data[], size_t len)
    {
        size_t size;
        if ((size = ::send(m_sock, data, len, 0)) == -1) 
            throw runtime_error("send error");
        
        return size;
    }
    
    int receive(byte data[], size_t len)
    {
        size_t size;
        if ((size = recv(m_sock, data, len , 0)) == -1)
            throw runtime_error("receive error");
        
        data[size] = 0;
        return size;
    }
    
    ~KUnixSocketAdapter()
    {
        close(m_sock);
    }
    
    
private:
    int m_sock;
    sockaddr_in m_svaddr;
    
};


#endif