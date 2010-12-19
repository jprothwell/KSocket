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

#include "kunixserveradapter.h"
#include "kwinserveradapter.h"

class KServerSocketFactory {
public:
    static KServerSocketAdapter* getSocketAdapter()
    {
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