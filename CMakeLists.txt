cmake_minimum_required(VERSION 3.21)

set(PIXELPART_GAMEMAKER_VERSION 1.8.3)

project(pixelpart-gamemaker
	VERSION ${PIXELPART_GAMEMAKER_VERSION}
	LANGUAGES C CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Messages
message(STATUS "Pixelpart plugin for GameMaker: Version ${PIXELPART_GAMEMAKER_VERSION}")
message(STATUS "Pixelpart plugin for GameMaker: Target ${CMAKE_SYSTEM_NAME}")

# Target
add_library(pixelpart-gamemaker SHARED)

# OS-specific settings
if(WIN32)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Architecture-specific settings
if(PIXELPART_GAMEMAKER_ARCHITECTURE STREQUAL "x64")
	if(WIN32)
		set_target_properties(pixelpart-gamemaker PROPERTIES
			OUTPUT_NAME "pixelpart_x64")
	else()
		set_target_properties(pixelpart-gamemaker PROPERTIES
			OUTPUT_NAME "pixelpart")
	endif()

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		add_compile_options("-m64")
		add_link_options("-m64")
	endif()
else()
	set_target_properties(pixelpart-gamemaker PROPERTIES
		OUTPUT_NAME "pixelpart")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		add_compile_options("-m32")
		add_link_options("-m32")
	endif()
endif()

# Options for pixelpart-runtime
set(PIXELPART_RUNTIME_MULTITHREADING OFF)
set(PIXELPART_RUNTIME_SIMD ON)

# Includes
include_directories(.)

# Subdirectories
add_subdirectory(src)
add_subdirectory(pixelpart-runtime)

# Link pixelpart-runtime library
set_target_properties(pixelpart-runtime PROPERTIES
	POSITION_INDEPENDENT_CODE ON)
target_link_libraries(pixelpart-gamemaker
	PRIVATE pixelpart-runtime)

# Install binaries
install(TARGETS pixelpart-gamemaker
	LIBRARY DESTINATION .
	RUNTIME DESTINATION .)
