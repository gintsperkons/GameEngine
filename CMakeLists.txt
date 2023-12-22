# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameEngine")

# Add source to this project's executable.
add_executable (GameEngine 
"GameEngine/Engine/Core/Rendering/Vulkan/VulkanRenderer.cpp" 
"GameEngine/Engine/Core/Rendering/Vulkan/VulkanRenderer.h"
"GameEngine/Engine/Core/Window/WindowManager.cpp" 
"GameEngine/Engine/Core/Window/WindowManager.h"
 "GameEngine/Engine/Core/Window/Window.cpp" 
 "GameEngine/Engine/Core/Window/Window.h" 
 "GameEngine/Engine.cpp" 
 "GameEngine/Engine/Core/Rendering/Renderer.h" 
 "GameEngine/Engine/Core/Rendering/Renderer.cpp" 
 "GameEngine/Engine/Core/Rendering/Vulkan/VulkanValidation.h" 
 "GameEngine/Engine/Core/Rendering/Vulkan/VulkanValidation.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
