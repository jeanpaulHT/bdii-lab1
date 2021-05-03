cmake_minimum_required(VERSION 3.17)
project(fileOrganization)

set(CMAKE_CXX_STANDARD 20)

add_executable(fileOrganization
        source/p1.cpp headers/p1.h test_headers/test_P1.hpp
#        p2.cpp headers/p2.h test_headers/test_P2.hpp
#        p3.cpp headers/p3.h test_headers/test_P3.hpp
#        p4.cpp headers/p4.h test_headers/test_P4.hpp
        )