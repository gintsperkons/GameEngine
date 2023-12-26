cmake_minimum_required(VERSION 3.8)
project(Window VERSION 0.1.0)




add_library(${PROJECT_NAME} OBJECT "Window.h" "Window.cpp" "WindowManager.h" "WindowManager.cpp")