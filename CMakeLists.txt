cmake_minimum_required(VERSION 3.9)

project(opengl_experiment)

find_package(OpenGL REQUIRED)

add_subdirectory(ext_libs/glfw)

option(OPTION_BUILD_TESTS             "Build tests."                                           OFF)
option(OPTION_BUILD_GPU_TESTS         "Build tests that require an OpenGL context."            OFF)
option(OPTION_BUILD_TOOLS             "Build tools."                                           OFF)
add_subdirectory(ext_libs/glbinding)



add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME}
                      OpenGL::GL
                      glfw
                      glbinding::glbinding)
