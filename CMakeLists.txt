# CMakeList.txt : CMake project for Rebellion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Rebellion")

# Add source to this project's executable.
add_executable (Rebellion "src/App.cpp" "libs/glfw-3.4/include/GLFW/glfw3.h" "libs/glfw-3.4/include/GLFW/glfw3native.h" "src/shapes/Rectangle.h"  "src/RunModes/Window.cpp" "src/shapes/Shape.h" "src/shapes/Rectangle.cpp" "src/shapes/Shape.cpp" "src/RunModes/Window.h" "src/App.h" "src/services/ConfigLoader.cpp" "src/services/ConfigLoader.h" "src/RunModes/Terminal.h" "src/RunModes/Terminal.cpp" "src/services/WebService.h" "src/services/WebService.cpp" "libs/curl/include/zconf.h" "libs/curl/include/zlib.h" "libs/curl/include/curl/curl.h" "libs/curl/include/curl/curlver.h" "libs/curl/include/curl/easy.h" "libs/curl/include/curl/header.h" "libs/curl/include/curl/mprintf.h" "libs/curl/include/curl/multi.h" "libs/curl/include/curl/options.h" "libs/curl/include/curl/stdcheaders.h" "libs/curl/include/curl/system.h" "libs/curl/include/curl/typecheck-gcc.h" "libs/curl/include/curl/urlapi.h" "libs/curl/include/curl/websockets.h")

# Tell CMake where GLFW's headers are
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
    ${CMAKE_SOURCE_DIR}/libs/curl/include
)

# Link GLFW and OpenGL
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/glfw3.lib
    ${CMAKE_SOURCE_DIR}/libs/curl/libcurl.lib
    ${CMAKE_SOURCE_DIR}/libs/curl/zlib.lib
    opengl32.lib
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Rebellion PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
