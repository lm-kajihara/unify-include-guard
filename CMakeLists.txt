cmake_minimum_required(VERSION 3.1)
project(unify_include_guard
  VERSION 1.0.0
  DESCRIPTION "replace include guards to normalized one"
  HOMEPAGE_URL "https://github.com/lm-kajihara/unify-include-guard"
  LANGUAGES CXX)
file(GLOB SRC_CODES src/*.cpp)
set(EXECUTE_FILE "unify_include_guard")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(${EXECUTE_FILE} ${SRC_CODES})
target_compile_features(${EXECUTE_FILE} PRIVATE cxx_std_17)