set BUILD_DIR=buildExternal2017

set SHINE_EXTERNAL_ROOT=W:/shine_external

set GENERATOR="Visual Studio 15 2017"

mkdir %BUILD_DIR%
cd %BUILD_DIR%

	cmake -G %GENERATOR% -DSHINE_INTERNAL=0 -DCMAKE_CONFIGURATION_TYPES=Debug;Release;Master ..

cd ..
pause