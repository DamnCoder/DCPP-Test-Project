#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
rm -r $DIR/build/
rm -r $DIR/build_xcode/
rm -r $DIR/build_eclipse/
exit 0