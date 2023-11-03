cmake_minimum_required(VERSION 3.15)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()
project(YukselC2Interpolation)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(GSL REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE GSL::gsl GSL::gslcblas)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
