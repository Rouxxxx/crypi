add_executable(e_voting hello.cpp)

target_link_libraries(e_voting SEAL::seal)
target_link_libraries(e_voting utils_lib bfv_lib)
target_link_libraries(e_voting wt wthttp)
