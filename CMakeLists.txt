cmake_minimum_required(VERSION 3.24)
project(Light3DEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENGINE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(ENGINE_USE_LOCAL_DEPS "Use local dependency source dirs instead of downloading" OFF)

include(FetchContent)

if(ENGINE_USE_LOCAL_DEPS)
  set(GLFW_LOCAL_SOURCE_DIR "" CACHE PATH "Path to local GLFW source directory")
  set(GLAD_LOCAL_SOURCE_DIR "" CACHE PATH "Path to local GLAD source directory")
  set(GLM_LOCAL_SOURCE_DIR  "" CACHE PATH "Path to local GLM source directory")

  if(NOT EXISTS "${GLFW_LOCAL_SOURCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "ENGINE_USE_LOCAL_DEPS=ON requires valid GLFW_LOCAL_SOURCE_DIR")
  endif()
  if(NOT EXISTS "${GLAD_LOCAL_SOURCE_DIR}/cmake/CMakeLists.txt" AND NOT EXISTS "${GLAD_LOCAL_SOURCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "ENGINE_USE_LOCAL_DEPS=ON requires valid GLAD_LOCAL_SOURCE_DIR")
  endif()
  if(NOT EXISTS "${GLM_LOCAL_SOURCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "ENGINE_USE_LOCAL_DEPS=ON requires valid GLM_LOCAL_SOURCE_DIR")
  endif()

  FetchContent_Declare(glfw SOURCE_DIR "${GLFW_LOCAL_SOURCE_DIR}")
  FetchContent_Declare(glad SOURCE_DIR "${GLAD_LOCAL_SOURCE_DIR}")
  FetchContent_Declare(glm  SOURCE_DIR "${GLM_LOCAL_SOURCE_DIR}")
else()
  # Use release archives instead of git clone so a git executable is not required.
  FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.zip
  )

  FetchContent_Declare(
    glad
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
  )

  FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
  )
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw glad glm)

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

set(ENGINE_GLAD_TARGET "")
if(TARGET glad::glad)
  set(ENGINE_GLAD_TARGET glad::glad)
elseif(TARGET glad)
  set(ENGINE_GLAD_TARGET glad)
elseif(TARGET libglad)
  set(ENGINE_GLAD_TARGET libglad)
else()
  message(FATAL_ERROR "GLAD target was not found after FetchContent_MakeAvailable(glad)")
endif()

set(ENGINE_GLM_TARGET "")
if(TARGET glm::glm)
  set(ENGINE_GLM_TARGET glm::glm)
elseif(TARGET glm)
  set(ENGINE_GLM_TARGET glm)
else()
  message(FATAL_ERROR "GLM target was not found after FetchContent_MakeAvailable(glm)")
endif()

target_link_libraries(engine
  PUBLIC
    glfw
    ${ENGINE_GLAD_TARGET}
    ${ENGINE_GLM_TARGET}
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
