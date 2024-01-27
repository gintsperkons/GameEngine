cmake_minimum_required(VERSION 3.23)
project(Rendering VERSION 0.1.0)


add_subdirectory(Vulkan)
add_subdirectory(OpenGL)
add_library(${PROJECT_NAME} OBJECT
"Renderer.h" "Renderer.cpp"
$<TARGET_OBJECTS:Vulkan>
$<TARGET_OBJECTS:OpenGL>)