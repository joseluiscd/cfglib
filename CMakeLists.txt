project(cfg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

add_executable(cfg_test
    test.cpp
    cfg.hpp
    toml.hpp
)
target_link_libraries(cfg_test fmt::fmt)
