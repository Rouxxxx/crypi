add_library(tests_lib SHARED
    BFV_tests.cpp
    Tester.cpp
)

target_link_libraries(tests_lib PRIVATE SEAL::seal)
