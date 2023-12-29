message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "${CMAKE_CURRENT_BINARY_DIR}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/frag.spv ${CMAKE_BINARY_DIR}/Shaders/frag.spv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vert.spv ${CMAKE_BINARY_DIR}/Shaders/vert.spv COPYONLY)