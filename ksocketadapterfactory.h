#ifndef _KSOCKETADAPTERFACTORY_H_
#define _KSOCKETADAPTERFACTORY_H_

#include "kwinsocketadapter.h"
#include "kunixsocketadapter.h"

class KSocketAdapterFactory {
public:
    static KSocketAdapter* getSocketAdapter()
    {
        assert(m_socketAdapter);

        return m_socketAdapter;
    }
private:
    KSocketAdapterFactory() {}

    static KSocketAdapter* m_socketAdapter;
};

#ifdef KWIN
KSocketAdapter* KSocketAdapterFactory::m_socketAdapter
        = new KWinSocketAdapter();
#else
KSocketAdapter* KSocketAdapterFactory::m_socketAdapter
        = new KUnixSocketAdapter();
#endif



#endif