project(SyntaxTreeParser)
cmake_minimum_required(VERSION 3.2.0)

file(GLOB_RECURSE SOURCES src/*)
add_library(SyntaxTree ${SOURCES})
target_include_directories(SyntaxTree PUBLIC include)

file(GLOB_RECURSE TEST_SOURCES tests/*)
add_executable(SyntaxTreeTests ${TEST_SOURCES})
target_include_directories(SyntaxTreeTests PRIVATE thirdparty include)
target_link_libraries(SyntaxTreeTests SyntaxTree)