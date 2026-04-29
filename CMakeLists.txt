cmake_minimum_required(VERSION 3.20)

project(Template_CMake
    VERSION 1.0
    DESCRIPTION "Basic C++ project template with CMake"
    LANGUAGES CXX
)

# -------------------------------
# Общие настройки
# -------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------------
# Поиск внешних пакетов
# -------------------------------

#find_package(Threads REQUIRED)
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# -------------------------------
# Подпроекты
# -------------------------------

add_subdirectory(src)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
