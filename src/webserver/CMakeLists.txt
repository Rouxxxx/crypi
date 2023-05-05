add_library(web_server SHARED
    login.cpp
    login.hh
)

target_link_libraries(web_server PRIVATE wt wthttp)
