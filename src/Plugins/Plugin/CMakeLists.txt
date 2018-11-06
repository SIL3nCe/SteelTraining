set(SOURCES_PLUGIN_IMPL Plugin.cpp Plugin.h)
source_group("" FILES ${SOURCES_PLUGIN_IMPL})

# Compile to use it on Runtime
add_library(Plugin STATIC ${SOURCES_PLUGIN_IMPL})

set_property(TARGET Plugin PROPERTY FOLDER "Runtime")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(Plugin PUBLIC "${SHSDK_LIBRARIES}")
target_include_directories(Plugin PUBLIC "${SHSDK_INCLUDE_DIRS}")

# Compile to use it in the Shine Editor
add_library(Plugin_Editor OBJECT ${SOURCES_PLUGIN_IMPL})

set_property(TARGET Plugin_Editor PROPERTY FOLDER "Editor")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET Plugin_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

target_link_libraries(Plugin_Editor PUBLIC "${SHSDK_EDITOR_LIBRARIES}")
target_include_directories(Plugin_Editor PUBLIC "${SHSDK_INCLUDE_DIRS}")

