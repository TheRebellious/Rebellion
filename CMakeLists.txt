# CMakeList.txt : CMake project for Rebellion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Rebellion")

# ── Dependencies ──────────────────────────────────────────────────────────────
# find_package() works with both vcpkg and system-installed packages.
# vcpkg users: configure CMake with -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake
# System users: install curl, glfw3, zlib via apt / brew / pacman / etc.

find_package(CURL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)

# ── Sources ───────────────────────────────────────────────────────────────────
add_executable(Rebellion
    "src/App.cpp"
    "src/App.h"
    "src/RunModes/Window.cpp"
    "src/RunModes/Window.h"
    "src/RunModes/Terminal.cpp"
    "src/RunModes/Terminal.h"
    "src/services/ConfigLoader.cpp"
    "src/services/ConfigLoader.h"
    "src/services/WebService.cpp"
    "src/services/WebService.h"
    "src/shapes/Rectangle.cpp"
    "src/shapes/Rectangle.h"
    "src/shapes/Shape.cpp"
    "src/shapes/Shape.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Rebellion PROPERTY CXX_STANDARD 20)
endif()

if (MSVC)
  target_compile_options(Rebellion PRIVATE /EHsc)
endif()

# ── Include dirs ──────────────────────────────────────────────────────────────
target_include_directories(Rebellion PRIVATE
    ${CURL_INCLUDE_DIRS}
)

# ── Link libraries ────────────────────────────────────────────────────────────
target_link_libraries(Rebellion PRIVATE
    CURL::libcurl
    glfw
    ZLIB::ZLIB
    OpenGL::GL
)

# ── Windows: copy libcurl.dll next to the exe after build ────────────────────
# This only runs when curl was found as a shared/DLL library.
if (WIN32)
    add_custom_command(TARGET Rebellion POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Rebellion>
            $<TARGET_FILE_DIR:Rebellion>
        COMMAND_EXPAND_LISTS
    )
endif()

# TODO: Add tests and install targets if needed.
