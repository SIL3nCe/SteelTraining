set BUILD_DIR=buildExternal2017

set EDITOR_EXT_DIR=J:\ShineResearch\ShineEngine\bin
set SDK_EXT_DIR=J:\ShineResearch\ShineEngine\lib
set SDK_EXT_ROOT=J:\ShineResearch\ShineEngine

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DSHINE_EDITOR_EXT_DIR=%EDITOR_EXT_DIR% -DSHINE_INTERNAL=0 -DSHSDK_EDITOR_LIBRARIES_MASTER="optimized;%SDK_EXT_DIR%/ShSDK_Editor.lib;optimized;%SDK_EXT_DIR%/ShCore_Editor.lib" -DSHSDK_EDITOR_LIBRARIES_DEBUG="debug;%SDK_EXT_DIR%/ShSDK_Editor_Debug.lib;debug;%SDK_EXT_DIR%/ShCore_Editor_Debug.lib" -DSHSDK_EDITOR_LIBRARIES="%SDK_EXT_DIR%/ShSDK_Editor_Debug.lib;%SDK_EXT_DIR%/ShCore_Editor_Debug.lib" -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause