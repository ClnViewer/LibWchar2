#!/bin/bash

function create_test() {
    tag=$1
    tag=${tag%.*}

    if [[ "${tag}" == "wchar_util" || "${tag}" == "wchar_utf8" || "${tag}" == "libwchar" ]] ;
    then
        return
    fi
    if [[ -f "test_${tag}.c" ]] ;
    then
        return
    fi
    echo -e "#include \"test_${tag}.c\"" >>check_wchar2_include.c
    echo -e "\ttcase_add_test(t, test_${tag});" >>check_wchar2_suite.c
    echo -e "START_TEST(test_${tag})\n{\n\tck_assert_msg((&${tag} == &_${tag}), 0, \"${tag} NO equals! libc used!\");\n}\nEND_TEST" >"test_${tag}.c"
}

    for i in `dir -1 ../src/*.c`
    do
        create_test `basename ${i}`
    done
