cmake_minimum_required(VERSION 3.11)
project(MyProjectName)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory(src/app)
add_subdirectory(src/input)
add_subdirectory(src/game)
add_subdirectory(src/render)

add_executable(MyProjectName src/main.cpp)

target_sources(MyProjectName PRIVATE src/libs/glad/glad.c)

target_link_libraries(MyProjectName PRIVATE
    app
    game
    input
    render

    spdlog::spdlog
    OpenGL::GL
    glm::glm
    glfw
    assimp
)

target_include_directories(MyProjectName PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/
)

set_target_properties(MyProjectName PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_definitions(MyProjectName PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)
