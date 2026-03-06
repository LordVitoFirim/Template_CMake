# Базовая шпаргалка для CMake

## Пример Структуры проекта

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
## Основные команды

- **add_library**
- **target_sources**
- **add_executable**
- **target_include_directories**
- **target_link_libraries**
- **target_compile_features**
- **add_subdirectory**
- **find_package**




