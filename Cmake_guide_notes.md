# Cmake guide

## Профиты CMake

- Описание сборки в одном месте (всё в нескольких `CMakeLists.txt`, разбросанных по проекту)
- Удобство сопровождения
- Сборка проекта любым поддерживаемым инструментом (`Ninja`, `Make`)
- Кроссплатформенность
- Кросс-компиляция (можно выбрать любой компилятор)

## Example 1

```sh
root@LAPTOP-5D6QTNQE:~/cmake_guide# cd example1/
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1# mkdir build
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1# cd build 
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1/build# cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake_guide/example1/build
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1/build# 
```

По итогу в директории build появятся сгенерированные из исходников файлы

При этом можно передать генератор через аргумент -G, сгенерировав проект под конкретную IDE. Или описать уникальный тулчейн для Cmake

```sh
Generators
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
* Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.
```

В помощь

```sh
cmake --help
```

Компилируем
```sh
root@LAPTOP-5D6QTNQE:~/cmake_guide# cd example1
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1# script termonal_out.txt
Script started, output log file is 'termonal_out.txt'.
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1# cd build
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1/build# cmake --build .
[ 50%] Building CXX object CMakeFiles/helloWorld.dir/main.cpp.o
[100%] Linking CXX executable helloWorld
[100%] Built target helloWorld
root@LAPTOP-5D6QTNQE:~/cmake_guide/example1/build# ./helloWorld 
Hello C++ World from VS Code and the C++ extension!
```

#R 

```
script terminal_out.txt
cat terminal_out.log | perl -pe 's/\e([^\[\]]|\[.*?[a-zA-Z]|\].*?\a)//g' | col -b > terminal_out.log
```

```cmake
add_executable(target src.cpp src2.cpp src2.h)
```
Скомпилировать файлы, как цель добавить бинарник/

Добавлять можно несколько исходных файлов, перечислять через запятую. Смысл добавления хедера в цель - в том, что cmake добавляет этот файл в дерево исходников.

```cmake
set_target_properties(target PROPERTIES prop1 prop2)
```

Добавляет к тргету некоторые свойства

Собирать 11 стандартам

Если 11 не работает выкинуть ошибку

## Структура генерируемых cmake файлов

`cmake_install.cmake` хз что делает, но мб нужно для компиляции - [дока](https://cmake.org/cmake/help/v3.13/command/install.html#command:install)

`CMakeCache.txt` - переменные окружения cmake на момент сборки

`Makefile` или налогичный инструкции для сборки проекта сгенерированные выбранным генератором постредством Cmake


## Example 3

```cmake
configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/conig.h)
```

Бери файл с шаблоном и выполняй инструкции из него

В conig.h.in Прописана команда на определение константы с мажорной версией проекта, которая задается в project(name VERSION Maj.Min.Pat)

```
target_include_directories(configure PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
```
добавляет к цели библиотеку

По сути добавляет путь до файла, подключаемого через #include в .cpp файле в список, по которым компилятор ищет эти самые инклуды.

```
include_directories(configure PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
```
добавляет библиотеку ко всем таргетам проекта

PRIVATE - PUBLIC - INTERFACE
Разные режимы прокидывания зависимостей между таргетами разных уровней

## Example 4

```cmake
add_subdirectory(src)
```
Иди в папку dir и ищи/выполняй CMakeLists.txt там

```cmake
add_library(lib STATIC lib.cpp lib.hpp)
```
Собирай библиотеку из исходников

```
target_link_libraries(main_app lib)
```

Линкуй к таргету либу

Cmake анализирует зависимости между таргетами и собирает подпроекты в нужном порядке.

## Example 5
```
find_package(lib CONFIG REQUIRED)
```
Ищет библиотеку в  дереве проекта и в стандартных путях
Ещё можно прокинуть путь через задание переменной (флаг -D) lib_DIR = PATH

```
target_link_libraries(main lib)
```

## Example 6
Пример для использования самописного модуля для поиска библиотек без инструкций для их сборки

скрипт Findlib.cmake

```cmake
find_path(RETURNED_PATH_VAR NAMES lib_to_find.hpp
HINTS $ENV{LIBDIR}
PATHS ${LIBROOT}
PATH_SUFFIXES dir_where_lib_root)
```
Поиск пути до файла

```cmake
find_library(RET_LIB_NAME NAMES  lib_to_find
HINTS $ENV{LIBDIR}
PATHS ${LIBROOT}
PATH_SUFFIXES lib
NO_DEFAULT_PATH)
```

## Example 7

```
option(OPTION_NAME "msg" OFF/ON)
```

Использовать в CMake

## Example 8

```
target_compile_feature(target Private feature1 feature2)
```
Можно указывать конкретные фичи компилятора для сборки проекта

starokurov cpp_open


