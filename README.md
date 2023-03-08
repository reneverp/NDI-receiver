# NDI Capturing lib

## Prerequisites

- Conan 1.59 : `pip install conan==1.59`
- NDI SDK : Download and install the latest NDI SDK from https://www.ndi.tv/sdk/

## Pre-Build
- Add conan-center as a conan remote: `conan remote add https://center.conan.io`
- Run `conan install ..\..\..\tools\NDI-Console\ -s build_type=Debug` from out\build\x64-debug
- Run `conan install ..\..\..\tools\NDI-Console\ -s build_type=Release` from out\build\x64-debug

