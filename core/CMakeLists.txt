project(XVIZ)



add_executable(${PROJECT_NAME} main.cpp program.cpp)

target_link_libraries(${PROJECT_NAME} imgui_impl)

