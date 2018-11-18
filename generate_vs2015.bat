SET BUILD_DIR=build

SET DEVLINE_DIR=C:/ShineP4/Shine/MainLine

SET SHSDK_DIR=%DEVLINE_DIR%/Build/Win32_VS2015/Tools/Libraries/Internal/

set GENERATOR="Visual Studio 14 2015"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DShSDK_DIR="%DEVLINE_DIR%/Build/Win32_VS2015/cmake/lib/x86/ShSDK" -DSHSDK_EDITOR_LIBRARIES="%SHSDK_DIR%/ShSDK/Debug/ShSDK_Editor_Debug.lib;%SHSDK_DIR%/ShCore/Debug/ShCore_Editor_Debug.lib" -DSHINE_INTERNAL=1 -DSHINE_EDITOR_EXT_DIR="%DEVLINE_DIR%/Build/Win32_VS2015/Compiled/Bin/x86/Extensions" -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause