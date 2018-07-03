#!/bin/sh

    if [[ ! -f ./configure.orig ]] ;
    then
        cp -f ./configure ./configure.orig
    fi

    autoreconf --install
    echo -e "#!/bin/sh\n\n./configure --prefix=/usr\nmake\nmake check\n\n" >build.sh
    chmod 0755 build.sh

