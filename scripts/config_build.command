#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR
cd ..

./utilities/CMakeConfigure/scripts/build.command
./utilities/NewClassProject/scripts/build.command

# Update the CMakeLists.txt
./create_cmakelists.command

# Create build dir if it doesn't exist
if [ ! -d ./build ]; then
	mkdir build
fi

# Configure build
# -H indicates where the project sources are located
# -B indicates where the build folder will be located
cmake -Hproject -Bbuild

# Build
cd ./build
make install
