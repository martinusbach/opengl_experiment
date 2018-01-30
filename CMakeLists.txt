cmake_minimum_required(VERSION 3.9)

project(opengl_experiment)

find_package(OpenGL REQUIRED)

add_subdirectory(ext_libs/glfw)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME}
                      OpenGL::GL
                      glfw)
