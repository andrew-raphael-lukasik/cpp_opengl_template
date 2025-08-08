add_library(render STATIC
    render.cpp
)

target_include_directories(render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(render PUBLIC app)

# copy shaders next to executable:
set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_TARGET_DIR ${CMAKE_BINARY_DIR}/bin/shaders)
message("copying shaders \n\tfrom: ${SHADER_SOURCE_DIR}\n\tto: ${SHADER_TARGET_DIR}")
add_custom_command(
    OUTPUT ${SHADER_TARGET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_SOURCE_DIR} ${SHADER_TARGET_DIR}
)
add_custom_target(copy_shaders ALL DEPENDS ${SHADER_TARGET_DIR})
message("shaders copied")
