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
message(STATUS "Pixelpart plugin for GameMaker: System ${CMAKE_SYSTEM_NAME}")

# Target
add_library(pixelpart-gamemaker SHARED)

set_target_properties(pixelpart-gamemaker PROPERTIES
	OUTPUT_NAME "pixelpart")

# OS-specific settings
if(WIN32)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")

	set_target_properties(pixelpart-gamemaker PROPERTIES
		OUTPUT_NAME "pixelpart_x64")
endif()

# Options for pixelpart-runtime
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
