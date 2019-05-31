cmake_minimum_required(VERSION 3.10)

if(NOT SHINE_EDITOR_EXT_DIR)
	message(FATAL_ERROR "Error, variable 'SHINE_EDITOR_EXT_DIR' is not set. Please set it as an argument of the cmake command.")
endif(NOT SHINE_EDITOR_EXT_DIR)

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Extension files
set(SOURCES_ExtensionST ExtensionST.cpp ExtensionST.h)
source_group("ExtensionST" FILES ${SOURCES_ExtensionST})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} ${SOURCES_ExtensionST})

# Set _Debug extension needed for editor
set(CMAKE_DEBUG_POSTFIX "_Debug")

add_library(ExtensionST SHARED ${SOURCES})

set_property(TARGET ExtensionST PROPERTY FOLDER "Editor")

set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_DEFINITIONS "${ShSDKEditor_COMPILE_DEFINITIONS}")
set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_FLAGS "${ShSDKEditor_COMPILE_FLAGS}")

set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_DEFINITIONS "PLUGIN_ST_PATH=\"$<TARGET_FILE:PluginST_Editor>\"")

target_link_libraries(ExtensionST PRIVATE ${ShSDKEditor_LIBRARIES})
target_include_directories(ExtensionST PRIVATE ${ShSDKEditor_INCLUDE_DIRS} "$<TARGET_PROPERTY:PluginST_Editor,INTERFACE_INCLUDE_DIRECTORIES>")

if(WIN32)
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SHINE_EDITOR_EXT_DIR}")
else(WIN32)
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SHINE_EDITOR_EXT_DIR}")
endif(WIN32)

set_property(TARGET ExtensionST PROPERTY PREFIX )

file(COPY "ExtensionST.configext" DESTINATION "${SHINE_EDITOR_EXT_DIR}")
