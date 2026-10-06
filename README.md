# Rebellion

A lightweight web browser built from scratch in modern C++ (C++20).

---

## Prerequisites

Before building Rebellion, ensure you have the following tools installed on your system:

### 1. Core Toolchain
- **C++ Compiler** with **C++20** support:
  - **Windows:** Visual Studio 2019 / 2022 / 2026 with the *Desktop development with C++* workload (MSVC 19.28+)
  - **Linux:** GCC 10+ or Clang 11+
  - **macOS:** Xcode Command Line Tools / Apple Clang 12+
- **CMake:** Version `3.15` or higher
- **Ninja:** Build system (included with Visual Studio, or available via system package managers)
- **Git:** For cloning repositories and submodules

### 2. Libraries
The following third-party libraries are required:
- [libcurl](https://curl.se) (with SSL support)
- [GLFW 3](https://www.glfw.org) (Windowing and input)
- [zlib](https://zlib.net) (Data compression)
- [OpenGL](https://www.opengl.org) (Graphics API, provided by OS/graphics drivers)

> **Tip:** You do not need to manually install these C++ libraries if you use **vcpkg**; they will be installed automatically via `vcpkg.json`.

---

## Getting Started: vcpkg Setup (Recommended)

Rebellion uses **vcpkg manifest mode** (`vcpkg.json`) to manage dependencies cross-platform.

### 1. Install vcpkg (One-time Setup)

#### Windows (PowerShell)
```powershell
# Clone vcpkg to your preferred directory (e.g. C:\Users\<Username>\vcpkg)
git clone https://github.com/microsoft/vcpkg "$HOME\vcpkg"
& "$HOME\vcpkg\bootstrap-vcpkg.bat"

# Set the VCPKG_ROOT environment variable (permanent for current user)
[System.Environment]::SetEnvironmentVariable("VCPKG_ROOT", "$HOME\vcpkg", "User")
$env:VCPKG_ROOT = "$HOME\vcpkg"
```

#### Linux & macOS (Bash / Zsh)
```bash
# Clone vcpkg to your home directory
git clone https://github.com/microsoft/vcpkg "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh"

# Add to ~/.bashrc or ~/.zshrc
export VCPKG_ROOT="$HOME/vcpkg"
```

---

## Build Instructions

### Method 1: Using Visual Studio (Windows)

1. Open **Visual Studio**.
2. Select **File > Open > Folder...** and select the `Rebellion` root folder.
3. Visual Studio will detect `CMakePresets.json`. Select the **`x64 Debug (vcpkg)`** configuration from the preset dropdown at the top.
4. Press **Build > Build All** (or `Ctrl+Shift+B`).
5. Select `Rebellion.exe` as the startup target and press **F5** to run with debugging or **Ctrl+F5** to run without debugging.

---

### Method 2: Command Line (CLI)

#### Windows (Developer PowerShell / Command Prompt)

Open **Developer PowerShell for VS** (or load `Launch-VsDevShell.ps1`):

```powershell
# Configure CMake with vcpkg preset
cmake --preset x64-debug-vcpkg

# Build the executable
cmake --build out/build/x64-debug-vcpkg

# Run Rebellion
.\out\build\x64-debug-vcpkg\Rebellion.exe
```

For Release builds:
```powershell
cmake --preset x64-release-vcpkg
cmake --build out/build/x64-release-vcpkg
```

#### Linux

```bash
# Configure
cmake --preset linux-debug-vcpkg

# Build
cmake --build out/build/linux-debug-vcpkg

# Run
./out/build/linux-debug-vcpkg/Rebellion
```

#### macOS

```bash
# Configure
cmake --preset macos-debug-vcpkg

# Build
cmake --build out/build/macos-debug-vcpkg

# Run
./out/build/macos-debug-vcpkg/Rebellion
```

---

## Alternative: Building with System Packages (Without vcpkg)

If you prefer using your operating system's package manager instead of vcpkg:

### 1. Install System Dependencies

- **Ubuntu / Debian:**
  ```bash
  sudo apt update
  sudo apt install -y build-essential cmake ninja-build libcurl4-openssl-dev libglfw3-dev zlib1g-dev libgl1-mesa-dev
  ```

- **Arch Linux:**
  ```bash
  sudo pacman -S base-devel cmake ninja curl glfw-x11 zlib mesa
  ```

- **macOS (Homebrew):**
  ```bash
  brew install cmake ninja curl glfw zlib
  ```

### 2. Configure & Build

```bash
# Linux
cmake --preset linux-debug
cmake --build out/build/linux-debug

# macOS
cmake --preset macos-debug
cmake --build out/build/macos-debug
```

---

## Configuration & Usage

Rebellion reads settings from `config.cfg` located in the application working directory (or uses internal defaults).

### Running Modes
- **Window mode (GUI):** Opens an OpenGL/GLFW window and renders web components.
- **Terminal mode (CLI):** Command-line interactive shell for web requests and search.
