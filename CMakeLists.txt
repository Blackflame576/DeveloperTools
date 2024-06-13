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

# if (WIN32)
#   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
# endif()
set(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
message("🔥 Copying folder of Scripts ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/Scripts DESTINATION ${CMAKE_BINARY_DIR}/)
message("✅ Copying folder of Scripts ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
message("🔥 Copying folder of DB ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/DB DESTINATION ${CMAKE_BINARY_DIR}/)
message("✅ Copying folder of DB ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")
message("🔥 Copying folder of locale ${CMAKE_BINARY_DIR} ...")
file(COPY ${CMAKE_SOURCE_DIR}/src/locale DESTINATION ${CMAKE_BINARY_DIR}/)
message("✅ Copying folder of locale ${CMAKE_BINARY_DIR} was successfully.")
message("==================================")

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${JSONCPP_INCLUDE_DIR}\"")  
elseif(WIN32)
  message("🔥 Copying folder of DLL ${CMAKE_BINARY_DIR} ...")
  file(COPY ${CMAKE_SOURCE_DIR}/DLL/ DESTINATION ${CMAKE_BINARY_DIR}/)
  message("✅ Copying folder of DLL ${CMAKE_BINARY_DIR} was successfully.")
  message("==================================")
endif()
# include(./CompileResources.cmake)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG
      "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996 /MT"
      CACHE STRING "Debug compiler flags" FORCE
    )
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")  
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -I /usr/local/include -I ../../include -DCURL_STATICLIB -Bstatic")
endif()
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadDependecies.cmake)
#target_include_directories(DeepForge-Toolset PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES
  src/DeepForge-Toolset.cpp
  include/DeepForge-Toolset/DeepForge-Toolset.hpp
)

add_definitions(-DUNICODE -D_UNICODE)
add_executable(DeepForge-Toolset ${SOURCE_FILES})

if (WIN32)
  set(USE_WINDOWS_SSPI ON)
  set(USE_SCHANNEL ON)
  set(LIBRARIES
  fmt::fmt 
  urlmon
  libcurl_static
  jsoncpp_static
  ws2_32
  SQLite
  Progressbar
  DatabaseAPI
  miniz
  Threads::Threads
  Logger
  )
elseif(APPLE)
  #set(MACOSX_BUNDLE_BUNDLE_NAME "DeepForge-Toolset")
  #set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.DeepForge.DeepForge-Toolset")
  #set(MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist")

  #set_source_files_properties(${MACOSX_BUNDLE_INFO_PLIST} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

  #set_target_properties(DeepForge-Toolset PROPERTIES
  #  MACOSX_BUNDLE TRUE
  #  MACOSX_BUNDLE_INFO_PLIST ${MACOSX_BUNDLE_INFO_PLIST}
  #)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++") 
  set(LIBRARIES
  fmt::fmt 
  jsoncpp_static
  libcurl_static
  SQLite
  Progressbar
  DatabaseAPI
  miniz
  Threads::Threads
  Logger
  )
elseif(UNIX)
  set(LIBRARIES
  fmt::fmt 
  jsoncpp_static
  libcurl_static
  SQLite
  Progressbar
  DatabaseAPI
  miniz
  Threads::Threads
  Logger
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