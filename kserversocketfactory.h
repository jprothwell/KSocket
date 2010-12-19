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
    static KServerSocketAdapter* getServerAdapter()
    {
        assert(m_serverAdapter);
        
        return m_serverAdapter;
    }
private:
    KServerSocketFactory() {}
    static KServerSocketAdapter* m_serverAdapter;
};

#if defined KWIN
KServerSocketAdapter* KServerSocketFactory::m_serverAdapter 
        = new KWinServerAdapter();
#else
KServerSocketAdapter* KServerSocketFactory::m_serverAdapter 
        = new KUnixServerAdapter();
#endif

#endif // _KSERVERSOCKETFACTORY_H_