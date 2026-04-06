cmake_minimum_required(VERSION 3.21)

set(PIXELPART_GAMEMAKER_VERSION 1.9.0)

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
if(EMSCRIPTEN)
	# Need add_executable to generate wasm
	add_executable(pixelpart-gamemaker)
else()
	add_library(pixelpart-gamemaker SHARED)
endif()

set_target_properties(pixelpart-gamemaker PROPERTIES
	OUTPUT_NAME "pixelpartgm")

# OS-specific settings
if(WIN32)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")

	set_target_properties(pixelpart-gamemaker PROPERTIES
		OUTPUT_NAME "pixelpartgm_x64")
elseif(EMSCRIPTEN)
	set_target_properties(pixelpart-gamemaker PROPERTIES
		OUTPUT_NAME "libpixelpartgm")
	set_target_properties(pixelpart-gamemaker PROPERTIES
		COMPILE_FLAGS "-Os")
	set_target_properties(pixelpart-gamemaker PROPERTIES
		LINK_FLAGS "--no-entry -Os -s WASM=1 -s SINGLE_FILE=1 \
			-s EXPORTED_FUNCTIONS=[\"_malloc\",\"_free\"] \
			-s EXPORTED_RUNTIME_METHODS=[\"HEAPU8\",\"UTF8ToString\",\"stringToUTF8\",\"stringToNewUTF8\",\"lengthBytesUTF8\"]")
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
