# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(DeveloperTools)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
set(CURL_INCLUDE_DIR " ${CMAKE_SOURCE_DIR}/../../include -L ../../lib/")
include_directories(${CURL_INCLUDE_DIR})
if(LIBCURL_ENABLE)
    target_link_libraries(CURL-DEMO CURL::libcurl)
endif()
add_executable(DeveloperTools DeveloperTools.cpp)
# We need hello.h and the hello library
# target_link_libraries(DeveloperTools
#     PRIVATE AppInstaller)
target_link_libraries(DeveloperTools ${CURL_LIBRARIES})
# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(DeveloperTools PUBLIC cxx_std_20)