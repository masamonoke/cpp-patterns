cmake_minimum_required(VERSION 3.23.2)

set(NAME patterns)
project(${NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
	builder.cpp
)
