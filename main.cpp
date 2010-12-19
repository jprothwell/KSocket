/*
 *  main.cpp
 *  ksocket
 *
 *  Created by Kewei He on 12/14/10.
 *  Copyright 2010 Northeastern University. All rights reserved.
 *
 */

#include "kserversocketfactory.h"
#include "kunixsocketadapter.h"
#include <iostream>
using namespace std;

int main()
{
//    KServerSocketAdapter* server = 
//        KServerSocketFactory::getSocketAdapter();
    
    const int buflen = 512;
    byte buf[buflen];
    strcpy(buf, "hello, world");
    
//    if (server->accept()) 
//        while (1) {
//            server->send(buf, strlen(buf) + 1);
//            if (server->receive(buf, buflen))
//                cout << "received " << buf << endl;
//        }
    
    KUnixSocketAdapter socket;
    socket.connect("10.0.1.7", 22222);
    while (1) {
        if (socket.receive(buf, buflen))
            cout << "received " << buf << endl;
        gets(buf);
        socket.send(buf, strlen(buf) + 1);
    }
}

