cmake_minimum_required(VERSION 3.10)
project(Xviz VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set (CMAKE_BUILD_TYPE Release)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Please switch to x64 build.")
    return()
endif()

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
    3rdParty/ImGuiFileDialog
    common
    ${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories(
    ${THIRD_PARTY_LIB}
)

add_subdirectory(3rdParty)
add_subdirectory(core)

# add_subdirectory(protoMessage)
      
# add_subdirectory(xviz)
# add_executable(XvizNode app/main.cpp)
# target_link_libraries(XvizNode xviz)



# add_subdirectory(xvizMsgSender)

# add_executable(xvizSenderDemo app/xvizSenderDemo.cpp)
# target_link_libraries(xvizSenderDemo xvizMsgSender)

# if(WIN32)
# file(COPY 3rdParty/bin/x64-windows/fmt.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug")
# file(COPY 3rdParty/bin/x64-windows/jsoncpp.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug")
# file(COPY 3rdParty/bin/x64-windows/libzmq-mt-4_3_5.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug")
# file(COPY 3rdParty/bin/x64-windows/libprotobuf.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug")
# endif()



# add_custom_command(
#          TARGET XvizNode POST_BUILD
#          COMMAND ${CMAKE_COMMAND} -E copy_directory
#                  ${CMAKE_CURRENT_SOURCE_DIR}/data/
#                  ${CMAKE_CURRENT_BINARY_DIR}/data/
#                  )
         

#  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TESTBED_SOURCE_FILES})