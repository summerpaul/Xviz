cmake_minimum_required(VERSION 3.8)
project(Xviz VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include
    3rdParty/spdlog/include
    3rdParty/imgui
    3rdParty/glad/include
    3rdParty/glfw/include
    3rdParty/imgui_impl
    3rdParty/box2d/include
    )

add_subdirectory(3rdParty)
add_subdirectory(src)

add_executable(Xviz_node main.cpp)
target_link_libraries(Xviz_node xviz)
