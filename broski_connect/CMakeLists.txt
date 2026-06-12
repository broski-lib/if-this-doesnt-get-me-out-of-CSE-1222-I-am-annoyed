cmake_minimum_required(VERSION 3.15)
project(broski_connect CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# required packages
find_package(Threads REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# paths for generated proto files
set(PROTO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
set(PROTO_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_OUT_DIR})

# protoc executable and the gRPC C++ plugin executable
find_program(PROTOC_PROGRAM protoc REQUIRED)
find_program(GRPC_CPP_PLUGIN_PROGRAM grpc_cpp_plugin REQUIRED)

# input proto file and the expected generated files
set(PROTO_FILE "${PROTO_SRC_DIR}/service.proto")
set(GEN_PROTO_SRC "${PROTO_OUT_DIR}/service.pb.cc")
set(GEN_PROTO_HDR "${PROTO_OUT_DIR}/service.pb.h")
set(GEN_GRPC_SRC  "${PROTO_OUT_DIR}/service.grpc.pb.cc")
set(GEN_GRPC_HDR  "${PROTO_OUT_DIR}/service.grpc.pb.h")

# generate C++ files from .proto
add_custom_command(
    OUTPUT "${GEN_PROTO_SRC}" "${GEN_PROTO_HDR}" "${GEN_GRPC_SRC}" "${GEN_GRPC_HDR}"
    COMMAND ${PROTOC_PROGRAM}
    ARGS --proto_path=${PROTO_SRC_DIR}
         --cpp_out=${PROTO_OUT_DIR}
         --grpc_out=${PROTO_OUT_DIR}
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_PROGRAM}
         ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
    COMMENT "Compiling protocol buffers using protoc"
    VERBATIM
)

# create a library out of the generated sources
add_library(proto_gen_lib STATIC
    ${GEN_PROTO_SRC}
    ${GEN_GRPC_SRC}
)
target_include_directories(proto_gen_lib PUBLIC ${PROTO_OUT_DIR})
target_link_libraries(proto_gen_lib PUBLIC gRPC::grpc++ protobuf::libprotobuf)


# Server Build
add_executable(bc_server src/server.cpp)
target_link_libraries(bc_server PRIVATE proto_gen_lib Threads::Threads)

# Client Build
add_executable(bc_client src/client.cpp)
target_link_libraries(bc_client PRIVATE proto_gen_lib Threads::Threads)
