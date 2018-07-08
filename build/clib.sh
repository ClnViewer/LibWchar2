#!/bin/sh

    #cd ../
    pwd

    if [[ -f ../env.sh ]] ;
    then
        INFO=`../env.sh`
        echo "ENV info: ${INFO}"
    fi
    if [[ -z "${PREFIX}" ]] ;
    then
        PREFIX=/usr/local
    fi
    {
        autoreconf --install
        ./configure --prefix=${PREFIX}
        make clean check install -C .
    }
