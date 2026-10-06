# Rebellion

A lightweight web browser prototype written in C++20. CMake is the project's build interface on Windows, macOS, and Linux.

## Requirements

- CMake 3.21 or newer
- A C++20 compiler supported by CMake
- CURL, GLFW 3.3 or newer, ZLIB, and OpenGL development packages

Install the libraries using your operating system's package manager or a C++ dependency manager such as vcpkg. CMake discovers the installed packages; the vcpkg toolchain can be selected with `-DCMAKE_TOOLCHAIN_FILE` when configuring.

## Configure and build

From the repository root, use the same commands on all supported systems:

```sh
cmake --preset debug
cmake --build --preset debug
```

For an optimized build:

```sh
cmake --preset release
cmake --build --preset release
```

Without presets, use CMake's standard configure/build commands:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

For a multi-configuration generator such as Visual Studio, the `--config` option selects the configuration. For a single-configuration generator, `CMAKE_BUILD_TYPE` selects it when configuring.

## Dependencies

With vcpkg installed, configure by passing its toolchain file. For example:

```sh
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
```

Alternatively, install CURL, GLFW, ZLIB, and OpenGL development files through your system package manager, then run the standard CMake commands above. CMake does not require Ninja or a particular compiler; it uses the generator and toolchain available on the host.

## Run

Run the generated `Rebellion` executable from the repository root so it can read `config.cfg`. The default mode is terminal mode; set `m=1` in that file to enable the GLFW window.
