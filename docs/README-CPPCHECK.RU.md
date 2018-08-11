[![Git HOME](https://img.shields.io/badge/Home-Git-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Web HOME](https://img.shields.io/badge/Home-Web-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README.RU.md)
[![Documentation](https://img.shields.io/badge/Documentation-DOC-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)
[![License MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/LICENSE)
[![Build Travis](https://travis-ci.com/ClnViewer/LibWchar2.svg)](https://travis-ci.com/ClnViewer/LibWchar2)
[![Build Appveyor](https://ci.appveyor.com/api/projects/status/5s47u3irthu3icqo?svg=true)](https://ci.appveyor.com/project/ClnViewer/libwchar2)
[![Job Status](https://inspecode.rocro.com/badges/github.com/ClnViewer/LibWchar2/status?token=EjhrEOus5kCYzf9OVjBAPrjGFe23VmAQertYJc6gSDM)](https://inspecode.rocro.com/jobs/github.com/ClnViewer/LibWchar2/latest?completed=true)

## Анализ кода - cppcheck

Проверяя собственный код программами анализа вы делаете его надежнее.
Библиотека `LibWchar2` имеет дополнительные файлы настроек для анализатора кода [cppcheck](https://ru.wikipedia.org/wiki/Cppcheck).

Вы можете использовать следующую команду для анализа вашего исходного кода с использованием библиотеки `LibWchar2` для `*nix` платформ:

    cppcheck --quiet --enable=all --language=c --std=c99 --platform=unix32
     --inconclusive --report-progress --force --inline-suppr
     --check-library --library=libchar2.cfg
     -D__SIZEOF_WCHAR_T__=2 -D__GNUC__ -U_WIN32 -U__CYGWIN__ -U__APPLE__
     -U__WIN32__ -U_Windows -U_WIN64 -U__WIN64__ -U__CYGWIN__ 
     -U__MINGW32__ -U__MINGW64__ -U_MSC_VER -UBUILD_MSVC -UBUILD_MINGW
     -UBUILD_MINGW32 -UBUILD_MINGW64 -UOS_WIN_FOPEN_MIXED_CHAR
     -UWS_FS_REDEFINE -UWS_FS_UTF8  -I.
     --output-file=cppcheck.xml --xml --xml-version=2
     <path to you source code directory>

> Время работы `cppcheck` с этими опциями может занимать довольно продолжительное время. Для контроля состояния включена опция `--report-progress`.

Полное описание всех параметров можно найти через `man cppcheck` или выполнив команду `cppcheck --help`.

- [Репозиторий `cppcheck`](http://cppcheck.sourceforge.net/)
- [XML файл описания функций `LibWchar2`](https://github.com/ClnViewer/LibWchar2/blob/master/docs/cppcheck/libwchar2.cfg)
- [Пример проекта cppcheck с настройками для `LibWchar2`](https://github.com/ClnViewer/LibWchar2/blob/master/docs/cppcheck/libwchar2.cppcheck)

