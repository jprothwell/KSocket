#ifndef _KSOCKETADAPTERFACTORY_H_
#define _KSOCKETADAPTERFACTORY_H_

#include "kwinsocketadapter.h"
#include "kunixsocketadapter.h"

namespace KSocket {

class SocketAdapterFactory {
public:
    static SocketAdapter* getSocketAdapter()
    {
        assert(m_socketAdapter);

        return m_socketAdapter;
    }
private:
    SocketAdapterFactory() {}

    static SocketAdapter* m_socketAdapter;
};

#ifdef KWIN
SocketAdapter* SocketAdapterFactory::m_socketAdapter
        = new WinSocketAdapter();
#else
SocketAdapter* SocketAdapterFactory::m_socketAdapter
        = new UnixSocketAdapter();
#endif

}
#endif