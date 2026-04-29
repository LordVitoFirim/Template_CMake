add_executable(app main.cpp)

target_link_libraries(app
    PRIVATE core
)

enable_project_warnings(app)
