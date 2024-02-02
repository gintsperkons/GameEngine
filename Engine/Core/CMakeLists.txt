cmake_minimum_required(VERSION 3.23)
project(Core VERSION 0.1.0)

add_subdirectory(FileHandling)
add_subdirectory(Window)
add_subdirectory(Rendering)
add_subdirectory(InputHandling)

add_library(${PROJECT_NAME}
$<TARGET_OBJECTS:FileHandling>
$<TARGET_OBJECTS:Rendering>
$<TARGET_OBJECTS:Vulkan>
$<TARGET_OBJECTS:OpenGL>
$<TARGET_OBJECTS:Window>
$<TARGET_OBJECTS:InputHandling>
)



target_link_libraries(${PROJECT_NAME} vulkan-1 glfw3)
