# Базовая шпаргалка для CMake

Это учебный шаблон C++ проекта на CMake. Его цель — показать, как постепенно собрать
небольшой проект из библиотеки, приложения и тестов.

Проект не использует внешние зависимости. В `CMakeLists.txt` оставлены закомментированные
примеры `find_package`, чтобы позже было проще вспомнить, куда добавлять сторонние
библиотеки.

## 1. Структура проекта

Сначала была сделана такая структура:

```text
Template_CMake/
│
├── CMakeLists.txt
├── cmake/
│   └── CompilerWarnings.cmake
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
├── external/
│
└── README.md
```

Что здесь за что отвечает:

- `CMakeLists.txt` в корне — главный файл сборки всего проекта.
- `include/` — публичные заголовочные файлы библиотеки.
- `src/` — реализация библиотеки.
- `app/` — исполняемая программа, которая использует библиотеку.
- `tests/` — тестовые программы.
- `cmake/` — дополнительные CMake-файлы, чтобы не перегружать корневой файл.
- `external/` — место под сторонние зависимости, если они появятся позже.

## 2. Корневой `CMakeLists.txt`

В корне проекта задается минимальная версия CMake:

```cmake
cmake_minimum_required(VERSION 3.20)
```

Потом описывается сам проект:

```cmake
project(Template_CMake
    VERSION 1.0
    DESCRIPTION "Basic C++ project template with CMake"
    LANGUAGES CXX
)
```

Здесь:

- `Template_CMake` — имя проекта.
- `VERSION 1.0` — версия проекта.
- `DESCRIPTION` — короткое описание.
- `LANGUAGES CXX` — проект использует C++.

Дальше задается стандарт C++:

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

Это значит:

- используется C++20;
- CMake обязан включить именно этот стандарт;
- расширения компилятора вроде `gnu++20` отключены, нужен более переносимый режим.

Дополнительный файл с предупреждениями подключается так:

```cmake
include(cmake/CompilerWarnings.cmake)
```

Внешние зависимости пока не используются, но место для них оставлено:

```cmake
#find_package(Threads REQUIRED)
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)
```

Подпроекты подключаются через `add_subdirectory`:

```cmake
add_subdirectory(src)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
```

Порядок здесь важен: сначала собирается библиотека `core`, потом приложение и тесты,
которые эту библиотеку используют.

## 3. Библиотека `core`

В папке `src/` создается библиотека:

```cmake
add_library(core)
```

К ней добавляется файл реализации:

```cmake
target_sources(core
    PRIVATE
        math_utils.cpp
)
```

`PRIVATE` значит, что `math_utils.cpp` нужен только для сборки самой библиотеки.
Пользователям библиотеки этот `.cpp` файл напрямую не нужен.

Публичные заголовочные файлы подключаются так:

```cmake
target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
```

`PUBLIC` здесь важен: если приложение линкуется с `core`, оно автоматически узнает,
где искать заголовки из `include/`.

Стандарт C++ также закрепляется на уровне цели:

```cmake
target_compile_features(core
    PUBLIC cxx_std_20
)
```

И включаются предупреждения компилятора:

```cmake
enable_project_warnings(core)
```

## 4. Заголовочный файл

Публичный интерфейс библиотеки лежит в `include/core/math_utils.hpp`:

```cpp
#pragma once

namespace core
{
    int add(int a, int b);
}
```

Здесь объявляется функция `add`, но не описывается ее реализация.
Так другие части проекта знают, что такая функция существует.

## 5. Реализация библиотеки

Реализация находится в `src/math_utils.cpp`:

```cpp
#include "core/math_utils.hpp"

namespace core
{
    int add(int a, int b)
    {
        return a + b;
    }
}
```

Файл подключает заголовок и описывает, что именно делает функция.

## 6. Приложение

В папке `app/` создается исполняемый файл:

```cmake
add_executable(app main.cpp)
```

Потом приложение связывается с библиотекой:

```cmake
target_link_libraries(app
    PRIVATE core
)
```

`PRIVATE` значит, что библиотека `core` нужна только самому приложению.

В `app/main.cpp` библиотека используется так:

```cpp
#include <iostream>

#include "core/math_utils.hpp"

int main()
{
    std::cout << "2 + 3 = "
              << core::add(2, 3)
              << '\n';

    return 0;
}
```

## 7. Тесты

Тест собирается как отдельная программа:

```cmake
add_executable(test_math test_math.cpp)
```

Он тоже подключается к библиотеке:

```cmake
target_link_libraries(test_math
    PRIVATE core
)
```

Чтобы CMake знал, что это именно тест, он регистрируется через CTest:

```cmake
add_test(NAME math_utils COMMAND test_math)
```

В самом тесте используются обычные `assert`:

```cpp
#include <cassert>

#include "core/math_utils.hpp"

int main()
{
    assert(core::add(2, 2) == 4);
    assert(core::add(-2, 2) == 0);
    assert(core::add(0, 0) == 0);
    assert(core::add(-2, -3) == -5);

    return 0;
}
```

Для маленького учебного проекта этого достаточно. Позже можно заменить `assert`
на полноценный тестовый фреймворк, например Catch2 или GoogleTest.

## 8. Предупреждения компилятора

Файл `cmake/CompilerWarnings.cmake` нужен, чтобы включать предупреждения одинаково
для разных целей:

```cmake
function(enable_project_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()
```

Для Visual Studio используется `/W4`, а для GCC и Clang:

- `-Wall`
- `-Wextra`
- `-Wpedantic`

Это помогает раньше замечать подозрительный код.

## 9. `.gitignore`

В проект добавлен `.gitignore`, чтобы не отправлять в Git временные файлы сборки:

```gitignore
build/
cmake-build-*/
CMakeCache.txt
CMakeFiles/
```

Смысл простой: исходный код хранится в Git, а результаты сборки можно получить заново.

## 10. Сборка проекта

Создать папку сборки и сконфигурировать проект:

```bash
cmake -S . -B build
```

Здесь:

- `-S .` — исходники лежат в текущей папке;
- `-B build` — файлы сборки нужно положить в папку `build`.

Собрать проект:

```bash
cmake --build build
```

## 11. Запуск приложения

```bash
./build/app/app
```

Ожидаемый вывод:

```text
2 + 3 = 5
```

## 12. Запуск тестов

```bash
ctest --test-dir build
```

CTest найдет зарегистрированный тест `math_utils` и запустит исполняемый файл
`test_math`.

## 13. Что можно добавить дальше

Этот шаблон можно расширять постепенно:

- добавить внешнюю библиотеку через `find_package`;
- заменить `assert` на Catch2 или GoogleTest;
- добавить GitHub Actions для автоматической сборки;
- добавить установку проекта через `install`;
- добавить больше файлов в библиотеку `core`.
