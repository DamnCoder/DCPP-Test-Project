#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR
cd ..

rm -r ./build/
rm -r ./build_xcode/
rm -r ./build_eclipse/
exit 0