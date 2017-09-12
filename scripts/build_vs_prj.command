#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR
cd ..

build_folder=build_vs

if [ ! -d ./$build_folder ]; then
	mkdir $build_folder
fi

cd $build_folder

cmake ../project -G "Visual Studio 10"

exit 0