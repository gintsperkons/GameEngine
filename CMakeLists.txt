# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.23)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameEngine")



if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(ARCH "x86")
endif()

message("CMAKE_GENERATOR_PLATFORM is ${CMAKE_SIZEOF_VOID_P}")
message("CMAKE_GENERATOR_PLATFORM is ${ARCH}")

if(ARCH STREQUAL "x64")
include_directories("${CMAKE_SOURCE_DIR}/Libraries/x64/include" "C:/VulkanSDK/1.3.261.1/Include")
link_directories("${CMAKE_SOURCE_DIR}/Libraries/x64/lib" "C:/VulkanSDK/1.3.261.1/Lib")
elseif(ARCH STREQUAL "x86")
include_directories("${CMAKE_SOURCE_DIR}/Libraries/x86/include" "C:/VulkanSDK/1.3.261.1/Include")
link_directories("${CMAKE_SOURCE_DIR}/Libraries/x86/lib" "C:/VulkanSDK/1.3.261.1/Lib32")
endif()



add_subdirectory("Engine")



# Add source to this project's executable.
add_library (${PROJECT_NAME}
 "Engine.h" 
 "Engine.cpp")
 target_link_libraries(${PROJECT_NAME} Core vulkan-1 glfw3)
 
  if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
 endif()
 



 add_executable (${PROJECT_NAME}StandAlone
 "Engine.h" 
 "Engine.cpp"
 "main.cpp")


 target_link_libraries(${PROJECT_NAME}StandAlone Core vulkan-1 glfw3)
 if (CMAKE_VERSION VERSION_GREATER 3.12)
 set_property(TARGET ${PROJECT_NAME}StandAlone PROPERTY CXX_STANDARD 20)
endif()




# TODO: Add tests and install targets if needed.
