SET BUILD_DIR=build

set GENERATOR="Visual Studio 14 2015"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DShSDK_DIR="W:/Shine/Shine/MainLine/Build/Win32_VS2015/cmake/lib/x86/ShSDK" -DSHSDK_EDITOR_LIBRARIES="W:/Shine/Shine/MainLine/Build/Win32_VS2015/Tools/Libraries/Internal/ShSDK/Debug/ShSDK_Editor_Debug.lib;W:/Shine/Shine/MainLine/Build/Win32_VS2015/Tools/Libraries/Internal/ShCore/Debug/ShCore_Editor_Debug.lib" -DSHINE_INTERNAL=1 -DSHINE_EDITOR_EXT_DIR="W:/Shine/Shine/MainLine/Build/Win32_VS2015/Compiled/Bin/x86/Extensions" -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..