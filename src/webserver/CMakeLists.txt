add_library(web_server SHARED
    evote.cpp
    evote.hh
    tools.cpp
    tools.hh
    home_page.cpp
    vote_page.cpp
)

target_link_libraries(web_server PRIVATE SEAL::seal)
target_link_libraries(web_server PRIVATE wt wthttp OpenSSL::SSL)
