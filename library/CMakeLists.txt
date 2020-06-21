cmake_minimum_required(VERSION 3.5)
project(hgapi VERSION 1.0.0 LANGUAGES CXX)
add_library(hgapi SHARED
        src/profile.cpp
        src/session.cpp
        src/profile_impl.h
        src/session_impl.h
        src/session_b.cpp
        src/dispatch.cpp
        src/id.cpp

        include/profile.h
        include/session.h
        include/session_b.h
        include/dispatch.h
        include/id.h )
target_include_directories(hgapi PUBLIC include)
