cmake_minimum_required(VERSION 4.1)
project(Simple++)

set(CMAKE_CXX_STANDARD 26)

add_executable(Simple++ simple++.cpp
        example.cpp)

#add_executable(SimplePlusPlus src/simple++.cpp)

if (MSVC)
    # Visual Studio编译器
    add_compile_options("/source-charset:utf-8")
else()
    # GCC/Clang编译器
    add_compile_options(-finput-charset=UTF-8)
endif()