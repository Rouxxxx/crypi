add_library(bfv_lib SHARED
    bfv.cpp 
    bfv.hh
)

target_link_libraries(bfv_lib PRIVATE SEAL::seal)
