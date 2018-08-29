
# make doc
make clean

    if [[ "${1}" == "" ]] ;
    then
        TXTCOMMIT="commit `date '+%Y-%m-%d'`"
    else
        TXTCOMMIT="${@} `date '+%Y-%m-%d'`"
    fi

chmod 664 src/*.c src/*.h test/*.c test/*.h include/*.h example/*.* winext/*.*
chown root:admin src/*.c src/*.h test/*.c test/*.h include/*.h example/*.* winext/*.*

wget --output-document=/tmp/master.atom https://github.com/ClnViewer/LibWchar2/commits/master.atom
build/doxymd -v -t githubfeed -f /tmp/master.atom -o docs

git add .
git commit -m "${TXTCOMMIT}"
git push -u origin master --tags
git status

exit

SUBMODULE

git submodule update --remote && git commit -
