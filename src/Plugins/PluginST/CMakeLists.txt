cmake_minimum_required(VERSION 3.10)

set(SHINE_EDITOR_EXT_DIR "" CACHE PATH "Extension directory")
set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK (editor) path") # FIXME

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Plugin files
set(SOURCES_PluginST PluginST.cpp PluginST.h)
source_group("Plugin" FILES ${SOURCES_PluginST})

# Factory files
set(SOURCES_Factory PluginFactory.cpp PluginFactory.h)
source_group("Factory" FILES ${SOURCES_Factory})

# World files
set(SOURCES_World World/World.cpp World/World.h)
source_group("World" FILES ${SOURCES_World})

# Inputs files
set(SOURCES_Inputs World/InputManager.cpp World/InputManager.h)
source_group("World\\Inputs" FILES ${SOURCES_Inputs})

# Character files
set(SOURCES_BaseCharacter World/Character/BaseCharacter.cpp World/Character/BaseCharacter.h)
source_group("World\\Character" FILES ${SOURCES_BaseCharacter})

# Character files
set(SOURCES_PlayerCharacter World/Character/PlayerCharacter.cpp World/Character/PlayerCharacter.h)
source_group("World\\Character" FILES ${SOURCES_PlayerCharacter})

# Put everything together before adding platform-specific files
set(SOURCES 
${SOURCES_PluginST}
${SOURCES_Factory}
${SOURCES_World}
${SOURCES_Inputs}
${SOURCES_BaseCharacter}
${SOURCES_PlayerCharacter}
)

# Compile to use it on Runtime
add_library(PluginST STATIC ${SOURCES})
set_property(TARGET PluginST PROPERTY FOLDER "Runtime")
set_property(TARGET PluginST APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET PluginST APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(PluginST INTERFACE ${SHSDK_LIBRARIES})
target_link_libraries(PluginST INTERFACE Box2D)

target_include_directories(PluginST PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(PluginST INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(PluginST PRIVATE "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>")

# Compile to use it in the Shine Editor
add_library(PluginST_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET PluginST_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET PluginST_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

target_link_libraries(PluginST_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES})
target_link_libraries(PluginST_Editor PRIVATE Box2D_shared)

target_include_directories(PluginST_Editor PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(PluginST_Editor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(PluginST_Editor PUBLIC "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>") # Public for Extension
