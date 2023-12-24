set (XVIZ_SOURCE_FILES
    xviz.cpp 
    draw.cpp 
    settings.cpp 
    sence.cpp 
    communication.cpp
    image.cpp
    images.cpp
    layer.cpp
)


add_library(xviz ${XVIZ_SOURCE_FILES})
target_link_libraries(xviz  
    imgui_impl 
    box2d  
    jsoncpp 
    zmq 
    spdlog  
    fmt 
    protoMessage
  #  nfd
    )  
