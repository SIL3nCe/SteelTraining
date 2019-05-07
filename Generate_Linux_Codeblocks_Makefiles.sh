BUILD_DIR=Linux_CodeBlocks_Makefiles

DIR=`pwd`
GENERATOR="CodeBlocks - Unix Makefiles"

mkdir build
cd build

	mkdir ${BUILD_DIR}
	cd ${BUILD_DIR}

		for CONFIG in Debug Release Master
		do

			mkdir ${CONFIG}
			cd ${CONFIG}

				cmake -G "${GENERATOR}" -DSHINE_INTERNAL=0 -DCMAKE_BUILD_TYPE="${CONFIG}" ${DIR}

			cd ..

		done

	cd ..

cd ..
