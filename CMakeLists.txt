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
add_executable (Rebellion "src/Rebellion.cpp" "libs/glfw-3.4/include/GLFW/glfw3.h" "libs/glfw-3.4/include/GLFW/glfw3native.h" "src/shapes/Rectangle.cpp" "src/shapes/Global.h" "src/Window.cpp")

# Tell CMake where GLFW's headers are
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
)

# Link GLFW and OpenGL
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/glfw3.lib
    opengl32.lib
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Rebellion PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
