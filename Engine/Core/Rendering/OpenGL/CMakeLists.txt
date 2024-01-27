cmake_minimum_required(VERSION 3.23)
project(OpenGL VERSION 0.1.0)


add_library(${PROJECT_NAME} OBJECT
"glad.c"
"Mesh.h" "Mesh.cpp"
"OpenGLRenderer.h" "OpenGLRenderer.cpp")
