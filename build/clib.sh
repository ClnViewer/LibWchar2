#!/bin/sh

    #cd ../
    pwd

    if [ -z "${PREFIX}" ] ;
    then
        PREFIX=/usr/local
    fi
    {
        autoreconf --install
        ./configure --prefix=${PREFIX}
        make clean check install -C .
    }
