cmake_minimum_required(VERSION 3.16)

project(SailTimer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Build executable
add_executable(
    json-test
    src/json-test.c
    src/read-text.c
)