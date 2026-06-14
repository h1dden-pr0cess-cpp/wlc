cmake_minimum_required(VERSION 3.25)

project(
    wlc
    VERSION 0.1.0
    DESCRIPTION "Mini Wireless LAN Controller"
    LANGUAGES CXX
)

# ---------- C++ ----------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------- Build type ----------

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# ---------- Threads ----------

find_package(Threads REQUIRED)

# ---------- Executable ----------

add_executable(wlc)

target_sources(wlc
    PRIVATE
        src/main.cpp

        src/app/wlc.cpp

        src/protocol/parser.cpp
        src/protocol/serializer.cpp
)

target_include_directories(wlc
    PRIVATE
        include
)

# ---------- Warnings ----------

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(wlc PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wcast-align
        -Wnull-dereference
        -Wdouble-promotion
        -Wimplicit-fallthrough
    )
endif()

# ---------- Debug ----------

target_compile_definitions(wlc PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
)

# ---------- Libraries ----------

target_link_libraries(wlc
    PRIVATE
        Threads::Threads
)
