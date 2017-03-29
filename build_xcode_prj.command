#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if [ ! -d ./build_xcode ]; then
	mkdir build_xcode
fi
cd ./build_xcode
cmake -G"Xcode" -DCMAKE_BUILD_TYPE=Debug ../project