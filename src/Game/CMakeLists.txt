add_executable(Game WIN32 Game.cpp Game.h)

set_property(TARGET Game PROPERTY FOLDER "Runtime")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

target_link_libraries(Game PRIVATE Plugin) # link with plugins
target_include_directories(Game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../Plugins/")
target_link_libraries(Game PRIVATE "${SHSDK_LIBRARIES}")
target_include_directories(Game PRIVATE "${SHSDK_INCLUDE_DIRS}")

CopyToShineSAAS(Game)
