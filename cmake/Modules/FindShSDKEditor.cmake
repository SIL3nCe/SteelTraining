# - Try to find ShSDKEditor
# Once done this will define
#  ShSDKEditor_FOUND - System has ShSDK
#  ShSDKEditor_LIBRARIES - The libraries needed to use ShSDK
#  ShSDKEditor_INCLUDE_DIRS - The list of include directories to use ShSDK
#  ShGameEditor_EXTENSION_DIR - The path to the ShGameEditor's Extension directory
#

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/win32")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "WindowsStore")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/uwp")
elseif(CMAKE_SYSTEM_NAME MATCHES "Durango")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/xboxone")
elseif(CMAKE_SYSTEM_NAME MATCHES "ORBIS")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/ps4")
elseif(CMAKE_SYSTEM_NAME MATCHES "PSP2")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/psvita")
elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/android")
elseif(DEFINED IOS)
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}/ios")
else(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(SHINE_BASE_DIR_PLATFORM "$ENV{SHINE_BASE_DIR}")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	if(EXISTS "/lib/x86_64-linux-gnu")
		string(REPLACE "-linux-gnu" "" BUILD_ARCHITECTURE ${CMAKE_LIBRARY_ARCHITECTURE})
		set(SHINE_BASE_DIR_PLATFORM_ARCH "${SHINE_BASE_DIR_PLATFORM}/${BUILD_ARCHITECTURE}")
	else(EXISTS "/lib/x86_64-linux-gnu")
		set(SHINE_BASE_DIR_PLATFORM_ARCH "${SHINE_BASE_DIR_PLATFORM}/${CMAKE_LIBRARY_ARCHITECTURE}")
	endif(EXISTS "/lib/x86_64-linux-gnu")
else(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(SHINE_BASE_DIR_PLATFORM_ARCH "${SHINE_BASE_DIR_PLATFORM}/${CMAKE_LIBRARY_ARCHITECTURE}")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

find_path(SHINE_ROOT_DIR NAMES include lib HINTS ENV SHINE_BASE_DIR ${SHINE_BASE_DIR_PLATFORM_ARCH})
if(NOT SHINE_ROOT_DIR)
	message(FATAL_ERROR "Could not locate root directory for ShineExternal")
endif(NOT SHINE_ROOT_DIR)

# ------------------------------------------------------------------------------------------------

find_path(ShSDKEditor_INCLUDE_DIRS NAMES ShSDK/ShSDK.h HINTS ${SHINE_ROOT_DIR}/include)

find_library(ShCoreEditor_LIBRARY NAMES ShCoreEditor HINTS ${SHINE_ROOT_DIR})
find_library(ShSDKEditor_LIBRARY NAMES ShSDKEditor HINTS ${SHINE_ROOT_DIR})
find_library(ShCompilerEditor_LIBRARY NAMES ShCompilerEditor HINTS ${SHINE_ROOT_DIR})

find_library(ShCoreEditor_LIBRARY_DEBUG NAMES ShCoreEditor_Debug HINTS ${SHINE_ROOT_DIR})
find_library(ShSDKEditor_LIBRARY_DEBUG NAMES ShSDKEditor_Debug HINTS ${SHINE_ROOT_DIR})
find_library(ShCompilerEditor_LIBRARY_DEBUG NAMES ShCompilerEditor_Debug HINTS ${SHINE_ROOT_DIR})

set(ShSDKEditor_LIBRARIES "optimized;${ShCoreEditor_LIBRARY}" "optimized;${ShSDKEditor_LIBRARY}" "optimized;${ShCompilerEditor_LIBRARY}" CACHE PATH "ShSDK Editor libraries")
if(ShCoreEditor_LIBRARY_DEBUG AND ShSDKEditor_LIBRARY_DEBUG AND ShCompilerEditor_LIBRARY_DEBUG)
	set(ShSDKEditor_LIBRARIES ${ShSDKEditor_LIBRARIES} "debug;${ShCoreEditor_LIBRARY_DEBUG}" "debug;${ShSDKEditor_LIBRARY_DEBUG}" "debug;${ShCompilerEditor_LIBRARY_DEBUG}" CACHE PATH "ShSDK Editor libraries")
endif(ShCoreEditor_LIBRARY_DEBUG AND ShSDKEditor_LIBRARY_DEBUG AND ShCompilerEditor_LIBRARY_DEBUG)

set(ShGameEditor_EXTENSION_DIR "${SHINE_ROOT_DIR}/Bin/Extensions" CACHE PATH "Extension directory")
file(MAKE_DIRECTORY ${ShGameEditor_EXTENSION_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ShSDKEditor DEFAULT_MSG ShSDKEditor_INCLUDE_DIRS ShSDKEditor_LIBRARIES ShGameEditor_EXTENSION_DIR)