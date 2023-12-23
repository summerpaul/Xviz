cmake_minimum_required(VERSION 3.10)
project(Xviz VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)





if(WIN32)
    set(THIRD_PARTY_LIB 3rdParty/lib/x64-windows)
elseif(UNIX)
    set(THIRD_PARTY_LIB 3rdParty/lib/arm64-osx)    
endif()


include_directories(    
    3rdParty/include
    3rdParty/glad/include
    3rdParty/glfw/include
    3rdParty/imgui_impl
    3rdParty/imgui
    common
)




link_directories(
    ${THIRD_PARTY_LIB}
)

add_subdirectory(3rdParty)
      
add_subdirectory(xviz)
add_executable(XvizNode main.cpp)
target_link_libraries(XvizNode xviz)



add_subdirectory(xvizMsgSender)

add_executable(xvizSenderDemo xvizSenderDemo.cpp)
target_link_libraries(xvizSenderDemo xvizMsgSender)

add_custom_command(
         TARGET XvizNode POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory
                 ${CMAKE_CURRENT_SOURCE_DIR}/data/
                 ${CMAKE_CURRENT_BINARY_DIR}/data/)

 source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TESTBED_SOURCE_FILES})