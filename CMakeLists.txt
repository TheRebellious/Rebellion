cmake_minimum_required(VERSION 3.21)

project(Rebellion VERSION 0.1.0 LANGUAGES CXX)

find_package(CURL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Rebellion
    src/App.cpp
    src/RunModes/Window.cpp
    src/RunModes/Terminal.cpp
    src/services/ConfigLoader.cpp
    src/services/WebService.cpp
    src/shapes/Rectangle.cpp
    src/shapes/Shape.cpp
)

target_compile_features(Rebellion PRIVATE cxx_std_20)

if(TARGET glfw)
    set(REBELLION_GLFW_TARGET glfw)
elseif(TARGET glfw3::glfw)
    set(REBELLION_GLFW_TARGET glfw3::glfw)
elseif(TARGET unofficial::glfw3::glfw)
    set(REBELLION_GLFW_TARGET unofficial::glfw3::glfw)
else()
    message(FATAL_ERROR "The glfw3 package did not provide a known CMake target")
endif()

target_link_libraries(Rebellion PRIVATE
    CURL::libcurl
    ${REBELLION_GLFW_TARGET}
    ZLIB::ZLIB
    OpenGL::GL
)
