
#
# Options
option(ENABLE_SKIP_TITLE_MENU "Enable TitleMenu skipping" ON)

# Settings files
set(SOURCES_Settings Settings.cpp Settings.h) 
source_group("Settings" FILES ${SOURCES_Settings})

# Application files
set(SOURCES_Application Application.cpp Application.h)
source_group("" FILES ${SOURCES_Application})

# GameState files
set(SOURCES_GameState GameStateManager.cpp GameStateManager.h GameState.cpp GameState.h) 
source_group("GameState" FILES ${SOURCES_GameState})

# GameState\\TitleMenu files
set(SOURCES_GameStateTitleMenu GameStateTitleMenu.cpp GameStateTitleMenu.h) 
source_group("GameState\\TitleMenu" FILES ${SOURCES_GameStateTitleMenu})

# GameState\\TitleMenuSettings files
set(SOURCES_GameStateTitleMenuSettings GameStateTitleMenuSettings.cpp GameStateTitleMenuSettings.h) 
source_group("GameState\\TitleMenuSettings" FILES ${SOURCES_GameStateTitleMenuSettings})

# GameState\\Game files
set(SOURCES_GameStateGame GameStateGame.cpp GameStateGame.h) 
source_group("GameState\\Game" FILES ${SOURCES_GameStateGame})

# Game files
set(SOURCES_Game Game.cpp Game.h) 
source_group("Game" FILES ${SOURCES_Game})

# Put everything together before adding platform-specific files
set(SOURCES
${SOURCES_Settings}
${SOURCES_Application}
${SOURCES_GameState}
${SOURCES_GameStateTitleMenu}
${SOURCES_GameStateTitleMenuSettings}
${SOURCES_GameStateGame}
${SOURCES_Game}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(Game WIN32 ${SOURCES})
ELSE()
	add_executable(Game ${SOURCES})
ENDIF()

if (MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
	set_target_properties(Game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Cooking/Windows")
endif (MSVC)

set_property(TARGET Game PROPERTY FOLDER "Runtime")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

# Custom properties
if(ENABLE_SKIP_TITLE_MENU)
	set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "ENABLE_SKIP_TITLE_MENU=1")
else(ENABLE_SKIP_TITLE_MENU)
	set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "ENABLE_SKIP_TITLE_MENU=0")
endif(ENABLE_SKIP_TITLE_MENU)

target_link_libraries(Game PRIVATE ${SHSDK_LIBRARIES})
target_link_libraries(Game PRIVATE PluginST)
target_include_directories(Game PRIVATE "${SHSDK_INCLUDE_DIRS}" "$<TARGET_PROPERTY:PluginST,INCLUDE_DIRECTORIES>")
