/*
 *  kserversocketfactory.h
 *  ksocket
 *
 *  Created by Kewei He on 12/19/10.
 *  Copyright 2010 Newsloch. All rights reserved.
 *
 */
#ifndef _KSERVERSOCKETFACTORY_H_
#define _KSERVERSOCKETFACTORY_H_

#if defined (_WIN32) || (WIN32) || (_MSC_VER)
#include "kwinserveradapter.h"
#else
#include "kunixserveradapter.h"
#endif

namespace KSocket {
    
class ServerSocketFactory {
public:
    static ServerSocketAdapter* getServerAdapter()
    {
        assert(m_serverAdapter);
        
        return m_serverAdapter;
    }
private:
    ServerSocketFactory() {}
    static ServerSocketAdapter* m_serverAdapter;
};

#if defined KWIN
ServerSocketAdapter* ServerSocketFactory::m_serverAdapter 
        = new WinServerAdapter();
#else
ServerSocketAdapter* ServerSocketFactory::m_serverAdapter 
        = new UnixServerAdapter();
#endif
    
}

#endif // _KSERVERSOCKETFACTORY_H_