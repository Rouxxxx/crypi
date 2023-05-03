add_executable(e_voting main.cpp)

find_package(SEAL 4.1 REQUIRED)
target_link_libraries(e_voting SEAL::seal)
