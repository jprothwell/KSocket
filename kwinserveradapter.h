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
#include <stdexp>
using std::runtime_error

class KWinServerAdapter : public KServerSocketAdapter {
public:
    KUnixServerAdapter(int port = 22222)
            : m_port(port)
            , m_svsock(0)
            , m_clsock(0)
            , m_backlog(0)
    {
        init();
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

