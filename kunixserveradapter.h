/*
 *  kunixadapter.h
 *  ksocket
 *
 *  Created by Kewei He on 12/14/10.
 *  Copyright 2010 Northeastern University. All rights reserved.
 *
 */
#include "knp.h"
#include "kserversocketadapter.h"
#include <stdexcept>
using std::runtime_error;

class KUnixServerAdapter : public KServerSocketAdapter {
public:
    KUnixServerAdapter(int port = 22222)
            : m_port(port)
            , m_svsock(0)
            , m_clsock(0)
            , m_backlog(0)
    {
        init();
    }
    
    int accept()
    {
        socklen_t sin_size = sizeof(struct sockaddr_in);
		if ((m_clsock = ::accept(m_svsock, 
                (sockaddr*)&m_claddr, &sin_size)) == -1) {
			throw runtime_error("accept error");
		}
        return 1;
    }
    
    int send(byte data[], size_t len)
    {
        size_t size;
        if ((size = ::send(m_clsock, data, len, 0)) == -1) 
            throw runtime_error("send error");
        
        return size;
    }
    
    int receive(byte data[], size_t len)
    {
        size_t size;
        if ((size = recv(m_clsock, data, len , 0)) == -1)
            throw runtime_error("receive error");
        
        data[size] = 0;
        return size;
    }
    
    ~KUnixServerAdapter()
    {
    }
    
private:
    int m_port;
    int m_svsock;
    int m_clsock;
    int m_backlog;
    sockaddr_in m_svaddr;
	sockaddr_in m_claddr;
    
    void init();
};

void KUnixServerAdapter::init()
{
    if ((m_svsock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw runtime_error("socket error");

    m_svaddr.sin_family = AF_INET;
    m_svaddr.sin_port   = htons(m_port);
    m_svaddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(m_svaddr.sin_zero), 0, 8);

    if (bind(m_svsock, (sockaddr*)&m_svaddr, 
             sizeof(sockaddr)) == -1) 
        throw runtime_error("bind error");

    if (listen(m_svsock, m_backlog) == -1) 
        throw runtime_error("listen error");
}