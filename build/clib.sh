#!/bin/sh

    cd ../

    if [ -z "${PREFIX}" ] ;
    then
        PREFIX=/usr/local
    fi
    {
        autoreconf --install
        ./configure --prefix=${PREFIX}
        make clean check install -C .
    }
