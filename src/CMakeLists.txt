cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR oti_oti_fight)
project(${PROJECT_NAME_STR} C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-Wall -ansi -Wno-deprecated -std=c++14)
endif()

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME_STR} ncurses)
target_link_libraries(${PROJECT_NAME_STR} ${PROJECT_LIB_NAME})
