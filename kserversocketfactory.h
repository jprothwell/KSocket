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

class KServerSocketFactory {
public:
    static KServerSocketAdapter* getSocketAdapter()
    {
        assert(socketAdapter);
        
        return socketAdapter;
    }
private:
    KServerSocketFactory() {}
    static KServerSocketAdapter* socketAdapter;
};

#if defined KWIN
KServerSocketAdapter* KServerSocketFactory::socketAdapter 
        = new KWinServerAdapter();
#else
KServerSocketAdapter* KServerSocketFactory::socketAdapter 
        = new KUnixServerAdapter();
#endif

#endif // _KSERVERSOCKETFACTORY_H_