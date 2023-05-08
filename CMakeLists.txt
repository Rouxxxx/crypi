cmake_minimum_required(VERSION 3.24)

project(
    e_voting
    VERSION 0.2
    DESCRIPTION "An Homomorphic Encryption Project for CRYPI lesson"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Werror -Wextra -Wpedantic -g)

find_package(SEAL REQUIRED)
find_package(Wt REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(src)
