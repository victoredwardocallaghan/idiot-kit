cmake_minimum_required(VERSION 2.8)
project(dipshit)

# Add local repository for FindXXX.cmake modules.
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

# Look for OpenGL.
find_package(OpenGL REQUIRED)

# Look for GLFW.
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})

# Look for GLEW.
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# Set necessary libs.
set(REQUIRED_EXTERNAL_LIBS
	${GLFW_LIBRARIES}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARY}
)

add_subdirectory(src)
