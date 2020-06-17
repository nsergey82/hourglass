cmake_minimum_required(VERSION 3.5)
project(hgapi VERSION 1.0.0 LANGUAGES CXX)
add_library(hgapi SHARED
        src/profile.cpp
        src/session.cpp
        src/profile_impl.h
        src/session_impl.h

        include/profile.h
        include/session.h
        include/dispatch.h src/dispatch.cpp include/id.h src/id.cpp)
target_include_directories(hgapi PUBLIC include)
