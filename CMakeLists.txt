# CMakeList.txt : CMake project for BasicCmakeSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NDIReceiver")

set(NDI-LIBS "Processing.NDI.Lib.x64.lib")
set(NDI-INCLUDES "C:/Program Files/NDI/NDI 5 SDK/Include")
set(NDI-BIN "C:/Program Files/NDI/NDI 5 SDK/Bin/X64")
set(NDI-DLL "Processing.NDI.Lib.x64.dll")
link_directories("C:/Program Files/NDI/NDI 5 SDK/Lib/x64")

add_subdirectory("core") 
add_subdirectory("tools")

# TODO: Add tests and install targets if needed.
