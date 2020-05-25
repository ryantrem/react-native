cmake_minimum_required(VERSION 3.13.2)

project(JSITest)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../../ReactCommon/jsi/jsi ${CMAKE_CURRENT_BINARY_DIR}/jsi)
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../../ReactCommon/jsi
)

add_library(JSITest SHARED src/main/cpp/JSITest.cpp)

target_link_libraries(JSITest
                      # link with these libraries:
                      android
                      log
                      jsi)