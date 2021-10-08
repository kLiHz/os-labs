# 要求最低的 CMake 版本
cmake_minimum_required(VERSION 3.1)

# 项目名称
project(hello)

# 生成可执行程序的目标
add_executable(main hello.c functions.h functions.c)
