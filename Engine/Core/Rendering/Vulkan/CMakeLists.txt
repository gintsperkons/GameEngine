cmake_minimum_required(VERSION 3.23)
project(Vulkan VERSION 0.1.0)


add_library(${PROJECT_NAME} OBJECT
"VulkanRenderer.h" "VulkanRenderer.cpp"
"VulkanValidation.h" "VulkanValidation.cpp")
