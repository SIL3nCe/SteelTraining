cmake_minimum_required(VERSION 3.10)

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

# HUD files
set(SOURCES_HUD HUD/HUD.cpp HUD/HUD.h)
source_group("HUD" FILES ${SOURCES_HUD})

# Inputs files
set(SOURCES_Inputs World/InputManager.cpp World/InputManager.h)
source_group("World\\Inputs" FILES ${SOURCES_Inputs})

# Object
set(SOURCES_Object World/Object.cpp World/Object.h)
source_group("World" FILES ${SOURCES_Object})

# Object Wall
set(SOURCES_ObjectWall World/Objects/ObjectWall.cpp World/Objects/ObjectWall.h)
source_group("World\\Objects" FILES ${SOURCES_ObjectWall})

# Character files
set(SOURCES_BaseCharacter World/Character/BaseCharacter.cpp World/Character/BaseCharacter.h)
source_group("World\\Character" FILES ${SOURCES_BaseCharacter})

# Character files
set(SOURCES_PlayerCharacter World/Character/PlayerCharacter.cpp World/Character/PlayerCharacter.h)
source_group("World\\Character" FILES ${SOURCES_PlayerCharacter})

# Character files
set(SOURCES_EnemyCharacter	World/Character/EnemyCharacter.cpp World/Character/EnemyCharacter.h
							World/Character/EnemyMeleeCharacter.cpp World/Character/EnemyMeleeCharacter.h)
source_group("World\\Character" FILES ${SOURCES_EnemyCharacter})

# Put everything together before adding platform-specific files
set(SOURCES
${SOURCES_PluginST}
${SOURCES_Factory}
${SOURCES_World}
${SOURCES_HUD}
${SOURCES_Inputs}
${SOURCES_BaseCharacter}
${SOURCES_PlayerCharacter}
${SOURCES_EnemyCharacter}
${SOURCES_Object}
${SOURCES_ObjectWall}
)

# Compile to use it on Runtime
add_library(PluginST STATIC ${SOURCES})
set_property(TARGET PluginST PROPERTY FOLDER "Runtime")
set_property(TARGET PluginST APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
if (NOT MSVC)
	set_property(TARGET PluginST APPEND PROPERTY COMPILE_OPTIONS -fno-exceptions -fno-rtti)
endif (NOT MSVC)
set_property(TARGET PluginST APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(PluginST PRIVATE ${SHSDK_LIBRARIES})
target_link_libraries(PluginST PUBLIC PluginMapGenerator)
target_link_libraries(PluginST INTERFACE Box2D)

target_include_directories(PluginST PUBLIC "${SHSDK_INCLUDE_DIRS}")
target_include_directories(PluginST INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(PluginST PUBLIC "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>" "$<TARGET_PROPERTY:PluginMapGenerator,INCLUDE_DIRECTORIES>") 

# Compile to use it in the Shine Editor
add_library(PluginST_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET PluginST_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
set_property(TARGET PluginST_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET PluginST_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

add_dependencies(PluginST_Editor PluginMapGenerator_Editor)

target_link_libraries(PluginST_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES})
target_link_libraries(PluginST_Editor PRIVATE PluginMapGenerator_Editor)
target_link_libraries(PluginST_Editor PRIVATE Box2D_shared)

target_include_directories(PluginST_Editor PRIVATE "${SHSDK_INCLUDE_DIRS}")
target_include_directories(PluginST_Editor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(PluginST_Editor PUBLIC "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>" "$<TARGET_PROPERTY:PluginMapGenerator_Editor,INCLUDE_DIRECTORIES>") # Public for Extension
