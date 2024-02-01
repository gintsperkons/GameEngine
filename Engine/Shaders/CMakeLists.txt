#Vulkan Shader Compilation
if(ARCH STREQUAL "x64")
set(GLSLC "C:/VulkanSDK/1.3.261.1/Bin/glslangValidator.exe")
elseif(ARCH STREQUAL "x86")
set(GLSLC "C:/VulkanSDK/1.3.261.1/Bin32/glslangValidator.exe")
endif()

message("ShaderMake")
message("CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

set(SHADERS_IN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vulkan")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/Shaders/Vulkan")

file(GLOB SHADERS "${SHADERS_IN_DIR}/*.vert" "${SHADERS_IN_DIR}/*.frag")

file(MAKE_DIRECTORY ${SHADERS_OUT_DIR})


message("CMAKE_SOURCE_DIR ${GLSLC}")
foreach(SHADER ${SHADERS})
	get_filename_component(SHADER_NAME ${SHADER} NAME)
	set(SHADER_OUT_NAME "${SHADERS_OUT_DIR}/${SHADER_NAME}.spv")
	list(APPEND SHADER_OUT_NAMES ${SHADER_OUT_NAME})
	add_custom_command(
		MAIN_DEPENDENCY ${SHADER}
		OUTPUT ${SHADER_OUT_NAME}
		COMMAND ${GLSLC} "-V" ${SHADER} "-o" ${SHADER_OUT_NAME}
		VERBATIM)
endforeach()


#OpenGL Shader Coppying

set(SHADERS_IN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/Shaders/OpenGL")
file(GLOB SHADERS "${SHADERS_IN_DIR}/*.vert" "${SHADERS_IN_DIR}/*.frag")
foreach(SHADER ${SHADERS})
	get_filename_component(SHADER_NAME ${SHADER} NAME)
	set(SHADER_OUT_NAME "${SHADERS_OUT_DIR}/${SHADER_NAME}")
	list(APPEND SHADER_OUT_NAMES ${SHADER_OUT_NAME})
	configure_file(${SHADER} ${SHADER_OUT_NAME} COPYONLY)
endforeach()
add_custom_target(build_shaders DEPENDS ${SHADER_OUT_NAMES})