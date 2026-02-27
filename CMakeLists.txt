cmake_minimum_required(VERSION 3.24)
project(Light3DEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENGINE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v2.0.8
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

add_library(engine
  src/engine/Application.cpp
  src/engine/Engine.cpp
  src/engine/Window.cpp
  src/engine/Camera.cpp
  src/engine/Shader.cpp
  src/engine/Mesh.cpp
  src/engine/Renderer.cpp
)

target_include_directories(engine PUBLIC include)

target_link_libraries(engine
  PUBLIC
    glfw
    glad::glad
    glm::glm
)

if(MSVC)
  target_compile_options(engine PRIVATE /W4)
  if(ENGINE_WARNINGS_AS_ERRORS)
    target_compile_options(engine PRIVATE /WX)
  endif()
else()
  target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic)
  if(ENGINE_WARNINGS_AS_ERRORS)
    target_compile_options(engine PRIVATE -Werror)
  endif()
endif()

add_executable(client_app src/client/main.cpp)
target_link_libraries(client_app PRIVATE engine)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
