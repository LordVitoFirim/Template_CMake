add_library(core)

target_sources(core
    PRIVATE
        math_utils.cpp
)

target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(core
    PUBLIC cxx_std_20
)

enable_project_warnings(core)
