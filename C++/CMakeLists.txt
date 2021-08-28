cmake_minimum_required(VERSION 3.10)
project(YukselC2Interpolation)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC $ENV{RESOURCES}/Include)
    target_link_directories(${PROJECT_NAME} PUBLIC $ENV{RESOURCES}/Library/Windows_X86_64)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC gsl)