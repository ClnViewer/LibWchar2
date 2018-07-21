
[![Git HOME](https://img.shields.io/badge/Home-Git-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Web HOME](https://img.shields.io/badge/Home-Web-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/README.RU.md)
[![Documentation](https://img.shields.io/badge/Documentation-DOC-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)
[![License MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/LICENSE)
[![Build Travis](https://travis-ci.com/ClnViewer/LibWchar2.svg)](https://travis-ci.com/ClnViewer/LibWchar2)
[![Build Appveyor](https://ci.appveyor.com/api/projects/status/5s47u3irthu3icqo?svg=true)](https://ci.appveyor.com/project/ClnViewer/libwchar2)

# LibWchar2 - для Windows API
----------
 
Расширение включает в себя набор функций библиотеки не входящих в стандартный состав `Windows API`.  

Для обратной совместимости с `*nix` версией библиотеки,нестандартные функции вынесены в отдельную сборку, которая позволяет использовать эти функции в приложениях собираемые на платформе `Windows`.

### Список функций библиотеки расширений

Со списком функций вошедшими в библиотеку расширений `LibWchar2` можно ознакомиться в файле заголовков [`wchar2ext.h`](https://github.com/ClnViewer/LibWchar2/blob/master/include/wchar2ext.h).  
Подробнее функции описаны в [документации](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html).  
Текущий результаты тестовых сборок библиотеки расширений `LibWchar2` на [appveyor.com](https://ci.appveyor.com/project/ClnViewer/libwchar2)

### Установка библиотеки расширений

Сборка библиотеки расширений `libwchar2` рассчитана на среду компиляции `MSVC`/`MSVS`. Подготовка к сборке происходит с помощью сценария `cmake`.

Последовательность шагов для сборки библиотеки расширений если ваша версия `Visual Studio` или `Visual C++` с помощью внешней утилиты `cmake`:

#### Выполнение сценария `cmake` для командной строки 

- перейдите в директорию `winext/build` в репозитории.
- выполните команду `cmake` с ключом `-G`, где параметром ключа является [версия](https://cmake.org/cmake/help/v3.4/manual/cmake-generators.7.html#visual-studio-generators) `Visual Studio` или `Visual C++`:

        cd winext/build
        cmake -G"Visual Studio 14"  .. 
        cmake --build . --target "ALL_BUILD" --config "Release"

- выходные файлы библиотеки после успешной сборки и инсталляции должны находиться в директории `winext/lib`.

Так же вы можете выбрать в `Visual Studio` проект `winext/build/libwchar2ext.sln` и собрать его стандартным образом.


#### Выполнение сценария `cmake` для `CMake GUI`

- запускаем `CMake GUI`
- указываем пути:
 - `Where is the source code` - полный путь до папки `winext` в репозитории.
 - `Where to build the binaries` - полный путь до папки `winext/build` в репозитории, туда будут генерироваться файлы проекта.
- нажимаем кнопку `Configure` и выбираем версию `Visual Studio`, в случае ошибки нажимаем еще раз :)
- нажимаем кнопку `Generate`.
- нажимаем кнопку `Open Project`, поддерживаться с версии `CMake GUI` `>=` `3.12`.
- в `Visual Studio`, выбираем тип сборки `Release` или `Debug`.
- нажимаем `F7`, компилируем проект.
- выходные файлы библиотеки после успешной сборки и инсталляции должны находиться в директории `winext/lib`

### Тесты функций библиотеки расширений

С библиотекой расширений `LibWchar2`  прилагается небольшая программа для теста функций вошедшими в библиотеку.  

В проект `Visual Studio` она в добавляется автоматически, если вы после сборки из командной строки хотите протестировать результат, выполните следующий сценарий:

    cd winext/build
    ctest --verbose -C "Debug"

С исходным кодом теста можно ознакомиться в файле [`test/check_wchar2_MSVC.c`](https://github.com/ClnViewer/LibWchar2/blob/master/test/check_wchar2_MSVC.c).

## License

_MIT_

