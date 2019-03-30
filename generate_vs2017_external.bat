set BUILD_DIR=buildExternal2017

set EDITOR_EXT_DIR=C:\ShineResearch\ShineEngine\bin
set SDK_EXT_DIR=C:\ShineResearch\ShineEngine\lib

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DSHINE_EDITOR_EXT_DIR=%EDITOR_EXT_DIR% -DSHINE_INTERNAL=0 -DSHSDK_LIBRARIES="%SDK_EXT_DIR%/ShSDK.lib;%SDK_EXT_DIR%/ShCore.lib" -DSHSDK_EDITOR_LIBRARIES="%SDK_EXT_DIR%/ShSDK_Editor.lib;%SDK_EXT_DIR%/ShCore_Editor.lib" -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause