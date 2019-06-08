SET BUILD_DIR=build2017_d3d11

SET DEVLINE_DIR=W:/Shine/Shine/MainLine

SET SHSDK_DIR=%DEVLINE_DIR%/Build/Win32_x86_VS2017_DX11/Tools/Libraries/Internal/

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DShSDK_DIR="%DEVLINE_DIR%/Build/Win32_x86_VS2017_DX11/cmake/lib/x86/ShSDK" -DShSDKEditor_DIR="%DEVLINE_DIR%/Build/Win32_x86_VS2017_DX11/cmake/lib/x86/ShSDKEditor" -DSHINE_INTERNAL=1 -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause