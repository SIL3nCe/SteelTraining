cmake_minimum_required(VERSION 3.1)

project(TemporaryDungeon)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)

# Warnings
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS") # use /wd4996 instead ?
else (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (MSVC)

# Find shine Engine libraries
find_package(ShSDK REQUIRED StubUserSystem ShEntryPoint)

set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK Editor libraries") # ugly
set(SHINE_EDITOR_EXT_DIR "$ENV{SHINE_BASE_DIR}/Bin/Extensions" CACHE PATH "Extension directory") # ugly too

# Include some cmake helpers
include(cmake/Master.cmake)
include(cmake/TargetBuildSAAS.cmake)

ConfigureShineSAAS()

add_subdirectory(src)
