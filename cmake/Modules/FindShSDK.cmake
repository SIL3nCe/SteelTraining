# - Try to find ShSDK
# Once done this will define
#  SHSDK_FOUND - System has ShSDK
#  SHSDK_INCLUDE_DIRS - The ShSDK include directories
#  SHSDK_LIBRARIES - The libraries needed to use ShSDK

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

find_path(SHINE_ROOT_DIR NAMES include lib HINTS ENV SHINE_BASE_DIR ${SHINE_BASE_DIR_PLATFORM_ARCH} NO_CMAKE_FIND_ROOT_PATH NO_DEFAULT_PATH)
if(NOT SHINE_ROOT_DIR)
	message(FATAL_ERROR "Could not locate root directory for ShineExternal")
endif(NOT SHINE_ROOT_DIR)

find_path(SHSDK_INCLUDE_DIR "ShSDK/ShSDK.h" HINTS "${SHINE_ROOT_DIR}" PATH_SUFFIXES "include" NO_CMAKE_FIND_ROOT_PATH)

macro(FIND_SHSDK_LIBRARY _var)
	find_library(${_var} NAMES ${ARGN} HINTS "${SHINE_ROOT_DIR}" PATH_SUFFIXES "lib" NO_CMAKE_FIND_ROOT_PATH)
	mark_as_advanced(${_var})
endmacro()

# ------------------------------------------------------------------------------------------------

if (MSVC)
	set(SHSDK_COMPILE_FLAGS "/EHs-c- /GR-") # disable exceptions / disable RTTI
else (MSVC)
	set(SHSDK_COMPILE_FLAGS "-fno-exceptions -fno-rtti")
endif (MSVC)

set(SHSDK_COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

# ------------------------------------------------------------------------------------------------

set(SHSDK_LIBRARIES )

FIND_SHSDK_LIBRARY(SHCORE_LIBRARY ShCore)
set(SHSDK_LIBRARIES ${SHSDK_LIBRARIES} "${SHCORE_LIBRARY}")

list(FIND ShSDK_FIND_COMPONENTS "ShEntryPoint" ShEntryPoint_INDEX)
if (${ShEntryPoint_INDEX} GREATER -1)
	FIND_SHSDK_LIBRARY(SHENTRYPOINT_LIBRARY ShEntryPoint)
	set(SHSDK_LIBRARIES ${SHSDK_LIBRARIES} "${SHENTRYPOINT_LIBRARY}")
endif()

list(FIND ShSDK_FIND_COMPONENTS "StubUserSystem" ShEntryPoint_INDEX)
if (${ShEntryPoint_INDEX} GREATER -1)
	FIND_SHSDK_LIBRARY(STUBUSERSYSTEM_LIBRARY StubUserSystem)
	set(SHSDK_LIBRARIES  ${SHSDK_LIBRARIES} "${STUBUSERSYSTEM_LIBRARY}")
endif()

FIND_SHSDK_LIBRARY(SHSDK_LIBRARY ShSDK)
if(SHSDK_LIBRARY)
	set(SHSDK_LIBRARIES "${SHSDK_LIBRARY}" "${SHSDK_LIBRARIES}" "${SHSDK_LIBRARY}") #${SHSDK_LIBRARY} is twice : ShSDK needs a User System and every User System depends upon ShSDK
endif(SHSDK_LIBRARY)

set(SHSDK_INCLUDE_DIRS "${SHSDK_INCLUDE_DIR}")

if (SHSDK_LIBRARY)

	if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
		#find_package(Threads) # automatic
		set(LIB_ANDROID android)
		set(LIB_LOG log)
		set(OPENSLES_LIBRARIES OpenSLES)
		set(OPENGLES2_LIBRARIES GLESv2)
		set(EGL_LIBRARIES EGL)
		
		list(APPEND SHSDK_LIBRARIES "${OPENGLES2_LIBRARIES}" "${EGL_LIBRARIES}" "${OPENSLES_LIBRARIES}" "${LIB_ANDROID}" "${LIB_LOG}")

	elseif (APPLE)

		# TODO

	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux") # Not Android and not Apple ... must be Linux or BSD

		find_package(Threads QUIET)
		find_package(OpenGL QUIET)
		find_package(OpenAL QUIET)
		find_package(X11 QUIET)

		list(APPEND SHSDK_LIBRARIES "${OPENGL_LIBRARIES}" "${X11_LIBRARIES}" "${OPENAL_LIBRARY}" "${CMAKE_THREAD_LIBS_INIT}")

	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

		find_package(DirectX9 REQUIRED)
		find_package(XAudio REQUIRED)
		find_package(XInput REQUIRED)

		list(APPEND SHSDK_INCLUDE_DIRS "${DirectX9_INCLUDE_DIR}")
		list(APPEND SHSDK_LIBRARIES "${DirectX9_LIBRARIES}" "${XInput_LIBRARIES}" "${XAudio_LIBRARY}")

	else ()

		# TODO

		message("Platform not supported")

	endif()

endif (SHSDK_LIBRARY)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(ShSDK DEFAULT_MSG SHSDK_LIBRARIES SHSDK_INCLUDE_DIRS)