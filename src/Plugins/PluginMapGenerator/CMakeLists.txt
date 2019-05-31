cmake_minimum_required(VERSION 3.10)

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Plugin files
set(SOURCES_Plugin PluginMapGenerator.cpp PluginMapGenerator.h)
source_group("Plugin" FILES ${SOURCES_Plugin})

# Factory files
set(SOURCES_Factory PluginMapGeneratorFactory.cpp PluginMapGeneratorFactory.h)
source_group("Factory" FILES ${SOURCES_Factory})

# Map files
set(SOURCES_Map		Map/Map.cpp		Map/Map.h
					Map/Map2D.cpp	Map/Map2D.h)
source_group("Map" FILES ${SOURCES_Map})

# Map Entity files
set(SOURCES_Map_Entity	MapEntity/MapEntity.cpp			MapEntity/MapEntity.h)
source_group("MapEntity" FILES ${SOURCES_Map_Entity})

# MapGenerator files
set(SOURCES_MapGenerator	MapGenerator/MapGenerator.cpp		MapGenerator/MapGenerator.h
							MapGenerator/MapGeneratorTest.cpp	MapGenerator/MapGeneratorTest.h)
source_group("MapGenerator" FILES ${SOURCES_MapGenerator})

# Put everything together before adding platform-specific files
set(SOURCES 
${SOURCES_Plugin}
${SOURCES_Factory}
${SOURCES_Map}
${SOURCES_Map_Entity}
${SOURCES_MapGenerator}
)

# Compile to use it on Runtime
add_library(PluginMapGenerator STATIC ${SOURCES})
set_property(TARGET PluginMapGenerator PROPERTY FOLDER "Runtime")
set_property(TARGET PluginMapGenerator APPEND PROPERTY COMPILE_DEFINITIONS "${ShSDK_COMPILE_DEFINITIONS}")
set_property(TARGET PluginMapGenerator APPEND PROPERTY COMPILE_FLAGS "${ShSDK_COMPILE_FLAGS}")

target_link_libraries(PluginMapGenerator PRIVATE ${ShSDKEditor_LIBRARIES})

target_include_directories(PluginMapGenerator PUBLIC "${ShSDK_INCLUDE_DIRS}")
target_include_directories(PluginMapGenerator INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(PluginMapGenerator PRIVATE "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>")

# Compile to use it in the Shine Editor
add_library(PluginMapGenerator_Editor STATIC ${SOURCES})
set_property(TARGET PluginMapGenerator_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginMapGenerator_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${ShSDKEditor_COMPILE_DEFINITIONS}")
set_property(TARGET PluginMapGenerator_Editor APPEND PROPERTY COMPILE_FLAGS "${ShSDKEditor_COMPILE_FLAGS}")
set_property(TARGET PluginMapGenerator_Editor APPEND PROPERTY LINK_FLAGS "${ShSDKEditor_LINK_FLAGS}")
if (NOT MSVC)
	set_target_properties(PluginMapGenerator_Editor PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif (NOT MSVC)

target_link_libraries(PluginMapGenerator_Editor PRIVATE ${ShSDKEditor_LIBRARIES})

target_include_directories(PluginMapGenerator_Editor PUBLIC "${ShSDKEditor_INCLUDE_DIRS}")
target_include_directories(PluginMapGenerator_Editor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
