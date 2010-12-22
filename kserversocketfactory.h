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
    static ServerSocketAdapter* createServerAdapter()
    {
#if defined KWIN
        return new WinServerAdapter();
#else
        return new UnixServerAdapter();
#endif
    }
    
    static ServerSocketAdapter* createServerAdapter(int port)
    {
#if defined KWIN
        return new WinServerAdapter(port);
#else
        return new UnixServerAdapter(port);
#endif        
    }
private:
    ServerSocketFactory() {}
};
    
}

#endif // _KSERVERSOCKETFACTORY_H_