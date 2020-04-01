project(module_data_statistics CXX)

cmake_minimum_required(VERSION 2.8)

set(MONGOOSE_DIR ${CMAKE_SOURCE_DIR}/../mongoose)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  #设置c++的编译选项
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")  #设置c的编译选项

aux_source_directory(. SRC_LIST)
add_subdirectory(${MONGOOSE_DIR} mongoose_binary_dir)

set(INC_DIR /usr/local/include/ )
set(LINK_DIR /usr/local/lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} mongoose)
