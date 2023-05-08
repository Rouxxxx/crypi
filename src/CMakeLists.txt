add_executable(e_voting main.cpp)

target_link_libraries(e_voting SEAL::seal)
target_link_libraries(e_voting utils_lib bfv_lib web_server)
target_link_libraries(e_voting wt wthttp)
target_link_libraries(e_voting OpenSSL::SSL)

add_subdirectory(BFV)
add_subdirectory(utils)
add_subdirectory(webserver)
