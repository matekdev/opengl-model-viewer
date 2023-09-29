cmake_minimum_required(VERSION 3.16)

project(opengl-model-viewer)

add_link_options(-static -static-libgcc -static-libstdc++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw-3.3.8)
add_subdirectory(libs/glad)
add_subdirectory(libs/imgui)
add_subdirectory(libs/glm)
add_subdirectory(libs/stb)

option(ASSIMP_BUILD_ASSIMP_VIEW OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
option(BUILD_SHARED_LIBS OFF)
add_subdirectory(libs/assimp)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad assimp stb imgui)

add_custom_target(copy_models
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/models"
        "${CMAKE_BINARY_DIR}/models"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "${CMAKE_BINARY_DIR}/Debug/shaders"
    COMMENT "Copying models folder to the build directory"
)

add_dependencies("${CMAKE_PROJECT_NAME}" copy_models)

add_custom_target(copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "${CMAKE_BINARY_DIR}/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/models"
        "${CMAKE_BINARY_DIR}/Debug/models"
    COMMENT "Copying shaders folder to the build directory"
)

add_dependencies("${CMAKE_PROJECT_NAME}" copy_shaders)