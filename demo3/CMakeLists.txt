cmake_minimum_required(VERSION 2.8)
project(openglDemo1)


set(CMAKE_VERBOSE_MAKEFILE OFF)

# glfw和glew的头文件目录，这是我的路径，你可以换成你自己的
include_directories(/usr/local/include)
include_directories(./glad/include)
aux_source_directory("./glad/src" SRCS)
aux_source_directory("./" SRCS)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

# glew的库目录路径
link_directories(/usr/local/Cellar/glew/2.2.0_1/lib)
# glfw的库目录路径
link_directories(/usr/local/Cellar/glfw/3.3.2/lib)
add_executable(openglDemo1 ${SRCS} ${HDRS})

# 指定glew库
target_link_libraries(openglDemo1 GLEW)
# 指定glfw库
target_link_libraries(openglDemo1 GLFW)