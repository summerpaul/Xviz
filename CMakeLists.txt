cmake_minimum_required(VERSION 3.10)
project(Xviz VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




add_subdirectory(3rdParty)

include_directories(include
    3rdParty/spdlog/include
    3rdParty/imgui
    3rdParty/glad/include
    3rdParty/glfw/include
    3rdParty/imgui_impl
    3rdParty/box2d/include
    3rdParty/jsoncpp/include
    3rdParty/libzmq/include
    3rdParty/cppzmq
    3rdParty/libzmq/include

    )



link_directories(${CMAKE_BINARY_DIR}/bin)


set (XVIZ_SOURCE_FILES
    src/xviz.cpp 
    src/draw.cpp 
    src/settings.cpp 
    src/sence.cpp 
    src/communication.cpp
)


add_library(xviz ${XVIZ_SOURCE_FILES})
target_link_libraries(xviz  imgui_impl box2d  jsoncpp zmq)        

add_executable(XvizNode main.cpp)
target_link_libraries(XvizNode xviz)

add_custom_command(
         TARGET XvizNode POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory
                 ${CMAKE_CURRENT_SOURCE_DIR}/data/
                 ${CMAKE_CURRENT_BINARY_DIR}/data/)

 source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TESTBED_SOURCE_FILES})