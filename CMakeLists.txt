cmake_minimum_required(VERSION 3.14)
project(esrt)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(stb_image_write)
add_subdirectory(stb_image)

add_executable(esrt camera.cpp render.cpp scripting.cpp hit.cpp main.cpp vec.cpp ray.cpp image.cpp scene.cpp interval.cpp bb.cpp rng.cpp material.cpp stb_image_write_impl.cpp stb_image_impl.cpp)
target_link_libraries(esrt stb_image_write stb_image)
