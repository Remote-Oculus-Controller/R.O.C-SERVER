# CMakeLists.txt for ROC video server
# This file is used to build the project with cmake

# Set cmake minimun version

cmake_minimum_required (VERSION 2.6)

# Set project name

project(ROC)

# The version number.

set (ROC_VERSION_MAJOR 1)
set (ROC_VERSION_MINOR 0)

# Modules directory

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# Protocol directory

set(ROC_PROTOCOL_FOLDER "${CMAKE_SOURCE_DIR}/Protobuf")

# ROC GPU option

option(ROC_WITH_CUDA "GPU acceleration" OFF)

# Dependencies

find_package (Threads   REQUIRED)
find_package(libv4l2    REQUIRED)
find_package(libx264    REQUIRED)
find_package(FFmpeg     REQUIRED COMPONENTS avutil swscale)
find_package(OpenCV     REQUIRED)
find_package(LiveMedia  REQUIRED)
find_package(Protobuf   REQUIRED)

# If OpenCV CUDA support found , set ROC_WITH_CUDA to ON

if(OpenCV_CUDA_VERSION)
  set(ROC_WITH_CUDA ON)
elseif(ROC_WITH_CUDA)
    message(FATAL_ERROR "ROC_WITH_CUDA is ON But OpenCV is build without CUDA support !")
endif()

# If ROC_WITH_CUDA is ON , enable module

if(ROC_WITH_CUDA)
  add_definitions(-DROC_WITH_CUDA)
endif()

# Add includes directories

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${LiveMedia_INCLUDE_DIRS})
include_directories(includes sources)

# Generate .hpp and .cpp files from .proto file

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${ROC_PROTOCOL_FOLDER}/proto.proto)

# Add source files

file(GLOB MAIN sources/Main/*.cpp)
file(GLOB VIDEO sources/Video/*.cpp)
file(GLOB ENCODER sources/Encoder/*.cpp)
file(GLOB SYNC sources/Sync/*.cpp)
file(GLOB LOGGER sources/Logger/*.cpp)
file(GLOB NETWORK sources/Network/*.cpp)
file(GLOB RTSPFACTORY sources/RTSPFactory/*.cpp)
file(GLOB ENCODER sources/Encoder/*.cpp)
file(GLOB MANAGER sources/Manager/*.cpp)
file(GLOB PARSER sources/Parser/*.cpp)
file(GLOB PROCESSING sources/Processing/*.cpp)
file(GLOB SINGLETONS sources/Singletons/*.cpp)
file(GLOB INTERPRETOR sources/Interpretor/*.cpp)

# add the executable

add_executable(ROC ${MAIN} ${VIDEO} ${SYNC} ${NETWORK} ${RTSPFACTORY} ${ENCODER} ${MANAGER} ${LOGGER} ${PARSER} ${PROCESSING} ${SINGLETONS} ${INTERPRETOR} ${PROTO_SRCS} ${PROTO_HDRS})

# link libraries

target_link_libraries(ROC ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS} ${LIBX264_LIBRARIES} ${FFMPEG_LIBRARIES} ${PROTOBUF_LIBRARIES} ${LiveMedia_LIBRARIES})
