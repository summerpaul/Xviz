add_library(xviz xviz.cpp draw.cpp settings.cpp sence.cpp)
target_link_libraries(xviz  imgui_impl box2d  jsoncpp)        