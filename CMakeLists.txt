cmake_minimum_required(VERSION 3.18)
project(DeepForge-Toolset)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)
include(FetchContent)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dylib)
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64") # for desktop
  set(architecture "x64")
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "AMD64")
  set(architecture "x64")
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64") # for tx2
  set(architecture "arm64")
endif()
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build/${architecture}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message("🔥 Copying folder of Scripts ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/Scripts DESTINATION ${CMAKE_BINARY_DIR})
message("✅ Copying folder of Scripts ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
message("🔥 Copying folder of utils ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/utils DESTINATION ${CMAKE_BINARY_DIR})
message("✅ Copying folder of utils ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
message("🔥 Copying folder of DB ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/DB DESTINATION ${CMAKE_BINARY_DIR})
message("✅ Copying folder of DB ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
message("🔥 Copying folder of locale ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/locale DESTINATION ${CMAKE_BINARY_DIR})
message("✅ Copying folder of locale ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${JSONCPP_INCLUDE_DIR}\"")  
endif()
# UpdateManager
FetchContent_Declare(UpdateManager
  GIT_REPOSITORY https://github.com/DeepForge-Technology/UpdateManager.git
  GIT_TAG master
)
FetchContent_GetProperties(UpdateManager)
if(NOT UpdateManager_POPULATED)
  FetchContent_Populate(UpdateManager)
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/_deps/updatemanager-src)
endif()

# UninstallerDeepForge-Toolset
FetchContent_Declare(UninstallerDeepForge-Toolset
  GIT_REPOSITORY https://github.com/DeepForge-Technology/UninstallerDeepForge-Toolset.git
  GIT_TAG master
)
FetchContent_GetProperties(UninstallerDeepForge-Toolset)
if(NOT UninstallerDeepForge-Toolset_POPULATED)
  FetchContent_Populate(UninstallerDeepForge-Toolset)
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/_deps/uninstallerdeepforge-toolset-src)
endif()

# include(./CompileResources.cmake)
# fmt
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/DeepForge-Technology/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)
# jsoncpp
FetchContent_Declare(jsoncpp
GIT_REPOSITORY https://github.com/DeepForge-Technology/jsoncpp.git
GIT_TAG master
)
# if(NOT jsoncpp_POPULATED)
#   FetchContent_Populate(jsoncpp)
#   add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR})
# endif()
FetchContent_MakeAvailable(jsoncpp)
FetchContent_Declare(SQLite
  GIT_REPOSITORY https://github.com/DeepForge-Technology/SQLite.git
  GIT_TAG master
)
FetchContent_MakeAvailable(SQLite)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG
      "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996"
      CACHE STRING "Debug compiler flags" FORCE
    )
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")  
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -I /usr/local/include -I ../../include -DCURL_STATICLIB -Bstatic")
endif()

#target_include_directories(DeepForge-Toolset PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/src/include)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
set(TEST_SOURCE_FILES
  ./src/test/MainTest.cpp
  ./src/DatabaseConnect.cpp
  ./src/DatabaseConnect.hpp
)
enable_testing()
include_directories(${CMAKE_SOURCE_DIR}/src/)
add_executable(
  MainTest
  ${TEST_SOURCE_FILES}
)
target_link_libraries(
  MainTest
  SQLite
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MainTest)

set(SOURCE_FILES
  ./src/DeepForgeToolset.cpp
  ./src/DatabaseConnect.cpp
  ./src/DatabaseConnect.hpp
)
add_executable(DeepForge-Toolset ${SOURCE_FILES})
if (WIN32)
  FetchContent_Declare(libcurl
    GIT_REPOSITORY https://github.com/DeepForge-Technology/curl.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(libcurl)
  set(LIBRARIES
    fmt::fmt 
    urlmon
    libcurl_static
    jsoncpp_static
    ws2_32
    SQLite
    Threads::Threads
  )
elseif(APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++") 
  find_package(libzip REQUIRED)
  # find_package(CURL)
  # if(CURL_FOUND)
  #   include_directories(${CURL_INCLUDE_DIR})
  #   set(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
  # else(CURL_FOUND)
  #   message(FATAL_ERROR "Could not find the CURL library and development files.")
  # endif(CURL_FOUND)
  FetchContent_Declare(libcurl
  GIT_REPOSITORY https://github.com/DeepForge-Technology/curl.git
  GIT_TAG master
  )
  FetchContent_MakeAvailable(libcurl)
  set(LIBRARIES
    fmt::fmt 
    jsoncpp_static
    libcurl_static
    zip
    SQLite
    Threads::Threads
  )
elseif(UNIX)
  FetchContent_Declare(libzip
    GIT_REPOSITORY https://github.com/DeepForge-Technology/libzip.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(libzip)
  FetchContent_Declare(libcurl
  GIT_REPOSITORY https://github.com/DeepForge-Technology/curl.git
  GIT_TAG master
  )
  FetchContent_MakeAvailable(libcurl)
  set(LIBRARIES
    fmt::fmt 
    jsoncpp_static
    libcurl_static
    SQLite
    zip
    Threads::Threads
  )
endif()

target_sources(DeepForge-Toolset PRIVATE ${CMAKE_SOURCE_DIR}/src/resource.rc)
target_link_libraries(DeepForge-Toolset 
  PRIVATE  
  ${LIBRARIES}
) 
# if(APPLE)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents/MacOS)
#   file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents/Resources)
#   # Поиск всех файлов в исходной папке
#   file(GLOB ALL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src*")
#   # Копирование всех найденных файлов в целевую папку
#   file(COPY ${ALL_SOURCE_FILES} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents/Resources")
#   file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/build/DeepForge-Toolset DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents/MacOS")
#   file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/DeepForge-Toolset.app/Contents")
# endif()