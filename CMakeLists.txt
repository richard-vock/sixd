cmake_minimum_required(VERSION 3.8.1)
project(sixd)
include_directories("${PROJECT_SOURCE_DIR}/include")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set (sixd_VERSION_MAJOR 0)
set (sixd_VERSION_MINOR 1)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wno-maybe-uninitialized -fPIC -fconcepts -g)

add_library(sixd "src/sixd.cpp")
target_compile_features(sixd PUBLIC cxx_std_17)
target_link_libraries(sixd CONAN_PKG::yaml-cpp CONAN_PKG::Eigen3 CONAN_PKG::pngpp)
