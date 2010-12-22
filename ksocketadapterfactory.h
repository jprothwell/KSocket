#ifndef _KSOCKETADAPTERFACTORY_H_
#define _KSOCKETADAPTERFACTORY_H_

#include "kwinsocketadapter.h"
#include "kunixsocketadapter.h"

namespace KSocket {

class SocketAdapterFactory {
public:
    static SocketAdapter* createSocketAdapter()
    {
#ifdef KWIN
        return new WinSocketAdapter();
#else
        return new UnixSocketAdapter();
#endif
    }
private:
    SocketAdapterFactory() {}
};

}
#endif