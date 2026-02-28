set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_INIT "-stdlib=libc++ -fuse-ld=lld")
set(CMAKE_C_FLAGS_INIT "-fuse-ld=lld")
