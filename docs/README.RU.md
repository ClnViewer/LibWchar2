
[![Git HOME](https://img.shields.io/badge/Home-Git-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Readme ENG](https://img.shields.io/badge/Readme-ENG-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README.md)
[![Documentation](https://img.shields.io/badge/Documentation-DOC-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)
[![License MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/LICENSE)
[![Build Travis](https://travis-ci.com/ClnViewer/LibWchar2.svg)](https://travis-ci.com/ClnViewer/LibWchar2)
[![Build Appveyor](https://ci.appveyor.com/api/projects/status/5s47u3irthu3icqo?svg=true)](https://ci.appveyor.com/project/ClnViewer/libwchar2)
[![Job Status](https://inspecode.rocro.com/badges/github.com/ClnViewer/LibWchar2/status?token=EjhrEOus5kCYzf9OVjBAPrjGFe23VmAQertYJc6gSDM)](https://inspecode.rocro.com/jobs/github.com/ClnViewer/LibWchar2/latest?completed=true)


[![Repo size](https://img.shields.io/github/repo-size/ClnViewer/LibWchar2.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Code size](https://img.shields.io/github/languages/code-size/ClnViewer/LibWchar2.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)

# LibWchar2
----------
 
Библиотека обертка для совместимости с проектами написанными для `Windows API`, где `wchar_t size` == `2 байта` на ***nix** платформах.  
Заменяет `libc`, `glibc` функции с использованием типа `wchar_t`.

### Для чего это:
----------

При портировании программного обеспечения использующего внутренний тип `wchar_t` с платформы `Windows API` требуется для нормальной работы размер типа `wchar_t` равный двум байтам (16 bit). В *nix системах, по умолчанию размер типа `wchar_t` соответствует 4 байтам (32 bit).  

Но, есть возможность собрать программу с типом `wchar_t` равному 2 байтам. Эта возможность есть при использовании компиляторов `GCC` или `clang`.  
Чтобы обеспечить работоспособность этих собранных программ, необходимо что бы `libc` и как следствие все остальные библиотеки были собраны с поддержкой `wchar_t` равной 2 байтам. Это условие как правило невыполнимо..

### Ключи компиляторов:

Использование ключей компиляции для создания вашей программы с помощью этой библиотеки.
Включить сборку с типом `wchar_t` равному 2 байтам.


CC | key
--- | ---
`GCC` | `-fshort-wchar`
`clang` | `-fwchar-type=short` `-fno-signed-wchar`


### Особенности библиотеки:

- Библиотека не имеет зависимостей.  
- Тестировалась под `Linux`, на других *nix платформах поведение не гарантированно.  
- Не предусмотрена для сборки в среде `Windows API`, по причине отсутствия необходимости в ней на этой платформе.  
- В библиотеку включены как основные функции из библиотек `libc`, `glibc` по работе с типом `wchar_t`, так и сторонние наработки и прочие расширения.
- Доступна дополнительная [библиотека расширений](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-WINAPIEXT.RU.md) на базе `LibWchar2` для `Windows API` платформ.
- В наличии [файлы настроек](https://github.com/ClnViewer/LibWchar2/blob/master/docs/cppcheck/libwchar2.cfg) анализатора кода [`cppcheck`](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-CPPCHECK.RU.md) для тестирования программ использующих эту библиотеку.
- **Внимание**, не все [функции](https://github.com/ClnViewer/LibWchar2/blob/master/docs/WCHAR2-LIST-MAP.md) протестированы должным образом, если вы поможете с тестами и поиском несоответствий это сделает библиотеку лучше и надежнее.



- Список функций:      [документация](https://github.com/ClnViewer/LibWchar2/blob/master/docs/WCHAR2-LIST-MAP.md)

### Стандарт ISO/IEC 9899:2011 + stddef.h

Краткий вольный перевод сути изложенного в стандартах касаемо `wchar_t` и сопутствующих типов.

1. `wchar_t` который представляет собой целочисленный тип, диапазон значений которого может представлять собой различные коды для всех членов самого большого расширенного набора символов, указанного среди поддерживаемых локальных кодировок. Нулевой символ должен иметь нулевое значение кода. Каждый член базового набора символов должен иметь значение кода, равное его значению при использовании в качестве одиночного символа в целочисленной символьной константе, если реализация не определяет `STDC_MB_MIGHT_NEQ_WC`.

2. `wint_t` - который является целочисленным типом, неизменным по умолчанию, поскольку он может содержать любое значение, соответствующее членам расширенного набора символов, а также по меньшей мере одно значение, которое не соответствует ни одному члену расширенного набора символами.

3. `mbstate_t` - который является полным типом объекта, отличным от типа массива, который может содержать информацию состояния преобразования, необходимую для преобразования между последовательностями много байтовых символов и широкими символами.

### Пояснения разработчиков реализации функционала `wchar_t`

- Использую флаги компиляторов для обеспечения размера 2 байта для типа `wchar_t`, вы делаете это на своей ответственности. Используя это вы теряете возможность работоспособного взаимодействия с внешними библиотеками собранными без этих флагов. Стандартные библиотеки по умолчанию собраны с поддержкой типа `wchar_t` размером 32 бита для *nix систем.    
- Ситуации, в которых `wchar_t` имеет размера 2 байта, очень ограничены и, вероятно, относятся главным образом к автономным реализациям совместно с изменением кода всех библиотек использующих широкие символы.
- Некоторые *nix системы определяют `wchar_t` как 16-разрядный тип и тем самым строго следуют `Unicode`. Это определение прекрасно соответствует стандарту, но также означает, что для представления всех символов из `Unicode` и `ISO 10646` необходимо использовать суррогатные символы `UTF-16`, что на самом деле является кодировкой с несколькими широкоформатными символами. Но, обращение к широкому символу кодированию противоречит цели этого `wchar_t` типа.
- Не рекомендуется смешивать функции ввода/вывода широкого символа и массива байтов. Функции `printf/fprintf/putchar` - это вывода байтов, независимо от того, включает ли она форматы для широких символов в том же потоке. Функции `wprintf/vfwprintf/putwchar` напротив, предназначены для вывода широких символов, хотя в состоянии печатать и байтовые массивы.
- Ещё одна проблема `glibc`, `libc` заключается в разности типов переменных `wchar_t` и `wint_t`, `unsigned` и `signed` соответственно. Часть функций `glibc`, `libc` связанных с широкими символами принимают в качестве входных параметров тип `wint_t` что составляет определённые проблемы связанные с предупреждениями компилятора о разных типах подписей переменной. 
- Интересная историческая заметка [wchar_t: Небезопасно в любом размере](http://losingfight.com/blog/2006/07/28/wchar_t-unsafe-at-any-size/) от [Энди Финнелл](http://losingfight.com/blog/contact/)  
 

### Идеологические изменения:

> Библиотека **LibWchar2** снимает эти ограничения, и не требует пере сборки всех библиотек, при этом позволяя создавать приложения с двух байтным типом `wchar_t`.
        
> В библиотеке **LibWchar2** переменная с типом `mbstate_t` игнорируется и даже если задать эту переменную она не будет использована, тем самым убираются промежуточные состояния которые запоминаются и мешают взаимному выполнению `ввода/вывода` в одном потоке. 
> 
> Так же в функциях `ввода/вывода` удалена работа с ориентацией потока, ее необходимость - вопрос довольно спорный, но это тоже влияет на стабильность работы функций связанных с операциями `ввода/вывода`.
        
> В библиотеке **LibWchar2** проблема типов решена, все функции так или иначе работающие с широкими символами приведены к единому типу `wchar_t`.
    
### Сборка и Инсталляция:

Сборка под *nix платформы выполняется типичным для них способом, с помощью пакета [autotools](https://ru.wikipedia.org/wiki/Autotools "Autotools")

Запустите инсталляционный скрипт `configure` из корневой директории проекта.  
Кроме типовых ключей, скрипт понимает следующие опции:

* `--enable-werror`  - собирать библиотеку и тесты с ключом `-Werror`.
* `--enable-devel`    - собирать библиотеку и тесты с ключом `-Wextra`.
* `--disable-testlib` - не собирать тесты библиотеки.
* `--enable-debug`    - собрать библиотеку с отладочной информацией.

Далее необходимо собрать библиотеку, стандартными командами:

    ./configure --prefix=/usr
    make
    make check
    make install
    
Так же, можно воспользоваться скриптом `build.sh` из корневой директории, это позволит не вводить эти команды руками.

Если есть необходимость пересобрать сам скрипт `./configure`, выполните:

    ./autogen.sh


### Расширения библиотеки для Windows API
 
- Установка [библиотеки расширений `LibWchar2`](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-WINAPIEXT.RU.md) для `Windows API`.

### API

- Файл заголовков:     [wchar2.h](https://github.com/ClnViewer/LibWchar2/blob/master/include/wchar2.h)  
- OnLine документация: [libwchar2](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)  
- Список функций:      [документация](https://github.com/ClnViewer/LibWchar2/blob/master/docs/WCHAR2-LIST-MAP.md), [man](https://github.com/ClnViewer/LibWchar2/blob/master/docs/wchar2.3)  
- Текущее состояние: [Журнал изменений](https://github.com/ClnViewer/LibWchar2/blob/master/docs/CHANGELOG-master.md)

Для использования библиотеки в проекте подключите заголовок последним, после всех системных заголовков, при этом `wchar.h` и `wctype.h` можно не указывать, они уже включены.

    #include <stdio.h>
    #include <string.h>
    #include ...
    #include <wchar2.h>

Подключение самой библиотеки производиться стандартным образом:


`Makefile:`

    CFLAGS = -I. -fshort-wchar /* GCC */
    CFLAGS = -I. -fwchar-type=short -fno-signed-wchar /* clang */
    LDFLAGS = -L. -lwchar2

Определенно удобно может быть переопределение стандартных функций работающих с файловой системой, таких как: `mkdir`, `remove`, `rename`, `stat`, `basename`, `dirname`, `access`, `fopen`, `fputc`, `fputs`.

Для этого, до включения заголовка, определите следующие определения:
 
    #define WS_FS_REDEFINE 1
    #include <wchar2.h>

или, если есть необходимость использовать только `UTF-8` кодировку:

    #define WS_FS_REDEFINE 1
    #define WS_FS_UTF8 1
    #include <wchar2.h>

**Внимание**, отдельно ключ `WS_FS_UTF8` работать не будет.

Пример [использования](https://github.com/ClnViewer/LibWchar2/blob/master/example/fs-redifine.c)

В режиме определения `WS_FS_UTF8` функции `mkdir`, `remove`, `rename`, `stat`, `fopen`, `access` воспринимают входные данные только в формате строки `wchar_t`, в другом случае входные данные могут быть в форматах приведенных в таблице, определение в этом случае производиться автоматически.

Подробнее смотри: [wchar2.h](https://github.com/ClnViewer/LibWchar2/blob/f884fcf232e483759b827a53cc2333332d2cda27/include/wchar2.h#L342) macro `__wchar_type_id(..)`

Тип | const | array | const array
--- | --- | --- | --- |
char* | const char* | char[] | const char[]
wchar_t* | const wchar_t* | wchar_t[] | const wchar_t[]
string_ws* | const string_ws* ||


### Тесты:

- Проверяя свой код программами анализа вы делаете его надежнее, если вы используете [cppcheck](https://ru.wikipedia.org/wiki/Cppcheck) возможно вам будет полезны [файлы конфигурации](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-CPPCHECK.RU.md) с описанием функций библиотеки для анализатора `cppcheck`.
- Если у вас есть время и желание или возможность помочь сделать библиотеку лучше, вы можете принять участие в написании тестов для функций библиотеки. Тем самым вы примите участие в тестировании.

### Проекты адаптированные к библиотеке

- [libexpat](https://github.com/libexpat/libexpat) - Быстрый потоковый XML-парсер, написан на `C`. Автор: [Expat development team](https://libexpat.github.io/)  
- [tinydir](https://github.com/ClnViewer/tinydir/tree/libwchar2support) - [patch v.1.2.3](https://github.com/ClnViewer/tinydir/blob/master/tinydir-release-1.2.3.diff) - Легкий, портативный и простой в использовании просмотрщик директорий и файлов. Автор: [cxong](https://github.com/cxong)


### Используемые материалы:

В проекте использован переработанный код авторов:

- [Tim J. Robbins](https://packetstormsecurity.com/files/author/1683/)
- [Nexenta Systems, Inc](https://en.wikipedia.org/wiki/Nexenta_Systems)
- [Fredrik Fornwall/Rich Felker](https://github.com/fornwall)
- [Angel Ortega](http://triptico.com/)
- [Mayu Laierlence](https://github.com/minacle)
- [Nodir Temirkhodjaev](https://github.com/tnodir)

за что им отдельное спасибо :)

## License

_MIT_
