cmake_minimum_required(VERSION 3.11)
project(MyProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(glm REQUIRED)

add_executable(MyProjectName src/main.cpp)

target_link_libraries(MyProjectName spdlog::spdlog)
target_link_libraries(MyProjectName OpenGL::GL)
target_link_libraries(MyProjectName glfw)
target_link_libraries(MyProjectName glm)

set_target_properties(MyProjectName PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_definitions(MyProjectName PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)
