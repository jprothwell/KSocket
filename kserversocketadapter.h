/*
 *  ksocketadapter.h
 *  ksocket
 *
 *  Created by Kewei He on 12/14/10.
 *  Copyright 2010 Northeastern University. All rights reserved.
 *
 */
#ifndef _KSERVERSOCKETADAPTER_H_
#define _KSERVERSOCKETADAPTER_H_

#include "ktype.h"

class KServerSocketAdapter {
public:
    virtual int accept() = 0;
    virtual int send(byte data[], size_t len) = 0;
    virtual int receive(byte data[], size_t len) = 0;
    
    virtual ~KServerSocketAdapter(){}
};

#endif