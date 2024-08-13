cmake_minimum_required(VERSION 3.22)

project(image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

add_library(common common/parameters_bmp.cpp common/parameters_bmp.hpp common/progargs.hpp common/progargs.cpp common/utilidades.hpp common/utilidades.cpp)
add_library(aos aos/lectura_aos.cpp aos/hist_aos.cpp aos/copy_aos.cpp aos/mono_aos.cpp aos/copy_aos.hpp aos/lectura_aos.hpp aos/mono_aos.hpp aos/hist_aos.hpp aos/gauss_aos.cpp aos/gauss_aos.hpp aos/calls_aos.cpp aos/calls_aos.hpp)
add_library(soa soa/lectura_soa.cpp soa/hist_soa.cpp soa/copy_soa.cpp soa/mono_soa.cpp soa/copy_soa.hpp soa/lectura_soa.hpp soa/mono_soa.hpp soa/hist_soa.hpp soa/gauss_soa.cpp soa/gauss_soa.hpp soa/calls_soa.cpp soa/calls_soa.hpp)

add_executable(imgaos image-aos/imgaos.cpp)
target_link_libraries(imgaos aos common)

add_executable(imgsoa image-soa/imgsoa.cpp)
target_link_libraries(imgsoa soa common)
