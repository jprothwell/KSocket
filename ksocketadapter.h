/*
 *  ksocketadapter.h
 *  ksocket
 *
 *  Created by Kewei He on 12/14/10.
 *  Copyright 2010 Northeastern University. All rights reserved.
 *
 */

#ifndef _KSOCKETADAPTER_H_
#define _KSOCKETADAPTER_H_

#include "ktype.h"

namespace KSocket {
    
class SocketAdapter {
public:
    virtual void connect(const char* address, int port) = 0;
    virtual int send(byte data[], size_t len) = 0;
    virtual int receive(byte data[], size_t len) = 0;
    
    virtual ~SocketAdapter() 
    {
    }
};

}

#endif

