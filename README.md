# Базовый шаблон CMake для C++

Учебный минимальный проект на C++20 с разделением на библиотеку, приложение и тесты.

## Структура проекта

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

## Сборка

```bash
cmake -S . -B build
cmake --build build
```

## Запуск приложения

```bash
./build/app/app
```

## Запуск тестов

```bash
ctest --test-dir build
```

## Где что находится

- `include/core/` — публичные заголовочные файлы библиотеки.
- `src/` — реализация библиотеки `core`.
- `app/` — пример исполняемого приложения.
- `tests/` — простые тесты, зарегистрированные в CTest.
- `cmake/` — вспомогательные CMake-модули проекта.

## Внешние зависимости

В корневом `CMakeLists.txt` оставлены закомментированные примеры `find_package` для будущих экспериментов. Сейчас проект не требует внешних библиотек.
