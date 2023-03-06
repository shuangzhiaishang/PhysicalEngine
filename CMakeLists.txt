cmake_minimum_required(VERSION 3.24)
project(PhysicalEngine)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(PhysicalEngine main.cpp src/glad.c)

target_link_libraries(PhysicalEngine ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
