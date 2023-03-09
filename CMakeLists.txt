# CMakeList.txt : CMake project for BasicCmakeSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NDIReceiver")

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

set(NDI-LIBS "Processing.NDI.Lib.x64.lib")
set(NDI-INCLUDES "C:/Program Files/NDI/NDI 5 SDK/Include")
set(NDI-BIN "C:/Program Files/NDI/NDI 5 SDK/Bin/X64")
set(NDI-DLL "Processing.NDI.Lib.x64.dll")
link_directories("C:/Program Files/NDI/NDI 5 SDK/Lib/x64")

 set(CONAN_DISABLE_CHECK_COMPILER "True")

  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup(NO_OUTPUT_DIRS)

add_subdirectory("core") 
add_subdirectory("tools")

# TODO: Add tests and install targets if needed.
