add_executable(e_voting main.cpp)

target_link_libraries(e_voting SEAL::seal)
target_link_libraries(e_voting utils_lib)

