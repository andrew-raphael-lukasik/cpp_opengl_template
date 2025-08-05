cmake_minimum_required(VERSION 3.10)
project(MyProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

add_executable(MyProjectName src/main.cpp)

target_link_libraries(MyProjectName spdlog::spdlog)

set_target_properties(MyProjectName PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_definitions(MyProjectName PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)
