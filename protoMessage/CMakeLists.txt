project(protoMessage)

set(PROTO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(PB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pb)

file(GLOB PROTO_FILES ${PROTO_PATH}/*.proto )

if(UNIX)
    set(PROTOC ../3rdParty/tools/arm64-osx/protoc)
elseif(WIN32)
    set(PROTOC ../3rdParty/tools/x64-windows/protoc.exe)
endif()

# 删除之前的文件
execute_process(COMMAND rm -rf ${PB_DIR})
# 创建文件夹
execute_process( COMMAND mkdir ${PB_DIR})
# 生成proto cpp文件
execute_process(COMMAND ${PROTOC} --proto_path=${PROTO_PATH} --cpp_out=${PB_DIR} ${PROTO_FILES})
# 生成的源文件
file(GLOB PROTO_SRCS  ${PB_DIR}/*.cc)
# 生成的头文件
file(GLOB PROTO_HDRS ${PB_DIR}/*.h)
# 生成静态库
add_library(${PROJECT_NAME} STATIC ${PROTO_SRCS} ${PROTO_HDRS} )
target_link_libraries(${PROJECT_NAME} libprotobuf.lib)