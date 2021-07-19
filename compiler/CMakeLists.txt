cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE Release)
project(compiler
	VERSION 1.0.0
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options("-O2")
add_compile_options("-stdlib=libstdc++")

add_executable(${PROJECT_NAME} compiler.cpp)
