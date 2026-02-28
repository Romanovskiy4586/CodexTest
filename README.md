# Light3D Engine (C++23 + CMake + GLFW + GLAD)

Небольшой 3D-движок с клиентским фреймворком, где клиент реализует жизненный цикл:
- `onAttach()` — инициализация ресурсов;
- `onUpdate()` — игровая логика;
- `onRender()` — отрисовка сцены.

## Возможности

- отображение нескольких простых 3D-примитивов: **куб, пирамида, плоскость**;
- Blinn-Phong освещение (материал + источник света);
- свободная камера: мышь + **WASD**;
- проект на C++23/CMake, ориентир на MinGW/Clang/libc++.

## Структура

- `include/engine` — публичный API движка;
- `src/engine` — реализация движка;
- `src/client` — пример клиентского приложения;
- `shaders` — GLSL-шейдеры;
- `cmake/Toolchains/mingw-clang-libcxx.cmake` — пример toolchain для MinGW + Clang + libc++.

## Сборка

### Linux/macOS

```bash
cmake -S . -B build
cmake --build build -j
```

### MinGW + Clang + libc++

```bash
cmake -S . -B build-mingw \
  -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchains/mingw-clang-libcxx.cmake
cmake --build build-mingw -j
```


> По умолчанию зависимости скачиваются как ZIP-архивы через `FetchContent` (без `git clone`).
> Это устраняет ошибку вида `could not find git for clone of glfw-populate` в средах, где git недоступен из CMake.

### Офлайн/локальные зависимости (без скачивания)

Если сеть или загрузка архивов недоступны, можно использовать локальные копии исходников:

```bash
cmake -S . -B build   -DENGINE_USE_LOCAL_DEPS=ON   -DGLFW_LOCAL_SOURCE_DIR=/path/to/glfw   -DGLAD_LOCAL_SOURCE_DIR=/path/to/glad   -DGLM_LOCAL_SOURCE_DIR=/path/to/glm
cmake --build build -j
```

## Управление

- `W/S` — вперёд/назад;
- `A/D` — влево/вправо;
- мышь — обзор камеры;
- `Esc` — выход.
