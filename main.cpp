/*
 *  main.cpp
 *  ksocket
 *
 *  Created by Kewei He on 12/14/10.
 *  Copyright 2010 Northeastern University. All rights reserved.
 *
 */

#include "kserversocketfactory.h"
#include <iostream>
using namespace std;

int main()
{
    KServerSocketAdapter* server = 
        KServerSocketFactory::getSocketAdapter();
    
    const int buflen = 512;
    byte buf[buflen];
    strcpy(buf, "hello, world");
    
    if (server->accept()) 
        while (1) {
            server->send(buf, strlen(buf) + 1);
            if (server->receive(buf, buflen))
                cout << "received " << buf << endl;
        }
}

