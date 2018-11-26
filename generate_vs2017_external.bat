set BUILD_DIR=build

set EDITOR_EXT_DIR=C:\ShineEngine\bin

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DSHINE_EDITOR_EXT_DIR=%EDITOR_EXT_DIR% -DSHINE_INTERNAL=0 -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause