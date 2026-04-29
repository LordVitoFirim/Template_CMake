# Базовая шпаргалка для CMake

**Пример Структуры проекта**

```text
Template_CMake/
│
├── CMakeLists.txt
├── cmake/
│
├── include/
│   └── core/
│       └── math_utils.hpp
│
├── src/
│   ├── CMakeLists.txt
│   └── math_utils.cpp
│
├── app/
│   ├── CMakeLists.txt
│   └── main.cpp
│
├── tests/
│   ├── CMakeLists.txt
│   └── test_math.cpp
│
└── external/
```

## Что тут происходит

CMake нужен, чтобы не собирать проект руками длинной командой через компилятор.

Когда файл один, можно написать примерно так:

```bash
c++ main.cpp -o app
```

Но когда появляются `src`, `include`, `app`, `tests`, свои заголовки и несколько
`CMakeLists.txt`, руками это уже неудобно. Поэтому мы описываем структуру проекта
в CMake, а он готовит сборку сам.

## Основная идея

В проекте есть маленькая библиотека `core`.

Она состоит из:

- `include/core/math_utils.hpp` — объявление функции;
- `src/math_utils.cpp` — реализация функции.

Потом эту библиотеку используют:

- `app/main.cpp` — основная программа;
- `tests/test_math.cpp` — простая ручная проверка.

То есть логика лежит отдельно, а приложение и тесты просто подключают ее.

## Главный CMakeLists.txt

В корне лежит главный файл:

```text
CMakeLists.txt
```

В нем написано:

```cmake
cmake_minimum_required(VERSION 3.20)
```

Это значит: нужна версия CMake не ниже `3.20`.

Дальше идет описание проекта:

```cmake
project(Template_CMake
    VERSION 1.0
    DESCRIPTION "Basic C++ project template with CMake"
    LANGUAGES CXX
)
```

Тут задается имя проекта, версия, описание и язык C++.

Потом выбирается стандарт:

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

На пальцах:

- используем C++20;
- CMake должен включить именно этот стандарт;
- расширения компилятора отключаем.

## Подключение папок

В корневом файле есть:

```cmake
add_subdirectory(src)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
```

`add_subdirectory(src)` говорит CMake зайти в папку `src` и прочитать там свой
`CMakeLists.txt`.

`add_subdirectory(app)` делает то же самое для приложения.

`enable_testing()` включает тесты.

`add_subdirectory(tests)` подключает папку с тестом.

## Библиотека

В `src/CMakeLists.txt` создается библиотека:

```cmake
add_library(core)
```

Потом к ней добавляется файл:

```cmake
target_sources(core
    PRIVATE
        math_utils.cpp
)
```

`PRIVATE` значит, что `math_utils.cpp` нужен только самой библиотеке.

Дальше указывается папка с заголовками:

```cmake
target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
```

`PUBLIC` значит, что эту папку увидит не только `core`, но и те, кто подключает
`core`.

Например `app` сможет написать:

```cpp
#include "core/math_utils.hpp"
```

## Приложение

В `app/CMakeLists.txt` создается программа:

```cmake
add_executable(app main.cpp)
```

И она подключается к библиотеке:

```cmake
target_link_libraries(app
    PRIVATE core
)
```

То есть `app` использует код из `core`.

## Тест

В `tests/CMakeLists.txt` создается отдельная маленькая программа:

```cmake
add_executable(test_math test_math.cpp)
```

Она тоже подключает `core`:

```cmake
target_link_libraries(test_math
    PRIVATE core
)
```

И регистрируется как тест:

```cmake
add_test(NAME math_utils COMMAND test_math)
```

Сам тест максимально простой и ручной. Он вызывает функцию и возвращает `0`, если
все хорошо, или `1`, если результат неправильный.

## Как собрать

Сначала CMake нужно подготовить:

```bash
cmake -S . -B build
```

Здесь:

- `-S .` — исходники лежат в текущей папке;
- `-B build` — сборочные файлы положить в папку `build`.

Потом собираем:

```bash
cmake --build build
```

## Как запустить

Приложение:

```bash
./build/app/app
```

Тесты:

```bash
ctest --test-dir build
```

## Внешние зависимости

Пока внешних зависимостей нет.

В корневом `CMakeLists.txt` оставлены закомментированные примеры:

```cmake
#find_package(Threads REQUIRED)
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)
```

Если потом понадобятся `Threads` или `Eigen`, эти строки можно будет раскомментировать
и подключить зависимости к нужной библиотеке.
