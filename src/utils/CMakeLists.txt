add_library(utils_lib SHARED
    file.cpp 
    file.hh
    basics.hh
    jsonLib.cpp
    jsonLib.hh
    candidates.cpp
)

target_link_libraries(utils_lib PRIVATE SEAL::seal)
