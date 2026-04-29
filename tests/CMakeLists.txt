add_executable(test_math test_math.cpp)

target_link_libraries(test_math
    PRIVATE core
)

enable_project_warnings(test_math)

add_test(NAME math_utils COMMAND test_math)
