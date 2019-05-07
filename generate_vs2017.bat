SET BUILD_DIR=build2017

SET DEVLINE_DIR=W:/Shine/Shine/MainLine

SET SHSDK_DIR=%DEVLINE_DIR%/Build/Win32_VS2017/Tools/Libraries/Internal/

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DShSDK_DIR="%DEVLINE_DIR%/Build/Win32_VS2017/cmake/lib/x86/ShSDK" -DSHSDK_EDITOR_LIBRARIES_DEBUG="%SHSDK_DIR%/ShSDK/Debug/ShSDK_Editor_Debug.lib;%SHSDK_DIR%/ShCore/Debug/ShCore_Editor_Debug.lib;%SHSDK_DIR%/ShCompiler/Debug/ShCompiler_Editor_Debug.lib"  -DSHSDK_EDITOR_LIBRARIES_MASTER="%SHSDK_DIR%/ShDK/Master/ShSDK_Editor.lib;%SHSDK_DIR%/ShCore/Master/ShCore_Editor.lib;%SHSDK_DIR%/ShCompiler/Master/ShCompiler_Editor.lib" -DSHINE_INTERNAL=1 -DSHINE_EDITOR_EXT_DIR="%DEVLINE_DIR%/Build/Win32_VS2017/Compiled/Bin/x86/Extensions" -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause