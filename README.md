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

## Управление

- `W/S` — вперёд/назад;
- `A/D` — влево/вправо;
- мышь — обзор камеры;
- `Esc` — выход.
