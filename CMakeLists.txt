cmake_minimum_required(VERSION 3.13)
project(Raytracing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

include_directories(include)
link_directories(libs)

add_executable(Raytracing src/main.cpp src/Viewport.cpp src/Viewport.h src/Camera.cpp src/Camera.h src/Light.cpp src/Light.h)

target_link_libraries(Raytracing GLEW glfw3 -m64)