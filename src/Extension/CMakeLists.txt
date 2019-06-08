cmake_minimum_required(VERSION 3.10)

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

# configext files
set(SOURCES_configext ExtensionST.configext)
source_group("config" FILES ${SOURCES_configext})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} ${SOURCES_ExtensionST} ${SOURCES_configext})

# Set _Debug/_Release extension needed for editor
set(CMAKE_DEBUG_POSTFIX "_Debug")
set(CMAKE_RELEASE_POSTFIX "_Release")

add_library(ExtensionST SHARED ${SOURCES})

set_property(TARGET ExtensionST PROPERTY FOLDER "Editor")
set_property(TARGET ExtensionST PROPERTY PREFIX "")

set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_DEFINITIONS "${ShSDKEditor_COMPILE_DEFINITIONS}")
set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_DEFINITIONS "PLUGIN_ST_PATH=\"$<TARGET_FILE:PluginST_Editor>\"")
set_property(TARGET ExtensionST APPEND PROPERTY COMPILE_FLAGS "${ShSDKEditor_COMPILE_FLAGS}")

target_link_libraries(ExtensionST PRIVATE ${ShSDKEditor_LIBRARIES})
target_include_directories(ExtensionST PRIVATE ${ShSDKEditor_INCLUDE_DIRS} "$<TARGET_PROPERTY:PluginST_Editor,INTERFACE_INCLUDE_DIRECTORIES>")

if(WIN32)
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY "${ShGameEditor_EXTENSION_DIR}")
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG "${ShGameEditor_EXTENSION_DIR}")
	set_property(TARGET ExtensionST PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE "${ShGameEditor_EXTENSION_DIR}")
else(WIN32)
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY "${ShGameEditor_EXTENSION_DIR}")
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY_DEBUG "${ShGameEditor_EXTENSION_DIR}")
	set_property(TARGET ExtensionST PROPERTY LIBRARY_OUTPUT_DIRECTORY_RELEASE "${ShGameEditor_EXTENSION_DIR}")
endif(WIN32)

add_custom_command(TARGET ExtensionST PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/ExtensionST.configext ${ShGameEditor_EXTENSION_DIR})