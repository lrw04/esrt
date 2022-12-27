cmake_minimum_required(VERSION 3.14)
project(esrt)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(stb_image_write)

add_executable(esrt main.cpp vec.cpp ray.cpp image.cpp stb_image_write_impl.cpp)
target_link_libraries(esrt stb_image_write)
