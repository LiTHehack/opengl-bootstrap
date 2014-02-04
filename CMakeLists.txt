cmake_minimum_required(VERSION 2.8)
project(Procedural-water-refraction)

#Set up the includes
include(ExternalProject)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_CXX_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_EXT_DIR ${PROJECT_SOURCE_DIR}/external)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
  message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
  message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


find_package(OpenGL REQUIRED)
find_package(Git REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
)
#Since there is no easy way to choose between _GLFW_HAS_GLXGETPROCADDRESS, _GLFW_HAS_GLXGETPROCADDRESSARB, _GLFW_HAS_GLXGETPROCADDRESSEXT and _GLFW_HAS_DLOPEN,
#I force the latter, which as least should exist (and work?) everywhere.
add_definitions(
	-D_GLFW_HAS_DLOPEN
	-D_GLFW_HAS_XRANDR
)
add_definitions(-D_UNIX)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL -framework IOKit -framework Foundation -framework AppKit")

# TODO This generates compile errors from glfw on Mavericks, need to investigate further
# add_definitions(-D_MACOSX -ObjC++)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(GLEW_SOURCE
	${PROJECT_EXT_DIR}/glew/src/glew.c
)
add_library(GLEW STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

#We do not want the extra compiling that GLFW does
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Do not build Tests")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Do not build examples")

#Get glfw
# This requies that submodules were initialized properly
add_subdirectory(
  ${PROJECT_EXT_DIR}/glfw/
)


set(ext_libs 
  ${CMAKE_SOURCE_DIR}/external/glfw/include/
  ${CMAKE_SOURCE_DIR}/external/glew/include/
)

include_directories(
        ${ext_libs}
)

#Set up some glm things
set(glm_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external/glm")
set(glm_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${glm_INSTALL_DIR})

ExternalProject_Add(glm
  PREFIX ${glm_PREFIX}
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  CMAKE_ARGS ${glm_CMAKE_ARGS}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_IN_SOURCE 1
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

include_directories(
        ${glm_PREFIX}/src/glm/
)


#This is since common only rolls with header only libraries currently (Might change in the future)

include_directories(
  ${CMAKE_SOURCE_DIR}/common/
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
        glfw
        ${GLFW_LIBRARIES}
	GLEW        
)

add_definitions(
        -Wall
        -Wextra
        -Werror
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


#Below here is where your executable should be added
add_executable(test
  ${CMAKE_SOURCE_DIR}/tutorial01.cpp
)
target_link_libraries(test
  ${ALL_LIBS}
)
