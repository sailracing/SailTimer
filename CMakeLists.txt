cmake_minimum_required(VERSION 3.16)

project(SailTimer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find cJSON installed from apt
find_package(PkgConfig REQUIRED)
pkg_check_modules(CJSON REQUIRED libcjson)

# Executable
add_executable(json-test
    src/json-test.c
    src/read-text.c
)

# Include paths
target_include_directories(json-test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CJSON_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(json-test PRIVATE
    ${CJSON_LIBRARIES}
)

# Project headers
target_include_directories(json-test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)