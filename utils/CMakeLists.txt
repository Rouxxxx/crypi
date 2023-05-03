add_library(utils_lib SHARED
    file.cpp 
    file.hh
    basics.hh
    nlohmann_json.hpp
)

target_link_libraries(utils_lib PRIVATE SEAL::seal)
