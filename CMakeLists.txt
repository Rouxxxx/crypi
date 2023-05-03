cmake_minimum_required(VERSION 3.24)

project(
    e_voting
    VERSION 0.1
    DESCRIPTION "An Homomorphic Encryption Project for CRYPI lesson"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Werror -Wextra -Wpedantic -g)

find_package(SEAL REQUIRED)

add_subdirectory(utils)
add_subdirectory(BFV)
add_subdirectory(src)
